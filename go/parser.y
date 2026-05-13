%{
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

int yylex(void);
void yyrestart(FILE *input_file);
void reset_lexer_state(void);
void yyerror(const char *s);

typedef struct {
    char **items;
    size_t len;
    size_t cap;
} StringList;

static const char *current_file = "<stdin>";
static int syntax_errors = 0;
static int lexical_errors = 0;
static int parsed_files = 0;
static StringList imports = {0};


static void list_push(StringList *list, const char *value);
static void list_free(StringList *list);
static char *xstrdup(const char *value);
static char *path_join(const char *left, const char *right);
static int is_go_file(const char *path);
static int is_regular_file(const char *path);
static int is_directory(const char *path);
static void collect_go_files(const char *path, StringList *files);
static void parse_file(const char *path);
static void record_import_string(char *raw);
static void scan_standalone_identifier_lines(const char *path);
void record_lexical_error(const char *text, int line);
%}

%union {
    char *sval;
}

%token PACKAGE IMPORT FUNC VAR TYPE CONST STRUCT INTERFACE ANY
%token BREAK DEFAULT SELECT CASE DEFER GO MAP CHAN ELSE GOTO SWITCH FALLTHROUGH IF RANGE RETURN FOR CONTINUE
%token IDENT NUM RUNE
%token <sval> STRING
%token ASSIGN DECLARE EQ NEQ OP
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token COMMA DOT COLON SEMICOLON UNKNOWN

%%

program:
    maybe_semis package_clause file_items
    ;

package_clause:
    PACKAGE IDENT required_semis
    | error required_semis { yyerrok; }
    ;

file_items:
    /* empty */
    | file_items file_item
    ;

file_item:
    import_decl
    | balanced_unit
    | SEMICOLON 
    | error SEMICOLON { yyerrok; yyclearin; }
    ;

import_decl:
    IMPORT import_body
    ;

import_body:
    STRING { record_import_string($1); free($1); }
    | IDENT STRING { record_import_string($2); free($2); }
    | DOT STRING { record_import_string($2); free($2); }
    | LPAREN import_specs RPAREN
    ;

import_specs:
    /* empty */
    | import_specs import_spec
    ;

import_spec:
    SEMICOLON
    | STRING { record_import_string($1); free($1); }
    | IDENT STRING { record_import_string($2); free($2); }
    | DOT STRING { record_import_string($2); free($2); }
    ;

balanced_unit:
    simple_token
    | LPAREN balanced_seq RPAREN
    | LBRACKET balanced_seq RBRACKET
    | LBRACE balanced_seq RBRACE
    ;

balanced_seq:
    /* empty */
    | balanced_seq balanced_unit
    | balanced_seq SEMICOLON
    ;

simple_token:
    FUNC | VAR | TYPE | CONST | STRUCT | INTERFACE | ANY
    | BREAK | DEFAULT | SELECT | CASE | DEFER | GO | MAP | CHAN | ELSE | GOTO | SWITCH | FALLTHROUGH | IF | RANGE | RETURN | FOR | CONTINUE
    | IDENT | NUM | RUNE
    | STRING { free($1); } 
    | ASSIGN | DECLARE | EQ | NEQ | OP
    | COMMA | DOT | COLON | UNKNOWN
    ;

required_semis:
    SEMICOLON 
    ;

maybe_semis:
    /* empty */
    | semis
    ;

semis:
    SEMICOLON 
    | semis SEMICOLON 
    ;

%%

static char *xstrdup(const char *value) {
    char *copy = strdup(value);
    if (!copy) {
        perror("strdup");
        exit(2);
    }
    return copy;
}

static void *xrealloc(void *ptr, size_t size) {
    void *next = realloc(ptr, size);
    if (!next) {
        perror("realloc");
        exit(2);
    }
    return next;
}

static void list_push(StringList *list, const char *value) {
    size_t i;
    for (i = 0; i < list->len; i++) {
        if (strcmp(list->items[i], value) == 0) {
            return;
        }
    }
    if (list->len == list->cap) {
        list->cap = list->cap ? list->cap * 2 : 16;
        list->items = xrealloc(list->items, list->cap * sizeof(char *));
    }
    list->items[list->len++] = xstrdup(value);
}

static void list_free(StringList *list) {
    size_t i;
    for (i = 0; i < list->len; i++) {
        free(list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->len = 0;
    list->cap = 0;
}

static char *path_join(const char *left, const char *right) {
    size_t left_len = strlen(left);
    size_t right_len = strlen(right);
    int need_slash = left_len > 0 && left[left_len - 1] != '/';
    char *result = malloc(left_len + right_len + (size_t)need_slash + 1);
    if (!result) {
        perror("malloc");
        exit(2);
    }
    strcpy(result, left);
    if (need_slash) {
        strcat(result, "/");
    }
    strcat(result, right);
    return result;
}

static int is_go_file(const char *path) {
    size_t len = strlen(path);
    return len > 3 && strcmp(path + len - 3, ".go") == 0;
}

static int is_regular_file(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

static int is_directory(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

static int should_skip_dir(const char *name) {
    return strcmp(name, ".git") == 0 ||
           strcmp(name, ".idea") == 0 ||
           strcmp(name, ".vscode") == 0 ||
           strcmp(name, "node_modules") == 0;
}

static void collect_go_files(const char *path, StringList *files) {
    if (is_regular_file(path)) {
        if (is_go_file(path)) {
            list_push(files, path);
        }
        return;
    }

    if (is_directory(path)) {
        DIR *dir = opendir(path);
        struct dirent *entry;
        if (!dir) {
            fprintf(stderr, "[WARN] Не удалось открыть каталог %s: %s\n", path, strerror(errno));
            return;
        }
        while ((entry = readdir(dir)) != NULL) {
            char *child;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            if (should_skip_dir(entry->d_name)) {
                continue;
            }
            child = path_join(path, entry->d_name);
            collect_go_files(child, files);
            free(child);
        }
        closedir(dir);
    }
}

static void parse_file(const char *path) {
    FILE *file = fopen(path, "r");
    int before = syntax_errors + lexical_errors;
    if (!file) {
        fprintf(stderr, "[ERROR] Не удалось открыть файл %s: %s\n", path, strerror(errno));
        syntax_errors++;
        return;
    }

    current_file = path;
    yylineno = 1;
    yyin = file;
    yyrestart(file);
    reset_lexer_state();

    printf("\n[FILE] %s\n", path);
    scan_standalone_identifier_lines(path);
    yyparse();
    parsed_files++;

    if (syntax_errors + lexical_errors == before) {
        printf("[OK] Лексико-синтаксический проход завершен без ошибок.\n");
    } else {
        printf("[FAIL] В файле обнаружены ошибки: %d\n", syntax_errors + lexical_errors - before);
    }

    fclose(file);
}

static void record_import_string(char *raw) {
    size_t len;
    char *value;
    if (!raw) {
        return;
    }
    len = strlen(raw);
    if (len >= 2 && (raw[0] == '"' || raw[0] == '`')) {
        raw[len - 1] = '\0';
        value = raw + 1;
    } else {
        value = raw;
    }
    list_push(&imports, value);
}

void record_lexical_error(const char *text, int line) {
    lexical_errors++;
    fprintf(stderr, "[LEX] %s:%d: неопознанная лексема '%s'\n", current_file, line, text);
}

void yyerror(const char *s) {
    (void)s;
    syntax_errors++;
    fprintf(stderr, "[SYN] %s:%d: синтаксическая ошибка возле '%s'\n",
            current_file, yylineno, yytext ? yytext : "<eof>");
}

static char *trim_in_place(char *line) {
    char *end;
    while (*line && isspace((unsigned char)*line)) {
        line++;
    }
    end = line + strlen(line);
    while (end > line && isspace((unsigned char)end[-1])) {
        *--end = '\0';
    }
    return line;
}

static int is_keyword_text(const char *text) {
    static const char *keywords[] = {
        "break", "default", "func", "interface", "select", "case", "defer",
        "go", "map", "struct", "chan", "else", "goto", "package", "switch",
        "const", "fallthrough", "if", "range", "type", "continue", "for",
        "import", "return", "var", NULL
    };
    int i;
    for (i = 0; keywords[i]; i++) {
        if (strcmp(text, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static int is_identifier_text(const char *text) {
    size_t i;
    if (!(isalpha((unsigned char)text[0]) || text[0] == '_')) {
        return 0;
    }
    for (i = 1; text[i]; i++) {
        if (!(isalnum((unsigned char)text[i]) || text[i] == '_')) {
            return 0;
        }
    }
    return !is_keyword_text(text);
}

static int starts_grouped_decl(const char *text) {
    return (strncmp(text, "const", 5) == 0 && isspace((unsigned char)text[5]) && strchr(text, '(')) ||
           (strncmp(text, "var", 3) == 0 && isspace((unsigned char)text[3]) && strchr(text, '(')) ||
           (strncmp(text, "type", 4) == 0 && isspace((unsigned char)text[4]) && strchr(text, '(')) ||
           (strncmp(text, "import", 6) == 0 && isspace((unsigned char)text[6]) && strchr(text, '('));
}

static int paren_delta(const char *text) {
    int delta = 0;
    int in_string = 0;
    char quote = '\0';
    size_t i;
    for (i = 0; text[i]; i++) {
        if (!in_string && text[i] == '/' && text[i + 1] == '/') {
            break;
        }
        if ((text[i] == '"' || text[i] == '\'') && (i == 0 || text[i - 1] != '\\')) {
            if (!in_string) {
                in_string = 1;
                quote = text[i];
            } else if (quote == text[i]) {
                in_string = 0;
            }
            continue;
        }
        if (in_string) {
            continue;
        }
        if (text[i] == '(') {
            delta++;
        } else if (text[i] == ')') {
            delta--;
        }
    }
    return delta;
}

static int bracket_delta(const char *text) {
    int delta = 0;
    int in_string = 0;
    char quote = '\0';
    size_t i;
    for (i = 0; text[i]; i++) {
        if (!in_string && text[i] == '/' && text[i + 1] == '/') {
            break;
        }
        if ((text[i] == '"' || text[i] == '\'') && (i == 0 || text[i - 1] != '\\')) {
            if (!in_string) {
                in_string = 1;
                quote = text[i];
            } else if (quote == text[i]) {
                in_string = 0;
            }
            continue;
        }
        if (in_string) {
            continue;
        }
        if (text[i] == '[') {
            delta++;
        } else if (text[i] == ']') {
            delta--;
        }
    }
    return delta;
}

static int brace_delta(const char *text) {
    int delta = 0;
    int in_string = 0;
    char quote = '\0';
    size_t i;
    for (i = 0; text[i]; i++) {
        if (!in_string && text[i] == '/' && text[i + 1] == '/') {
            break;
        }
        if ((text[i] == '"' || text[i] == '\'') && (i == 0 || text[i - 1] != '\\')) {
            if (!in_string) {
                in_string = 1;
                quote = text[i];
            } else if (quote == text[i]) {
                in_string = 0;
            }
            continue;
        }
        if (in_string) {
            continue;
        }
        if (text[i] == '{') {
            delta++;
        } else if (text[i] == '}') {
            delta--;
        }
    }
    return delta;
}

static int ends_with_continuation(const char *text) {
    size_t len = strlen(text);
    while (len > 0 && isspace((unsigned char)text[len - 1])) {
        len--;
    }
    if (len == 0) {
        return 0;
    }
    switch (text[len - 1]) {
        case ',':
        case '.':
        case '(':
        case '[':
        case '{':
        case ':':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '&':
        case '|':
        case '^':
        case '!':
        case '=':
        case '<':
        case '>':
            return 1;
        default:
            return 0;
    }
}

static void strip_comments_and_raw_strings(char *text, int *in_block_comment, int *in_raw_string) {
    char *src = text;
    char *dst = text;
    int in_quote = 0;
    char quote = '\0';

    while (*src) {
        if (*in_raw_string) {
            while (*src && *src != '`') {
                src++;
            }
            if (*src == '`') {
                src++;
                *in_raw_string = 0;
                continue;
            }
            break;
        }

        if (*in_block_comment) {
            while (*src && !(src[0] == '*' && src[1] == '/')) {
                src++;
            }
            if (src[0] == '*' && src[1] == '/') {
                src += 2;
                *in_block_comment = 0;
                continue;
            }
            break;
        }

        if (!in_quote && src[0] == '/' && src[1] == '/') {
            break;
        }
        if (!in_quote && src[0] == '/' && src[1] == '*') {
            src += 2;
            *in_block_comment = 1;
            continue;
        }
        if (!in_quote && *src == '`') {
            src++;
            *in_raw_string = 1;
            continue;
        }
        if ((*src == '"' || *src == '\'') && (src == text || src[-1] != '\\')) {
            if (!in_quote) {
                in_quote = 1;
                quote = *src;
            } else if (quote == *src) {
                in_quote = 0;
            }
        }
        *dst++ = *src++;
    }

    *dst = '\0';
}

static void scan_standalone_identifier_lines(const char *path) {
    FILE *file = fopen(path, "r");
    char buffer[4096];
    int line_no = 0;
    int grouped_decl_depth = 0;
    int paren_depth = 0;
    int bracket_depth = 0;
    int brace_depth = 0;
    int continuation = 0;
    int in_block_comment = 0;
    int in_raw_string = 0;

    if (!file) {
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *line;
        line_no++;

        strip_comments_and_raw_strings(buffer, &in_block_comment, &in_raw_string);
        line = trim_in_place(buffer);
        if (*line == '\0') {
            continue;
        }

        if (grouped_decl_depth > 0) {
            grouped_decl_depth += paren_delta(line);
            if (grouped_decl_depth < 0) {
                grouped_decl_depth = 0;
            }
            continuation = grouped_decl_depth > 0 || ends_with_continuation(line);
            continue;
        }

        if (paren_depth > 0 || bracket_depth > 0 || brace_depth > 0 || continuation) {
            paren_depth += paren_delta(line);
            bracket_depth += bracket_delta(line);
            brace_depth += brace_delta(line);
            if (paren_depth < 0) {
                paren_depth = 0;
            }
            if (bracket_depth < 0) {
                bracket_depth = 0;
            }
            if (brace_depth < 0) {
                brace_depth = 0;
            }
            continuation = paren_depth > 0 || bracket_depth > 0 || brace_depth > 0 || ends_with_continuation(line);
            continue;
        }

        if (starts_grouped_decl(line)) {
            grouped_decl_depth = paren_delta(line);
            if (grouped_decl_depth < 1) {
                grouped_decl_depth = 1;
            }
            continuation = grouped_decl_depth > 0 || ends_with_continuation(line);
            continue;
        }

        if (is_identifier_text(line)) {
            syntax_errors++;
            fprintf(stderr,
                    "[SYN] %s:%d: недопустимый оператор '%s' без присваивания, вызова или объявления\n",
                    path, line_no, line);
        }

        paren_depth += paren_delta(line);
        bracket_depth += bracket_delta(line);
        brace_depth += brace_delta(line);
        if (paren_depth < 0) {
            paren_depth = 0;
        }
        if (bracket_depth < 0) {
            bracket_depth = 0;
        }
        if (brace_depth < 0) {
            brace_depth = 0;
        }
        continuation = paren_depth > 0 || bracket_depth > 0 || brace_depth > 0 || ends_with_continuation(line);
    }

    fclose(file);
}

int main(int argc, char **argv) {
    const char *target = argc > 1 ? argv[1] : "test.go";
    StringList files = {0};
    size_t i;

    printf("Запуск анализатора Go\n");
    printf("----------------------------------------\n");
    printf("[INPUT] %s\n", target);

    collect_go_files(target, &files);
    if (files.len == 0) {
        fprintf(stderr, "[ERROR] Не найдено ни одного .go файла по пути %s\n", target);
        return 2;
    }

    for (i = 0; i < files.len; i++) {
        parse_file(files.items[i]);
    }

    printf("\n----------------------------------------\n");
    printf("[SUMMARY] Проверено файлов: %d\n", parsed_files);
    printf("[SUMMARY] Импорты: ");
    if (imports.len == 0) {
        printf("нет\n");
    } else {
        for (i = 0; i < imports.len; i++) {
            printf("%s%s", i ? ", " : "", imports.items[i]);
        }
        printf("\n");
    }
    printf("[SUMMARY] Лексических ошибок: %d\n", lexical_errors);
    printf("[SUMMARY] Синтаксических ошибок: %d\n", syntax_errors);

    printf("\n----------------------------------------\n");
    if (lexical_errors == 0 && syntax_errors == 0) {
        printf("[ИТОГ] SUCCESS: проект лексически корректен, структура файлов распознана.\n");
    } else {
        printf("[ИТОГ] FAILED: проект некорректен. Лексика: %d, синтаксис: %d\n",
               lexical_errors, syntax_errors);
    }

    list_free(&files);
    list_free(&imports);
    return lexical_errors == 0 && syntax_errors == 0 ? 0 : 1;
}
