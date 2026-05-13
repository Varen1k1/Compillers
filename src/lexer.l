/*
 * Kotlin lexer (Flex). Returns tokens consumed by src/parser.y.
 *
 * Key trick borrowed from the Go validator in go/lexer.l:
 *   newlines are emitted as the NL token only when the previous token
 *   could legally END a statement (identifier, literal, ')', ']', '}',
 *   '!!', 'return', etc.). After an operator or an opening bracket the
 *   newline is whitespace. This eliminates spurious NL-in-the-middle-of-
 *   an-expression ambiguities that crippled the earlier grammar.
 *
 * Lexical errors are reported but never abort the scan.
 */
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"

int line_num = 1;
int col_num  = 1;

/* shared with the parser: error count and source-line cache (for nice errors) */
extern int error_count;
extern void print_source_line(int line);

/* depth tracking suppresses NL-as-separator inside parens/brackets */
static int paren_depth   = 0;
static int bracket_depth = 0;

/* set by emit_token() to remember whether the previous token can end a stmt */
static int last_can_end_stmt = 0;

static void track_text(const char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] == '\n') { line_num++; col_num = 1; }
        else              { col_num++; }
    }
}

static int token_can_end_stmt(int tok) {
    switch (tok) {
        case IDENTIFIER:
        case SOFT_KW:
        case STRING_LIT:
        case INT_LIT:
        case REAL_LIT:
        case CHAR_LIT:
        case BOOL_LIT:
        case NULL_LIT:
        case THIS:
        case SUPER:
        case RETURN:
        case BREAK:
        case CONTINUE:
        case INCR:
        case DECR:
        case DBL_EXCL:
        case ')':
        case ']':
        case '}':
        case '*':   /* covers `import foo.*` where the trailing `*` ends the stmt */
        case '>':   /* covers `class Foo<T>` */
            return 1;
        default:
            return 0;
    }
}

static int emit(int tok) {
    last_can_end_stmt = token_can_end_stmt(tok);
    return tok;
}
%}

%option noyywrap
%option nounput
%option noinput

%x BLOCK_COMMENT
%x TRIPLE_STR

DIGIT   [0-9]
HEX     [0-9a-fA-F]
BIN     [01]
LETTER  [a-zA-Z_]
IDENT   {LETTER}({LETTER}|{DIGIT})*

%%

  /* whitespace */
[ \t\r]+        { col_num += yyleng; }

  /* newlines: only become NL tokens when they actually end a statement */
\n              {
    line_num++; col_num = 1;
    if (last_can_end_stmt && paren_depth == 0 && bracket_depth == 0) {
        last_can_end_stmt = 0;
        return NL;
    }
}

  /* line and block comments (block comments may span lines) */
"//"[^\n]*      { col_num += yyleng; }
"/*"            { col_num += 2; BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>{
    [^*\n]+     { col_num += yyleng; }
    "*"+[^*/\n]* { col_num += yyleng; }
    "*"+"/"     { col_num += yyleng; BEGIN(INITIAL); }
    \n          { line_num++; col_num = 1; }
}

  /* triple-quoted strings - opaque content */
"\"\"\""        { col_num += 3; BEGIN(TRIPLE_STR); }
<TRIPLE_STR>{
    "\"\"\""    { col_num += 3; yylval.str = strdup("\"\"\"...\"\"\""); BEGIN(INITIAL); return emit(STRING_LIT); }
    \n          { line_num++; col_num = 1; }
    .           { col_num++; }
}

  /* hard keywords */
"package"       { track_text(yytext); return emit(PACKAGE); }
"import"        { track_text(yytext); return emit(IMPORT); }
"class"         { track_text(yytext); return emit(CLASS); }
"interface"     { track_text(yytext); return emit(INTERFACE); }
"object"        { track_text(yytext); return emit(OBJECT); }
"fun"           { track_text(yytext); return emit(FUN); }
"val"           { track_text(yytext); return emit(VAL); }
"var"           { track_text(yytext); return emit(VAR); }
"if"            { track_text(yytext); return emit(IF); }
"else"          { track_text(yytext); return emit(ELSE); }
"when"          { track_text(yytext); return emit(WHEN); }
"for"           { track_text(yytext); return emit(FOR); }
"while"         { track_text(yytext); return emit(WHILE); }
"do"            { track_text(yytext); return emit(DO); }
"return"        { track_text(yytext); return emit(RETURN); }
"break"         { track_text(yytext); return emit(BREAK); }
"continue"      { track_text(yytext); return emit(CONTINUE); }
"throw"         { track_text(yytext); return emit(THROW); }
"try"           { track_text(yytext); return emit(TRY); }
"catch"         { track_text(yytext); return emit(CATCH); }
"finally"       { track_text(yytext); return emit(FINALLY); }
"this"          { track_text(yytext); return emit(THIS); }
"super"         { track_text(yytext); return emit(SUPER); }
"in"            { track_text(yytext); return emit(IN); }
"!in"           { track_text(yytext); return emit(NOT_IN); }
"is"            { track_text(yytext); return emit(IS); }
"!is"           { track_text(yytext); return emit(NOT_IS); }
"as"            { track_text(yytext); return emit(AS); }
"as?"           { track_text(yytext); return emit(AS_SAFE); }
"typealias"     { track_text(yytext); return emit(TYPEALIAS); }
"enum"          { track_text(yytext); return emit(ENUM); }
"init"          { track_text(yytext); return emit(INIT); }
"constructor"   { track_text(yytext); return emit(CONSTRUCTOR); }
"by"            { track_text(yytext); return emit(BY); }
"get"           { track_text(yytext); return emit(GET); }
"set"           { track_text(yytext); return emit(SET); }
"true"          { track_text(yytext); yylval.str = strdup("true");  return emit(BOOL_LIT); }
"false"         { track_text(yytext); yylval.str = strdup("false"); return emit(BOOL_LIT); }
"null"          { track_text(yytext); return emit(NULL_LIT); }

  /* soft keywords: all returned as the single SOFT_KW token so the
   * grammar doesn't have to enumerate every soft keyword in every slot.
   */
"open"|"final"|"abstract"|"override"|"private"|"public"|"protected"|"internal"|"sealed"|"data"|"inline"|"infix"|"operator"|"suspend"|"tailrec"|"external"|"const"|"lateinit"|"companion"|"where"|"out"|"vararg"|"reified"|"crossinline"|"noinline"|"inner"|"annotation"|"value"|"expect"|"actual"|"field"|"property"|"receiver"|"param"|"setparam"|"delegate"|"file"|"dynamic"   { track_text(yytext); yylval.str = strdup(yytext); return emit(SOFT_KW); }

  /* multi-character operators (longest match first) */
"==="           { col_num += 3; return emit(EQEQEQ); }
"!=="           { col_num += 3; return emit(NEQEQ); }
"=="            { col_num += 2; return emit(EQEQ); }
"!="            { col_num += 2; return emit(NEQ); }
"<="            { col_num += 2; return emit(LEQ); }
">="            { col_num += 2; return emit(GEQ); }
"&&"            { col_num += 2; return emit(ANDAND); }
"||"            { col_num += 2; return emit(OROR); }
"++"            { col_num += 2; return emit(INCR); }
"--"            { col_num += 2; return emit(DECR); }
"+="            { col_num += 2; return emit(PLUS_EQ); }
"-="            { col_num += 2; return emit(MINUS_EQ); }
"*="            { col_num += 2; return emit(STAR_EQ); }
"/="            { col_num += 2; return emit(SLASH_EQ); }
"%="            { col_num += 2; return emit(MOD_EQ); }
"..<"           { col_num += 3; return emit(RANGE_UNTIL); }
".."            { col_num += 2; return emit(RANGE); }
"->"            { col_num += 2; return emit(ARROW); }
"?."            { col_num += 2; return emit(SAFE_DOT); }
"?:"            { col_num += 2; return emit(ELVIS); }
"::"            { col_num += 2; return emit(COLONCOLON); }
"!!"            { col_num += 2; return emit(DBL_EXCL); }

  /* numeric literals */
{DIGIT}+\.{DIGIT}+([eE][+-]?{DIGIT}+)?[fF]?    { track_text(yytext); yylval.str = strdup(yytext); return emit(REAL_LIT); }
"0"[xX]{HEX}+([uU]?[lL]?)                       { track_text(yytext); yylval.str = strdup(yytext); return emit(INT_LIT); }
"0"[bB]{BIN}+([uU]?[lL]?)                       { track_text(yytext); yylval.str = strdup(yytext); return emit(INT_LIT); }
{DIGIT}+([uU]?[lL]?)                            { track_text(yytext); yylval.str = strdup(yytext); return emit(INT_LIT); }

  /* string and char literals - opaque, $name interpolation ignored */
\"([^"\\\n]|\\.)*\"                             { track_text(yytext); yylval.str = strdup(yytext); return emit(STRING_LIT); }
'([^'\\\n]|\\.)+'                               { track_text(yytext); yylval.str = strdup(yytext); return emit(CHAR_LIT); }

  /* identifiers (including backtick-quoted) */
{IDENT}         { track_text(yytext); yylval.str = strdup(yytext); return emit(IDENTIFIER); }
`[^`\n]+`       { track_text(yytext); yylval.str = strdup(yytext); return emit(IDENTIFIER); }

  /* single-character punctuation - track bracket depth for NL suppression */
"("       { col_num++; paren_depth++;   return emit('('); }
")"       { col_num++; if (paren_depth)   paren_depth--;   return emit(')'); }
"["       { col_num++; bracket_depth++; return emit('['); }
"]"       { col_num++; if (bracket_depth) bracket_depth--; return emit(']'); }
"{"       { col_num++; return emit('{'); }
"}"       { col_num++; return emit('}'); }
"+"       { col_num++; return emit('+'); }
"-"       { col_num++; return emit('-'); }
"*"       { col_num++; return emit('*'); }
"/"       { col_num++; return emit('/'); }
"%"       { col_num++; return emit('%'); }
"="       { col_num++; return emit('='); }
"!"       { col_num++; return emit('!'); }
"<"       { col_num++; return emit('<'); }
">"       { col_num++; return emit('>'); }
"&"       { col_num++; return emit('&'); }
"|"       { col_num++; return emit('|'); }
"?"       { col_num++; return emit('?'); }
"."       { col_num++; return emit('.'); }
","       { col_num++; return emit(','); }
":"       { col_num++; return emit(':'); }
";"       { col_num++; last_can_end_stmt = 0; return ';'; }
"@"       { col_num++; return emit('@'); }

  /* anything else is a lexical error - reported but not fatal */
.   { error_count++; fprintf(stderr, "[Error #%d] line %d, col %d: unexpected character '%s' (lexical)\n", error_count, line_num, col_num, yytext); print_source_line(line_num); fflush(stderr); col_num++; }

%%
