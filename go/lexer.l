%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void record_lexical_error(const char *text, int line);
static int block_comment_start_line = 1;
static int last_can_end_statement = 0;
static int eof_semicolon_emitted = 0;
static int paren_depth = 0;
static int bracket_depth = 0;

static int token_can_end_statement(int token) {
    switch (token) {
        case IDENT:
        case NUM:
        case STRING:
        case RUNE:
        case BREAK:
        case CONTINUE:
        case FALLTHROUGH:
        case RETURN:
        case RPAREN:
        case RBRACKET:
        case RBRACE:
            return 1;
        default:
            return 0;
    }
}

static int emit_token(int token) {
    last_can_end_statement = token_can_end_statement(token);
    eof_semicolon_emitted = 0;
    return token;
}
%}

%option noyywrap
%option yylineno
%option noinput
%option nounput
%x COMMENT

%%

"//".*                         { /* line comment */ }
"/*"                           { block_comment_start_line = yylineno; BEGIN(COMMENT); }
<COMMENT>"*/"                  { BEGIN(INITIAL); }
<COMMENT>\n                    { /* yylineno is updated by flex */ }
<COMMENT>.                     { /* block comment body */ }
<COMMENT><<EOF>>               { record_lexical_error("unterminated block comment", block_comment_start_line); BEGIN(INITIAL); return UNKNOWN; }

"break"                        { return emit_token(BREAK); }
"default"                      { return emit_token(DEFAULT); }
"func"                         { return emit_token(FUNC); }
"interface"                    { return emit_token(INTERFACE); }
"select"                       { return emit_token(SELECT); }
"case"                         { return emit_token(CASE); }
"defer"                        { return emit_token(DEFER); }
"go"                           { return emit_token(GO); }
"map"                          { return emit_token(MAP); }
"struct"                       { return emit_token(STRUCT); }
"chan"                         { return emit_token(CHAN); }
"else"                         { return emit_token(ELSE); }
"goto"                         { return emit_token(GOTO); }
"package"                      { return emit_token(PACKAGE); }
"switch"                       { return emit_token(SWITCH); }
"const"                        { return emit_token(CONST); }
"fallthrough"                  { return emit_token(FALLTHROUGH); }
"if"                           { return emit_token(IF); }
"range"                        { return emit_token(RANGE); }
"type"                         { return emit_token(TYPE); }
"continue"                     { return emit_token(CONTINUE); }
"for"                          { return emit_token(FOR); }
"import"                       { return emit_token(IMPORT); }
"return"                       { return emit_token(RETURN); }
"var"                          { return emit_token(VAR); }
"any"                          { return emit_token(ANY); }
"nil"|"true"|"false"|"iota"    { return emit_token(IDENT); }

\357\273\277                   { /* UTF-8 BOM */ }
[a-zA-Z_\200-\377][a-zA-Z0-9_\200-\377]* { return emit_token(IDENT); }

0[bB][01_]+                    { return emit_token(NUM); }
0[oO][0-7_]+                   { return emit_token(NUM); }
0[xX][0-9a-fA-F_]*(\.[0-9a-fA-F_]*)?[pP][+-]?[0-9_]+[i]? { return emit_token(NUM); }
0[xX][0-9a-fA-F_]+             { return emit_token(NUM); }
([0-9][0-9_]*)(\.[0-9_]*)?([eE][+-]?[0-9_]+)?[i]? { return emit_token(NUM); }
\.[0-9_]+([eE][+-]?[0-9_]+)?[i]? { return emit_token(NUM); }

\"([^\"\\\n]|\\.)*\"          { yylval.sval = strdup(yytext); return emit_token(STRING); }
`([^`])*`                      { yylval.sval = strdup(yytext); return emit_token(STRING); }
'([^'\\\n]|\\.)*'             { return emit_token(RUNE); }

":="                           { return emit_token(DECLARE); }
"=="                           { return emit_token(EQ); }
"!="                           { return emit_token(NEQ); }
"="                            { return emit_token(ASSIGN); }
"("                            { paren_depth++; return emit_token(LPAREN); }
")"                            { if (paren_depth > 0) paren_depth--; return emit_token(RPAREN); }
"{"                            { return emit_token(LBRACE); }
"}"                            { return emit_token(RBRACE); }
"["                            { bracket_depth++; return emit_token(LBRACKET); }
"]"                            { if (bracket_depth > 0) bracket_depth--; return emit_token(RBRACKET); }
","                            { return emit_token(COMMA); }
"."                            { return emit_token(DOT); }
":"                            { return emit_token(COLON); }
";"                            { last_can_end_statement = 0; return SEMICOLON; }

"..."|"<<="|">>="|"&^="|"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|"&&"|"||"|"<-"|"++"|"--"|"<="|">="|"<<" { return emit_token(OP); }
">>"|"&^"|"+"|"-"|"*"|"/"|"%"|"&"|"|"|"^"|"!"|"~"|"<"|">" { return emit_token(OP); }

[ \t\r]+                       { /* whitespace */ }
\n+                             { if (last_can_end_statement && paren_depth == 0 && bracket_depth == 0) { last_can_end_statement = 0; return SEMICOLON; } }
<<EOF>>                        { if (last_can_end_statement && !eof_semicolon_emitted) { eof_semicolon_emitted = 1; last_can_end_statement = 0; return SEMICOLON; } yyterminate(); }
.                               { record_lexical_error(yytext, yylineno); return emit_token(UNKNOWN); }

%%

void reset_lexer_state(void) {
    block_comment_start_line = 1;
    last_can_end_statement = 0;
    eof_semicolon_emitted = 0;
    paren_depth = 0;
    bracket_depth = 0;
    BEGIN(INITIAL);
}
