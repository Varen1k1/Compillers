%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"

int line_num = 1;
int col_num = 1;

void update_location() {
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            line_num++;
            col_num = 1;
        } else {
            col_num++;
        }
    }
}
%}

%option noyywrap
%option yylineno

/* Patterns */
NL               (\r\n|\n|\r)
WS               [ \t\f]+
DIGIT            [0-9]
HEX_DIGIT        [0-9a-fA-F]
BIN_DIGIT        [01]
IDENTIFIER       [a-zA-Z_][a-zA-Z0-9_]*
BACKTICK_ID      `[^`\r\n]+`
INTEGER          {DIGIT}+
HEX_INTEGER      0[xX]{HEX_DIGIT}+
BIN_INTEGER      0[bB]{BIN_DIGIT}+
LONG_INTEGER     {INTEGER}[lL]
UNSIGNED_INT     {INTEGER}[uU]
UNSIGNED_LONG    {INTEGER}[uU][lL]
FLOAT_LITERAL    ({DIGIT}+\.{DIGIT}*|\.{DIGIT}+)([eE][+-]?{DIGIT}+)?[fF]?
DOUBLE_LITERAL   {DIGIT}+\.{DIGIT}*([eE][+-]?{DIGIT}+)?|{DIGIT}+[eE][+-]?{DIGIT}+

%x S_STRING TEMPLATE_STRING

%%

{WS}             { col_num += yyleng; }
{NL}             { line_num++; col_num = 1; return NL; }

/* Comments */
"//".* { }
"/*" { 
    int c;
    int depth = 1;
    while((c = input()) != 0 && depth > 0) {
        if (c == '\n') {
            line_num++;
            col_num = 1;
        } else {
            col_num++;
        }
        if (c == '*') {
            c = input();
            if (c == '/') {
                depth--;
            } else {
                if (c == '\n') {
                    line_num++;
                    col_num = 1;
                }
                unput(c);
            }
        } else if (c == '/' && input() == '*') {
            depth++;
        }
    }
}

/* Keywords */
"abstract"      { yylval.str_val = strdup(yytext); return ABSTRACT; }
"annotation"    { yylval.str_val = strdup(yytext); return ANNOTATION; }
"as"            { return AS; }
"as?"           { return AS_SAFE; }
"break"         { return BREAK; }
"by"            { yylval.str_val = strdup(yytext); return BY; }
"catch"         { yylval.str_val = strdup(yytext); return CATCH; }
"class"         { return CLASS; }
"companion"     { yylval.str_val = strdup(yytext); return COMPANION; }
"const"         { yylval.str_val = strdup(yytext); return CONST_LITERAL; }
"constructor"   { yylval.str_val = strdup(yytext); return CONSTRUCTOR; }
"continue"      { return CONTINUE; }
"crossinline"   { yylval.str_val = strdup(yytext); return CROSSINLINE; }
"data"          { yylval.str_val = strdup(yytext); return DATA; }
"delegate"      { yylval.str_val = strdup(yytext); return DELEGATE; }
"do"            { return DO; }
"dynamic"       { yylval.str_val = strdup(yytext); return DYNAMIC; }
"else"          { return ELSE; }
"enum"          { yylval.str_val = strdup(yytext); return ENUM; }
"expect"        { yylval.str_val = strdup(yytext); return EXPECT_LITERAL; }
"external"      { yylval.str_val = strdup(yytext); return EXTERNAL; }
"false"         { return FALSE; }
"field"         { yylval.str_val = strdup(yytext); return FIELD; }
"file"          { yylval.str_val = strdup(yytext); return FILE_KW; }
"final"         { yylval.str_val = strdup(yytext); return FINAL; }
"finally"       { yylval.str_val = strdup(yytext); return FINALLY; }
"for"           { return FOR; }
"fun"           { return FUN; }
"get"           { yylval.str_val = strdup(yytext); return GET; }
"if"            { return IF; }
"import"        { yylval.str_val = strdup(yytext); return IMPORT; }
"in"            { return IN; }
"infix"         { yylval.str_val = strdup(yytext); return INFIX; }
"init"          { yylval.str_val = strdup(yytext); return INIT; }
"inline"        { yylval.str_val = strdup(yytext); return INLINE; }
"inner"         { yylval.str_val = strdup(yytext); return INNER; }
"interface"     { return INTERFACE; }
"internal"      { yylval.str_val = strdup(yytext); return INTERNAL; }
"is"            { return IS; }
"lateinit"      { yylval.str_val = strdup(yytext); return LATEINIT; }
"noinline"      { yylval.str_val = strdup(yytext); return NOINLINE; }
"null"          { return NULL_LITERAL; }
"object"        { return OBJECT; }
"open"          { yylval.str_val = strdup(yytext); return OPEN; }
"operator"      { yylval.str_val = strdup(yytext); return OPERATOR; }
"out"           { yylval.str_val = strdup(yytext); return OUT; }
"override"      { yylval.str_val = strdup(yytext); return OVERRIDE; }
"package"       { return PACKAGE; }
"param"         { yylval.str_val = strdup(yytext); return PARAM; }
"private"       { yylval.str_val = strdup(yytext); return PRIVATE; }
"protected"     { yylval.str_val = strdup(yytext); return PROTECTED; }
"property"      { yylval.str_val = strdup(yytext); return PROPERTY; }
"public"        { yylval.str_val = strdup(yytext); return PUBLIC; }
"receiver"      { yylval.str_val = strdup(yytext); return RECEIVER; }
"reified"       { yylval.str_val = strdup(yytext); return REIFIED; }
"return"        { return RETURN; }
"sealed"        { yylval.str_val = strdup(yytext); return SEALED; }
"set"           { yylval.str_val = strdup(yytext); return SET; }
"setparam"      { yylval.str_val = strdup(yytext); return SETPARAM; }
"super"         { return SUPER; }
"suspend"       { yylval.str_val = strdup(yytext); return SUSPEND; }
"tailrec"       { yylval.str_val = strdup(yytext); return TAILREC; }
"this"          { return THIS; }
"throw"         { return THROW; }
"true"          { return TRUE; }
"try"           { return TRY; }
"typealias"     { return TYPE_ALIAS; }
"val"           { return VAL; }
"var"           { return VAR; }
"vararg"        { yylval.str_val = strdup(yytext); return VARARG; }
"when"          { return WHEN; }
"where"         { yylval.str_val = strdup(yytext); return WHERE; }
"while"         { return WHILE; }

/* Special keywords for soft mode (can be identifiers too) */
"actual"        { yylval.str_val = strdup(yytext); return ACTUAL; }
"value"         { yylval.str_val = strdup(yytext); return VALUE; }

/* Operators - Three character */
"==="           { return EQEQEQ; }
"!=="           { return EXCL_EQEQ; }
"!in"           { return NOT_IN; }
"!is"           { return NOT_IS; }
"..<"           { return RANGE_UNTIL; }
"!!"            { return DOUBLE_EXCL; }
"?."            { return SAFE_DOT; }
"?:"            { return ELVIS; }
"::"            { return DOUBLE_COLON; }

/* Operators - Two character */
"=="            { return EQEQ; }
"!="            { return EXCL_EQ; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return ANDAND; }
"||"            { return OROR; }
"++"            { return INCR; }
"--"            { return DECR; }
"+="            { return ADD_ASSIGN; }
"-="            { return SUB_ASSIGN; }
"*="            { return MULT_ASSIGN; }
"/="            { return DIV_ASSIGN; }
"%="            { return MOD_ASSIGN; }
".."            { return RANGE; }
"->"            { return ARROW; }

/* Single character operators */
"+"             { return ADD; }
"-"             { return SUB; }
"*"             { return MULT; }
"/"             { return DIV; }
"%"             { return MOD; }
"="             { return ASSIGNMENT; }
"!"             { return NOT; }
"<"             { return LANGLE; }
">"             { return RANGLE; }
"&"             { return AMPER; }

/* Delimiters */
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACK; }
"]"             { return RBRACK; }
"{"             { return LCURL; }
"}"             { return RCURL; }
"."             { return DOT; }
","             { return COMMA; }
":"             { return COLON; }
";"             { return SEMICOLON; }
"?"             { return QUEST; }
"@"             { return AT; }

/* Literals */
{LONG_INTEGER}          { yylval.str_val = strdup(yytext); return LONG_LITERAL; }
{UNSIGNED_LONG}         { yylval.str_val = strdup(yytext); return UNSIGNED_LITERAL; }
{UNSIGNED_INT}          { yylval.str_val = strdup(yytext); return UNSIGNED_LITERAL; }
{HEX_INTEGER}           { yylval.str_val = strdup(yytext); return HEX_LITERAL; }
{BIN_INTEGER}           { yylval.str_val = strdup(yytext); return BIN_LITERAL; }
{DOUBLE_LITERAL}        { yylval.str_val = strdup(yytext); return REAL_LITERAL; }
{FLOAT_LITERAL}         { yylval.str_val = strdup(yytext); return REAL_LITERAL; }
{INTEGER}               { yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }

/* String and character literals */
\"              { BEGIN(TEMPLATE_STRING); return QUOTE; }
"${"            { return DOLLAR_LBRACE; }
'.'             { yylval.str_val = strdup(yytext); return CHARACTER_LITERAL; }
"$"             { return DOLLAR; }

<TEMPLATE_STRING>{
    "\\\""      { /* escaped quote */ }
    "\\"        { /* escaped char */ }
    "\""        { BEGIN(INITIAL); return QUOTE; }
    "$"         { return DOLLAR; }
    \n          { line_num++; col_num = 1; }
    [^"\\\n$]   { /* string content */ }
}

/* Identifiers */
{IDENTIFIER}    { yylval.str_val = strdup(yytext); return IDENTIFIER; }
{BACKTICK_ID}   { yylval.str_val = strdup(yytext); return IDENTIFIER; }

/* Error handling */
.               { 
    fprintf(stderr, "Lexical Error at line %d, column %d: Unexpected character '%s'\n", 
            line_num, col_num, yytext);
    col_num++;
}

%%
