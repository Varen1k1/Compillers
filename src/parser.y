%define lr.type canonical-lr
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

extern int yylex(void);
extern int line_num;
extern FILE *yyin;
extern char *yytext;

void yyerror(const char *s);

int error_count = 0;
int error_cnt = 0;

typedef struct {
    char *kind;
    char *name;
    int   line;
} Decl;

static Decl decls[4000];
static int  decl_count = 0;

static void add_decl(const char *kind, const char *name, int line) {
    if (decl_count >= 4000) return;
    decls[decl_count].kind = strdup(kind ? kind : "?");
    decls[decl_count].name = strdup(name ? name : "<anon>");
    decls[decl_count].line = line;
    decl_count++;
}

static char **source_lines  = NULL;
static int    source_nlines = 0;

/* Load the file twice: once for the cache, once via yyin for the lexer.
 * Returns 1 on success, 0 if the file is unreadable.
 */
static int load_source_lines(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    int   cap   = 256;
    int   count = 0;
    char **arr  = malloc(cap * sizeof(char *));
    char   buf[8192];

    while (fgets(buf, sizeof(buf), f)) {
        /* strip trailing newline */
        size_t n = strlen(buf);
        while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) buf[--n] = '\0';
        if (count >= cap) {
            cap *= 2;
            arr  = realloc(arr, cap * sizeof(char *));
        }
        arr[count++] = strdup(buf);
    }
    fclose(f);

    source_lines  = arr;
    source_nlines = count;
    return 1;
}

/* Print the cached line for the current error. Used by both yyerror() and
 * the lexer's catch-all rule, hence non-static.
 */
void print_source_line(int line) {
    if (line < 1 || line > source_nlines) return;
    fprintf(stderr, "    | %s\n", source_lines[line - 1]);
}
%}

%union {
    char *str;
}

%token <str> IDENTIFIER SOFT_KW STRING_LIT INT_LIT REAL_LIT CHAR_LIT BOOL_LIT
%token NL NULL_LIT
%token PACKAGE IMPORT CLASS INTERFACE OBJECT FUN VAL VAR
%token IF ELSE WHEN FOR WHILE DO RETURN BREAK CONTINUE THROW TRY CATCH FINALLY
%token THIS SUPER IN NOT_IN IS NOT_IS AS AS_SAFE TYPEALIAS ENUM
%token INIT CONSTRUCTOR BY GET SET
%token EQEQEQ NEQEQ EQEQ NEQ LEQ GEQ ANDAND OROR INCR DECR
%token PLUS_EQ MINUS_EQ STAR_EQ SLASH_EQ MOD_EQ
%token RANGE RANGE_UNTIL ARROW SAFE_DOT ELVIS COLONCOLON DBL_EXCL

%type <str> identifier qualifiedName

%right '=' PLUS_EQ MINUS_EQ STAR_EQ SLASH_EQ MOD_EQ
%right ARROW
%left  OROR
%left  ANDAND
%left  EQEQ NEQ EQEQEQ NEQEQ
%left  '<' '>' LEQ GEQ
%nonassoc IN NOT_IN IS NOT_IS
%right ELVIS
%left INFIX_FN
%nonassoc RANGE RANGE_UNTIL
%left  '+' '-'
%left  '*' '/' '%'
%nonassoc AS AS_SAFE
%right '!' UMINUS UPLUS
%right INCR DECR
%left  '.' SAFE_DOT
%left  COLONCOLON
%nonassoc DBL_EXCL
%left  '(' '['
%nonassoc THEN
%nonassoc ELSE

%start file

%%

/*==============*\
| File top level |
\*==============*/

file
    : opt_seps
    | opt_seps topItems opt_seps
    ;

opt_seps : /* empty */ | seps ;

seps
    : sep
    | seps sep
    ;
sep : NL | ';' ;

topItems
    : topItem
    | topItems seps topItem
    | topItems error sep
        { yyerrok;   /* error already counted by yyerror; this is just recovery */
          fprintf(stderr, "         (recovered at top level around line %d)\n", line_num); }
    ;

topItem
    : packageDecl
    | importDecl
    | declaration
    ;

/*================*\
| Package / import |
\*================*/

packageDecl
    : PACKAGE qualifiedName
        { printf("[Line %d] Package: %s\n", line_num, $2); free($2); }
    ;

importDecl
    : IMPORT qualifiedName
        { printf("[Line %d] Import:  %s\n", line_num, $2); free($2); }
    | IMPORT qualifiedName '.' '*'
        { printf("[Line %d] Import:  %s.*\n", line_num, $2); free($2); }
    | IMPORT qualifiedName AS identifier
        { printf("[Line %d] Import:  %s as %s\n", line_num, $2, $4); free($2); free($4); }
    ;

qualifiedName
    : identifier                       { $$ = $1; }
    | qualifiedName '.' identifier
        { char *r = malloc(strlen($1)+strlen($3)+2);
          sprintf(r, "%s.%s", $1, $3);
          free($1); free($3); $$ = r; }
    ;

  /*
   * 'identifier' covers any context where the token can be used as a name.
   * Includes IDENTIFIER, SOFT_KW, and the hard keywords that doubled as
   * soft keywords in earlier versions (init/constructor/by) so users can
   * still write `val constructor = ...` or `val init = ...`.
   */
identifier
    : IDENTIFIER     { $$ = $1; }
    | SOFT_KW        { $$ = $1; }
    | CONSTRUCTOR    { $$ = strdup("constructor"); }
    | INIT           { $$ = strdup("init"); }
    | BY             { $$ = strdup("by"); }
    | GET            { $$ = strdup("get"); }
    | SET            { $$ = strdup("set"); }
    ;

/*============*\
| Declarations |
\*============*/

declaration
    : classDecl
    | objectDecl
    | funDecl
    | propDecl
    | typeAliasDecl
    ;

modifiers
    : /* empty */
    | modifiers modifierItem
    ;

modifierItem
    : SOFT_KW
    | ENUM
    | annotation
    ;

annotation
    : '@' identifier
    | '@' identifier '(' opt_args ')'
    | '@' SOFT_KW ':' identifier
    | '@' SOFT_KW ':' identifier '(' opt_args ')'
    ;

classDecl
    : modifiers opt_seps CLASS IDENTIFIER opt_typeParams opt_primCtor opt_supertypes opt_whereClause opt_classBody
        { printf("[Line %d] Class:     %s\n", line_num, $4); add_decl("class", $4, line_num); free($4); }
    | modifiers opt_seps INTERFACE IDENTIFIER opt_typeParams opt_supertypes opt_whereClause opt_classBody
        { printf("[Line %d] Interface: %s\n", line_num, $4); add_decl("interface", $4, line_num); free($4); }
    ;

objectDecl
    : modifiers opt_seps OBJECT IDENTIFIER opt_supertypes opt_classBody
        { printf("[Line %d] Object:    %s\n", line_num, $4); add_decl("object", $4, line_num); free($4); }
    | modifiers opt_seps OBJECT opt_supertypes opt_classBody     /* unnamed (e.g. companion object) */
        { printf("[Line %d] Object:    <anonymous>\n", line_num); add_decl("object", "<anon>", line_num); }
    ;

opt_typeParams
    : /* empty */
    | '<' typeParamList '>'
    ;

typeParamList
    : typeParam
    | typeParamList ',' typeParam
    ;

typeParam
    : modifiers opt_seps identifier            { free($3); }
    | modifiers opt_seps identifier ':' type   { free($3); }
    ;

opt_primCtor
    : /* empty */
    | '(' ')'
    | '(' ctorParamList opt_comma ')'
    | modifiers opt_seps CONSTRUCTOR '(' ')'
    | modifiers opt_seps CONSTRUCTOR '(' ctorParamList opt_comma ')'
    ;

opt_comma : /* empty */ | ',' ;

ctorParamList
    : ctorParam
    | ctorParamList ',' ctorParam
    ;

ctorParam
    : modifiers opt_seps identifier ':' type                    { free($3); }
    | modifiers opt_seps identifier ':' type '=' expr           { free($3); }
    | modifiers opt_seps VAL identifier ':' type                { free($4); }
    | modifiers opt_seps VAR identifier ':' type                { free($4); }
    | modifiers opt_seps VAL identifier ':' type '=' expr       { free($4); }
    | modifiers opt_seps VAR identifier ':' type '=' expr       { free($4); }
    ;

opt_supertypes
    : /* empty */
    | ':' supertypeList
    ;

supertypeList
    : supertype
    | supertypeList ',' supertype
    ;

supertype
    : type
    | type '(' opt_args ')'
    | type BY expr           /* "X by delegate" */
    ;

opt_classBody
    : /* empty */
    | classBody
    ;

classBody
    : '{' opt_seps '}'
    | '{' opt_seps members opt_seps '}'
    ;

members
    : member
    | members seps member
    | members error sep
        { yyerrok;   /* error already counted by yyerror; this is just recovery */
          fprintf(stderr, "         (recovered in class body around line %d)\n", line_num); }
    ;

member
    : declaration
    | initBlock
    | accessor
    | secondaryCtor
    | enumEntries
    ;

initBlock
    : INIT block                                            /* "init { ... }" - INIT is a hard keyword now */
    ;

secondaryCtor
    : modifiers opt_seps CONSTRUCTOR '(' opt_ctorParams ')' opt_ctorDelegation opt_funBody  /* CONSTRUCTOR is hard kw */
    ;
opt_ctorParams
    : /* empty */
    | ctorParamList
    ;
opt_ctorDelegation
    : /* empty */
    | ':' THIS '(' opt_args ')'
    | ':' SUPER '(' opt_args ')'
    ;

enumEntries
    : enumEntry
    | enumEntries ',' opt_seps enumEntry          /* allow newline after comma */
    ;

enumEntry
    : modifiers opt_seps IDENTIFIER                              { free($3); }
    | modifiers opt_seps IDENTIFIER '(' opt_args ')'             { free($3); }
    | modifiers opt_seps IDENTIFIER '(' opt_args ')' classBody   { free($3); }
    | modifiers opt_seps IDENTIFIER classBody                    { free($3); }
    ;

funDecl
    : modifiers opt_seps FUN opt_typeParams funHead '(' opt_paramList opt_comma ')' opt_retType opt_whereClause opt_funBody
        { printf("[Line %d] Function declared\n", line_num); add_decl("fun", "<fn>", line_num); }
    ;

funHead
    : identifier                                          { free($1); }
    | funHead '.' identifier                              { free($3); }
    | funHead '<' typeArgList opt_comma '>'
    | funHead '?'
    ;

opt_paramList
    : /* empty */
    | paramList
    ;

paramList
    : param
    | paramList ',' param
    ;

param
    : modifiers opt_seps identifier ':' type                  { free($3); }
    | modifiers opt_seps identifier ':' type '=' expr         { free($3); }
    ;

opt_retType
    : /* empty */
    | ':' type
    ;

opt_whereClause
    : /* empty */
    | SOFT_KW typeConstraintList   /* "where" */
    ;

typeConstraintList
    : typeConstraint
    | typeConstraintList ',' typeConstraint
    ;

typeConstraint
    : identifier ':' type   { free($1); }
    ;

opt_funBody
    : /* empty */
    | block
    | '=' expr
    ;

propDecl
    : modifiers opt_seps VAL declTarget opt_init opt_accessors
        { printf("[Line %d] Val\n", line_num); add_decl("val", "<val>", line_num); }
    | modifiers opt_seps VAR declTarget opt_init opt_accessors
        { printf("[Line %d] Var\n", line_num); add_decl("var", "<var>", line_num); }
    ;

declTarget
    : identifier                            { free($1); }
    | identifier ':' type                   { free($1); }
    | '(' destructList ')'
    | '(' destructList ')' ':' type
    ;

destructList
    : identifier                            { free($1); }
    | identifier ':' type                   { free($1); }
    | destructList ',' identifier           { free($3); }
    | destructList ',' identifier ':' type  { free($3); }
    ;

opt_init
    : /* empty */
    | '=' expr
    | BY expr
    ;

opt_accessors
    : /* empty */
    | accessor
    | accessor accessor
    ;

accessor
    : GET '(' ')' opt_retType opt_funBody
    | SET '(' identifier ')' opt_funBody                { free($3); }
    | SET '(' identifier ':' type ')' opt_funBody       { free($3); }
    | GET                                                /* short form: `val x get() = ...` — not really common, but parsed */
    | SET                                                /* analogous */
    ;

typeAliasDecl
    : modifiers opt_seps TYPEALIAS identifier opt_typeParams '=' type
        { printf("[Line %d] Typealias: %s\n", line_num, $4); add_decl("typealias", $4, line_num); free($4); }
    ;

/*========*\
|   Types  |
\*========*/
type
    : typeRef
    | typeRef '?'
    | '(' opt_typeArgList opt_comma ')' ARROW type    /* function type */
    | typeRef '.' '(' opt_typeArgList opt_comma ')' ARROW type
    ;

typeRef
    : qualifiedName { free($1); }
    | qualifiedName '<' typeArgList opt_comma '>' { free($1); }
    | typeRef '.' identifier { free($3); }
    | typeRef '.' identifier '<' typeArgList opt_comma '>' { free($3); }
    ;

opt_typeArgList
    : /* empty */
    | typeArgList
    ;

typeArgList
    : typeArgItem
    | typeArgList ',' typeArgItem
    ;

typeArgItem
    : type
    | '*'
    | SOFT_KW type    /* "out T" or "in T" - SOFT_KW is "out" */
    | IN type
    ;

/*==================*\
| Block / statements |
\*==================*/

block
    : '{' opt_seps '}'
    | '{' opt_seps stmts opt_seps '}'
    ;

stmts
    : stmt
    | stmts seps stmt
    | stmts error sep
        { yyerrok;
          fprintf(stderr, "         (recovered in block around line %d)\n", line_num); }
    ;

stmt
    : declaration
    | expr
    | expr '=' expr
    | expr PLUS_EQ expr
    | expr MINUS_EQ expr
    | expr STAR_EQ expr
    | expr SLASH_EQ expr
    | expr MOD_EQ expr
    | forStmt
    | whileStmt
    | doWhileStmt
    | labelStmt
    ;

labelStmt
    : IDENTIFIER '@' stmt { free($1); }
    ;

forStmt
    : FOR '(' forVar IN expr ')' stmt
    | FOR '(' forVar IN expr ')' ';'
    ;

forVar
    : modifiers opt_seps identifier { free($3); }
    | modifiers opt_seps identifier ':' type { free($3); }
    | '(' destructList ')'
    ;

whileStmt
    : WHILE '(' expr ')' stmt
    | WHILE '(' expr ')' ';'
    ;

doWhileStmt
    : DO stmt WHILE '(' expr ')'
    ;

/* ============================================================== */
/* Expressions                                                     */
/* ============================================================== */

expr
    : expr OROR expr
    | expr ANDAND expr
    | expr EQEQ expr
    | expr NEQ expr
    | expr EQEQEQ expr
    | expr NEQEQ expr
    | expr '<' expr
    | expr '>' expr
    | expr LEQ expr
    | expr GEQ expr
    | expr IN expr
    | expr NOT_IN expr
    | expr IS type
    | expr NOT_IS type
    | expr AS type
    | expr AS_SAFE type
    | expr RANGE expr
    | expr RANGE_UNTIL expr
    | expr ELVIS expr
    | expr IDENTIFIER expr  %prec INFIX_FN
    | expr SOFT_KW expr     %prec INFIX_FN
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | '-' expr %prec UMINUS
    | '+' expr %prec UPLUS
    | '!' expr
    | INCR expr
    | DECR expr
    | expr INCR
    | expr DECR
    | expr DBL_EXCL
    | expr '.' identifier           { free($3); }
    | expr SAFE_DOT identifier      { free($3); }
    | expr COLONCOLON identifier    { free($3); }
    | expr COLONCOLON CLASS
    | expr '(' opt_args ')'
    | expr '(' opt_args ')' lambda
    | expr lambda
    | expr '[' argList ']'
    | primary
    ;

primary
    : INT_LIT                                    { free($1); }
    | REAL_LIT                                   { free($1); }
    | STRING_LIT                                 { free($1); }
    | CHAR_LIT                                   { free($1); }
    | BOOL_LIT                                   { free($1); }
    | NULL_LIT
    | identifier                                 { free($1); }
    | THIS
    | THIS '@' identifier                        { free($3); }
    | SUPER
    | SUPER '@' identifier                       { free($3); }
    | SUPER '<' type '>'
    | '(' expr ')'
    | lambda
    | ifExpr
    | whenExpr
    | tryExpr
    | objectLit
    | COLONCOLON identifier                      { free($2); }
    | COLONCOLON CLASS
    | jumpExpr                                   /* break/continue/return/throw as expressions */
    ;

  /* jump-expressions usable anywhere an expression is allowed */
jumpExpr
    : RETURN                                  %prec UMINUS
    | RETURN expr                             %prec UMINUS
    | RETURN '@' identifier                   %prec UMINUS  { free($3); }
    | RETURN '@' identifier expr              %prec UMINUS  { free($3); }
    | BREAK
    | CONTINUE
    | BREAK '@' identifier                                  { free($3); }
    | CONTINUE '@' identifier                               { free($3); }
    | THROW expr                              %prec UMINUS
    ;

/* lambdas: either statements only, or "params -> stmts" */
lambda
    : '{' opt_seps '}'
    | '{' opt_seps stmts opt_seps '}'
    | '{' opt_seps lambdaParamList ARROW opt_seps '}'
    | '{' opt_seps lambdaParamList ARROW opt_seps stmts opt_seps '}'
    | '{' opt_seps ARROW opt_seps '}'
    | '{' opt_seps ARROW opt_seps stmts opt_seps '}'
    ;

lambdaParamList
    : lambdaParam
    | lambdaParamList ',' lambdaParam
    ;

lambdaParam
    : IDENTIFIER                               { free($1); }
    | IDENTIFIER ':' type                      { free($1); }
    | '(' destructList ')'
    | '_'      /* underscore is just IDENTIFIER, kept here for documentation */
    ;

ifExpr
    : IF '(' expr ')' expr                  %prec THEN
    | IF '(' expr ')' expr ELSE expr
    ;

whenExpr
    : WHEN '{' opt_seps '}'
    | WHEN '{' opt_seps whenEntries opt_seps '}'
    | WHEN '(' expr ')' '{' opt_seps '}'
    | WHEN '(' expr ')' '{' opt_seps whenEntries opt_seps '}'
    | WHEN '(' VAL identifier '=' expr ')' '{' opt_seps whenEntries opt_seps '}'              { free($4); }
    | WHEN '(' VAL identifier ':' type '=' expr ')' '{' opt_seps whenEntries opt_seps '}'     { free($4); }
    ;

whenEntries
    : whenEntry
    | whenEntries seps whenEntry
    ;

whenEntry
    : whenCondList ARROW stmt
    | ELSE ARROW stmt
    ;

whenCondList
    : whenCond
    | whenCondList ',' whenCond
    ;

whenCond
    : expr
    | IN expr
    | NOT_IN expr
    | IS type
    | NOT_IS type
    ;

tryExpr
    : TRY block catchList
    | TRY block catchList FINALLY block
    | TRY block FINALLY block
    ;

catchList
    : catchClause
    | catchList catchClause
    ;

catchClause
    : CATCH '(' opt_modifiers identifier ':' type ')' block   { free($4); }
    ;

opt_modifiers
    : /* empty */
    | modifiers opt_seps modifierItem    /* at least one */
    ;

objectLit
    : OBJECT opt_supertypes classBody
    ;

opt_args
    : /* empty */
    | argList opt_seps
    ;

argList
    : arg
    | argList ',' arg
    ;

arg
    : expr
    | identifier '=' expr   { free($1); }
    | '*' expr
    ;

%%

void yyerror(const char *s) {
    error_cnt++;
    fprintf(stderr, "[Error #%d] line %d: %s (near '%s')\n",
            error_cnt, line_num, s, yytext ? yytext : "?");
    print_source_line(line_num);
    fflush(stderr);
}

int process_single_file(const char *path) {
    yyin = fopen(path, "r");
    error_cnt = 0;
    if (!yyin) {
        perror(path);
        return -1;
    }
    load_source_lines(path);
    
    line_num = 1;  /* reset line number for new file */
    printf("\n--- File: %s ---\n", path);
    int rc = yyparse();

    printf("\n  Declarations: %d | Errors: %d\n", decl_count, error_cnt);
    if (decl_count > 0) {
        for (int i = 0; i < decl_count; i++) {
            printf("    line %4d  %-10s  %s\n",
                   decls[i].line, decls[i].kind, decls[i].name);
        }
    }

    fclose(yyin);
    decl_count = 0;
    return error_cnt;
}

static void process_directory_recursively(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror(dir_path);
        return;
    }

    struct dirent *entry;
    struct stat st;
    char full_path[4096];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        if (stat(full_path, &st) == -1) {
            perror(full_path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            process_directory_recursively(full_path);
        } else if (S_ISREG(st.st_mode)) {
            const char *dot = strrchr(entry->d_name, '.');
            if (dot && strcmp(dot, ".kt") == 0) {
                error_cnt += process_single_file(full_path);
            }
        }
    }

    closedir(dir);
}

static const char *banner =
"========================================\n"
"Kotlin Validator - starting analysis\n"
"========================================\n";

int main(int argc, char **argv) {
    const char *path = NULL;
    struct stat st;
    
    if (argc > 1) {
        path = argv[1];
        
        /* Check if path is a directory or a file */
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
            /* Directory: process recursively */
            fputs(banner, stdout);
            printf("Source directory: %s\n", path);
            fputc('\n', stdout);
            process_directory_recursively(path);
            printf("\n========================================\n");
            printf("Analysis complete.\n");
            printf("========================================\n");
        } else {
            /* File: process as before */
            yyin = fopen(path, "r");
            if (!yyin) { perror(path); return 2; }
            load_source_lines(path);
        }
    } else {
        yyin = stdin;
    }

    printf("\n========================================\n");
    if (error_count == 0) {
        printf("Result: SUCCESS - file is valid Kotlin code.\n");
    } else {
        printf("Result: FAILURE - file contains %d error(s).\n", error_count);
    }
    printf("========================================\n");

    return (error_count == 0) ? 0 : 1;
}
