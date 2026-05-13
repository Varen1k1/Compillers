/*
 * Kotlin validator grammar (Bison, LALR(1)).
 *
 * Strategy: parse declarations strictly (package/import/class/object/
 * interface/fun/val/var/typealias), parse statement and expression bodies
 * permissively. Soft keywords (open, final, private, get, set, init, by,
 * ...) all arrive as a single SOFT_KW token, so the grammar doesn't have
 * to enumerate every keyword in every modifier slot.
 *
 * The parser reports lexical errors (from the lexer) and syntax errors
 * (from yyerror), recovers via the standard 'error' token, and continues
 * - per the project spec it must NOT abort on the first error.
 */
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int yylex(void);
extern int line_num;
extern FILE *yyin;
extern char *yytext;

void yyerror(const char *s);

int error_count = 0;

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

/* Source line cache, populated once in main() so yyerror() can echo the
 * offending line back to the user. Keeps errors anchored to real code.
 */
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

  /* operator precedence, lowest first - matches Kotlin's grammar reference */
%right '=' PLUS_EQ MINUS_EQ STAR_EQ SLASH_EQ MOD_EQ
%right ARROW
%left  OROR
%left  ANDAND
%left  EQEQ NEQ EQEQEQ NEQEQ
%left  '<' '>' LEQ GEQ
%nonassoc IN NOT_IN IS NOT_IS
%right ELVIS
%left  INFIX_FN                              /* infix function call: a foo b */
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

/* ============================================================== */
/* File top level                                                  */
/* ============================================================== */

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

/* ============================================================== */
/* Package / import                                                */
/* ============================================================== */

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

/* ============================================================== */
/* Declarations                                                    */
/* ============================================================== */

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
    : modifiers CLASS IDENTIFIER opt_typeParams opt_primCtor opt_supertypes opt_whereClause opt_classBody
        { printf("[Line %d] Class:     %s\n", line_num, $3); add_decl("class", $3, line_num); free($3); }
    | modifiers INTERFACE IDENTIFIER opt_typeParams opt_supertypes opt_whereClause opt_classBody
        { printf("[Line %d] Interface: %s\n", line_num, $3); add_decl("interface", $3, line_num); free($3); }
    ;

objectDecl
    : modifiers OBJECT IDENTIFIER opt_supertypes opt_classBody
        { printf("[Line %d] Object:    %s\n", line_num, $3); add_decl("object", $3, line_num); free($3); }
    | modifiers OBJECT opt_supertypes opt_classBody     /* unnamed (e.g. companion object) */
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
    : modifiers identifier            { free($2); }
    | modifiers identifier ':' type   { free($2); }
    ;

opt_primCtor
    : /* empty */
    | '(' ')'
    | '(' ctorParamList opt_comma ')'
    | modifiers CONSTRUCTOR '(' ')'
    | modifiers CONSTRUCTOR '(' ctorParamList opt_comma ')'
    ;

opt_comma : /* empty */ | ',' ;

ctorParamList
    : ctorParam
    | ctorParamList ',' ctorParam
    ;

ctorParam
    : modifiers identifier ':' type                    { free($2); }
    | modifiers identifier ':' type '=' expr           { free($2); }
    | modifiers VAL identifier ':' type                { free($3); }
    | modifiers VAR identifier ':' type                { free($3); }
    | modifiers VAL identifier ':' type '=' expr       { free($3); }
    | modifiers VAR identifier ':' type '=' expr       { free($3); }
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

  /* Accessor IS a member - now that get/set are dedicated GET/SET tokens
   * (not SOFT_KW), accessor-as-member doesn't conflict with modifier-
   * extending-with-SOFT_KW.
   */
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
    : modifiers CONSTRUCTOR '(' opt_ctorParams ')' opt_ctorDelegation opt_funBody  /* CONSTRUCTOR is hard kw */
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

  /* enum entries: only IDENTIFIER (not soft keywords) - so SOFT_KW
   * doesn't reduce to identifier here and conflict with accessor/initBlock.
   */
enumEntry
    : modifiers IDENTIFIER                              { free($2); }
    | modifiers IDENTIFIER '(' opt_args ')'             { free($2); }
    | modifiers IDENTIFIER '(' opt_args ')' classBody   { free($2); }
    | modifiers IDENTIFIER classBody                    { free($2); }
    ;

funDecl
    : modifiers FUN opt_typeParams funHead '(' opt_paramList opt_comma ')' opt_retType opt_whereClause opt_funBody
        { printf("[Line %d] Function declared\n", line_num); add_decl("fun", "<fn>", line_num); }
    ;

  /* funHead absorbs both 'name' and 'receiverType.name' and 'A<T>.name'.
   * The last identifier is the function name; the rest (if any) is the
   * receiver type. We don't separate them for validation purposes.
   */
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
    : modifiers identifier ':' type                  { free($2); }
    | modifiers identifier ':' type '=' expr         { free($2); }
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
    : modifiers VAL declTarget opt_init opt_accessors
        { printf("[Line %d] Val\n", line_num); add_decl("val", "<val>", line_num); }
    | modifiers VAR declTarget opt_init opt_accessors
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
    | BY expr          /* "by delegate" - BY is a hard keyword now */
    ;

opt_accessors
    : /* empty */
    | accessor
    | accessor accessor
    ;

  /* accessor: get/set declaration. GET/SET are dedicated hard keywords. */
accessor
    : GET '(' ')' opt_retType opt_funBody
    | SET '(' identifier ')' opt_funBody                { free($3); }
    | SET '(' identifier ':' type ')' opt_funBody       { free($3); }
    | GET                                                /* short form: `val x get() = ...` — not really common, but parsed */
    | SET                                                /* analogous */
    ;

typeAliasDecl
    : modifiers TYPEALIAS identifier opt_typeParams '=' type
        { printf("[Line %d] Typealias: %s\n", line_num, $3); add_decl("typealias", $3, line_num); free($3); }
    ;

/* ============================================================== */
/* Types                                                           */
/* ============================================================== */

  /* Note: standalone parenthesized type `(T)` is intentionally not a rule
   * because it overlaps with the function-type prefix `(T1, T2) -> R` and
   * LALR can't disambiguate until it sees ARROW (or its absence). The
   * shift-reduce here defaults to shift, so function types win.
   * In Kotlin the parenthesized form is rare and can usually be omitted.
   */
type
    : typeRef
    | typeRef '?'
    | '(' opt_typeArgList opt_comma ')' ARROW type    /* function type */
    | typeRef '.' '(' opt_typeArgList opt_comma ')' ARROW type
    ;

typeRef
    : qualifiedName                          { free($1); }
    | qualifiedName '<' typeArgList opt_comma '>'   { free($1); }
    | typeRef '.' identifier                 { free($3); }
    | typeRef '.' identifier '<' typeArgList opt_comma '>'  { free($3); }
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

/* ============================================================== */
/* Block / statements                                              */
/* ============================================================== */

block
    : '{' opt_seps '}'
    | '{' opt_seps stmts opt_seps '}'
    ;

stmts
    : stmt
    | stmts seps stmt
    | stmts error sep
        { yyerrok;   /* error already counted by yyerror; this is just recovery */
          fprintf(stderr, "         (recovered in block around line %d)\n", line_num); }
    ;

  /* stmt level: declarations, control flow, assignments, and expressions.
   * RETURN/BREAK/CONTINUE/THROW were moved to primary so they're usable
   * inside expressions like `if (x) continue` and `if (x) return v`.
   */
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
    : IDENTIFIER '@' stmt        { free($1); }
    ;

forStmt
    : FOR '(' forVar IN expr ')' stmt
    | FOR '(' forVar IN expr ')' ';'
    ;

forVar
    : modifiers identifier                  { free($2); }
    | modifiers identifier ':' type         { free($2); }
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
    | expr IDENTIFIER expr  %prec INFIX_FN              /* infix function call */
    | expr SOFT_KW expr     %prec INFIX_FN              /* infix using soft keyword name */
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
    | expr '.' identifier                           { free($3); }
    | expr SAFE_DOT identifier                      { free($3); }
    | expr COLONCOLON identifier                    { free($3); }
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
    | modifiers modifierItem    /* at least one */
    ;

objectLit
    : OBJECT opt_supertypes classBody
    ;

opt_args
    : /* empty */
    | argList opt_comma
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
    error_count++;
    fprintf(stderr, "[Error #%d] line %d: %s (near '%s')\n",
            error_count, line_num, s, yytext ? yytext : "?");
    print_source_line(line_num);
    fflush(stderr);
}

static const char *banner =
"========================================\n"
"Kotlin Validator - starting analysis\n"
"========================================\n";

int main(int argc, char **argv) {
    const char *path = NULL;
    if (argc > 1) {
        path = argv[1];
        yyin = fopen(path, "r");
        if (!yyin) { perror(path); return 2; }
        /* second open is for the source-line cache (yyin is consumed by the lexer) */
        load_source_lines(path);
    } else {
        yyin = stdin;
    }

    fputs(banner, stdout);
    if (path) printf("Source: %s\n", path);
    fputc('\n', stdout);

    int rc = yyparse();

    printf("\n========================================\n");
    printf("Analysis Report\n");
    printf("========================================\n");
    printf("Declarations found: %d\n", decl_count);
    printf("Errors reported:    %d\n", error_count);

    if (decl_count > 0) {
        printf("\nDeclarations:\n");
        for (int i = 0; i < decl_count; i++) {
            printf("  line %4d  %-10s  %s\n",
                   decls[i].line, decls[i].kind, decls[i].name);
        }
    }

    printf("\n========================================\n");
    if (rc == 0 && error_count == 0) {
        printf("Result: SUCCESS - file is valid Kotlin code.\n");
    } else {
        printf("Result: FAILURE - file contains %d error(s).\n", error_count);
    }
    printf("========================================\n");

    return (rc == 0 && error_count == 0) ? 0 : 1;
}
