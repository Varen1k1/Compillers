%glr-parser
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yylineno;
extern FILE *yyin;
void yyerror(const char *s);

int error_count = 0;
int has_package = 0;

typedef struct {
    char* name;
    int line;
} Declaration;

Declaration declarations[1000];
int decl_count = 0;

void add_declaration(const char* name, int line) {
    if (decl_count < 1000) {
        declarations[decl_count].name = strdup(name);
        declarations[decl_count].line = line;
        decl_count++;
    }
}

%}

%union {
    int int_val;
    char* str_val;
    struct {
        char* name;
        int line;
    } decl_val;
}

/* Tokens - Literals and Identifiers */
%token <int_val> INTEGER_LITERAL
%token <str_val> IDENTIFIER REAL_LITERAL HEX_LITERAL BIN_LITERAL LONG_LITERAL UNSIGNED_LITERAL
%token <str_val> CHARACTER_LITERAL STRING_LITERAL

/* Tokens - Modifiers */
%token <str_val> ABSTRACT ANNOTATION BY CATCH COMPANION CONSTRUCTOR CROSSINLINE DATA
%token <str_val> DELEGATE DYNAMIC ENUM EXPECT_LITERAL EXTERNAL FIELD FILE_KW FINAL
%token <str_val> FINALLY GET IMPORT INFIX INIT INLINE INNER INTERNAL LATEINIT
%token <str_val> NOINLINE OPEN OPERATOR OUT OVERRIDE PARAM PRIVATE PROPERTY
%token <str_val> PROTECTED PUBLIC RECEIVER REIFIED SEALED SET SETPARAM SUSPEND
%token <str_val> TAILREC VARARG WHERE ACTUAL VALUE CONST_LITERAL

/* Tokens - Keywords */
%token AS AS_SAFE BREAK CLASS CONTINUE DO ELSE FALSE FOR FUN IF IN NOT_IN
%token INTERFACE IS NOT_IS OBJECT PACKAGE RETURN SUPER THIS THROW TRUE TRY
%token TYPE_ALIAS VAL VAR WHEN WHILE NULL_LITERAL

/* Tokens - Operators */
%token EQEQEQ EXCL_EQEQ EQEQ EXCL_EQ LE GE ANDAND OROR
%token INCR DECR ADD_ASSIGN SUB_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token RANGE RANGE_UNTIL DOUBLE_EXCL SAFE_DOT ELVIS DOUBLE_COLON ARROW
%token ADD SUB MULT DIV MOD ASSIGNMENT NOT LANGLE RANGLE AMPER

/* Tokens - Delimiters */
%token LPAREN RPAREN LBRACK RBRACK LCURL RCURL DOT COMMA COLON SEMICOLON QUEST AT
%token NL DOLLAR QUOTE DOLLAR_LBRACE

%type <str_val> identifier simpleIdentifier type modifiers
%type <str_val> typeArguments typeParameters

%expect 128

%start kotlinFile

/* Operator precedence and associativity (lowest to highest) */
%nonassoc LOWEST
%nonassoc IF
%nonassoc ELSE
%right ASSIGNMENT ADD_ASSIGN SUB_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%right ARROW
%left OROR
%left ANDAND
%left EQEQ EXCL_EQ EQEQEQ EXCL_EQEQ
%nonassoc IN NOT_IN IS NOT_IS
%nonassoc RANGE RANGE_UNTIL
%left LANGLE RANGLE LE GE
%right ELVIS
%left ADD SUB
%left MULT DIV MOD
%left AS AS_SAFE
%right NOT INCR DECR DOUBLE_EXCL
%left DOT SAFE_DOT DOUBLE_COLON
%nonassoc LPAREN RPAREN LBRACK RBRACK
%nonassoc CALL_SUFFIX
%nonassoc HIGHEST

%%

/* ============================================================================ */
/* ROOT RULES */
/* ============================================================================ */

kotlinFile
    : opt_nl topLevelItems opt_nl
    | opt_nl
    ;

topLevelItems
    : topLevelItem
    | topLevelItems separator topLevelItem
    ;

topLevelItem
    : packageHeader
    | importHeader
    | topLevelDeclaration
    | error { yyerrok; fprintf(stderr, "Skipping error at line %d\n", yylineno); }
    ;

/* ============================================================================ */
/* SEPARATORS */
/* ============================================================================ */

opt_nl
    : nl
    | /* empty */
    ;

nl
    : NL
    | nl NL
    ;

separator
    : SEMICOLON
    | NL
    ;

separators
    : separator
    | separators separator
    ;

opt_separator
    : separator
    | /* empty */
    ;

/* ============================================================================ */
/* PACKAGE AND IMPORTS */
/* ============================================================================ */

packageHeader
    : PACKAGE identifier opt_separator
        { printf("[Line %d] Package: %s\n", yylineno, $2); has_package = 1; free($2); }
    ;

importHeader
    : IMPORT identifier opt_separator
        { printf("[Line %d] Import: %s\n", yylineno, $2); free($2); }
    | IMPORT identifier DOT MULT opt_separator
        { printf("[Line %d] Import all: %s.*\n", yylineno, $2); free($2); }
    | IMPORT identifier AS simpleIdentifier opt_separator
        { printf("[Line %d] Import as: %s as %s\n", yylineno, $2, $4); free($2); free($4); }
    ;

/* ============================================================================ */
/* TOP-LEVEL DECLARATIONS */
/* ============================================================================ */

topLevelDeclaration
    : classDeclaration
    | objectDeclaration
    | interfaceDeclaration
    | functionDeclaration
    | propertyDeclaration
    | typeAliasDeclaration
    | enumDeclaration
    ;

/* ============================================================================ */
/* CLASS DECLARATION */
/* ============================================================================ */

classDeclaration
    : opt_modifiers CLASS simpleIdentifier opt_typeParameters opt_primaryConstructor
      opt_inheritance opt_classBody
        { printf("[Line %d] Class: %s\n", yylineno, $3); add_declaration($3, yylineno); free($3); }
    ;

opt_primaryConstructor
    : opt_modifiers CONSTRUCTOR LPAREN opt_classParameters RPAREN
    | LPAREN opt_classParameters RPAREN
    | /* empty */
    ;

opt_classParameters
    : classParameterList
    | /* empty */
    ;

classParameterList
    : classParameter
    | classParameterList COMMA classParameter
    | classParameterList NL classParameter
    ;

classParameter
    : opt_modifiers opt_val_var simpleIdentifier COLON type opt_equalExpression
        { free($3); }
    | opt_modifiers opt_val_var simpleIdentifier opt_equalExpression
        { free($3); }
    ;

opt_val_var
    : VAL
    | VAR
    | /* empty */
    ;

opt_inheritance
    : COLON delegationSpecifiers
    | /* empty */
    ;

delegationSpecifiers
    : delegationSpecifier
    | delegationSpecifiers COMMA delegationSpecifier
    | delegationSpecifiers NL delegationSpecifier
    ;

delegationSpecifier
    : type opt_typeArguments opt_callArguments
    | type opt_typeArguments
    ;

opt_callArguments
    : LPAREN opt_callArgumentList RPAREN
    | /* empty */
    ;

opt_callArgumentList
    : callArgumentList
    | /* empty */
    ;

callArgumentList
    : expression
    | callArgumentList COMMA expression
    | callArgumentList NL expression
    ;

opt_classBody
    : classBody
    | /* empty */
    ;

classBody
    : LCURL opt_nl opt_classMembers opt_nl RCURL
    | LCURL opt_nl RCURL
    ;

opt_classMembers
    : classMembers
    | /* empty */
    ;

classMembers
    : classMember
    | classMembers separator classMember
    ;

classMember
    : topLevelDeclaration
    | INIT LCURL opt_nl statements opt_nl RCURL
    | companionObject
    ;

companionObject
    : opt_modifiers COMPANION OBJECT simpleIdentifier opt_inheritance opt_classBody
        { free($4); }
    ;

/* ============================================================================ */
/* OBJECT DECLARATION */
/* ============================================================================ */

objectDeclaration
    : opt_modifiers OBJECT simpleIdentifier opt_inheritance opt_classBody
        { printf("[Line %d] Object: %s\n", yylineno, $3); add_declaration($3, yylineno); free($3); }
    ;

/* ============================================================================ */
/* INTERFACE DECLARATION */
/* ============================================================================ */

interfaceDeclaration
    : opt_modifiers INTERFACE simpleIdentifier opt_typeParameters opt_inheritance opt_classBody
        { printf("[Line %d] Interface: %s\n", yylineno, $3); add_declaration($3, yylineno); free($3); }
    ;

/* ============================================================================ */
/* ENUM DECLARATION */
/* ============================================================================ */

enumDeclaration
    : opt_modifiers ENUM CLASS simpleIdentifier opt_typeParameters opt_inheritance enumBody
        { printf("[Line %d] Enum: %s\n", yylineno, $4); add_declaration($4, yylineno); free($4); }
    | opt_modifiers ENUM CLASS simpleIdentifier opt_typeParameters opt_primaryConstructor
      opt_inheritance enumBody
        { printf("[Line %d] Enum: %s\n", yylineno, $4); add_declaration($4, yylineno); free($4); }
    ;

enumBody
    : LCURL opt_nl opt_enumEntries opt_enumBody_rest opt_nl RCURL
    | LCURL opt_nl RCURL
    ;

opt_enumEntries
    : enumEntries
    | /* empty */
    ;

enumEntries
    : enumEntry
    | enumEntries COMMA enumEntry
    | enumEntries NL enumEntry
    ;

enumEntry
    : opt_modifiers simpleIdentifier opt_callArguments opt_enumBody
        { free($2); }
    ;

opt_enumBody
    : LCURL opt_nl opt_classMembers opt_nl RCURL
    | /* empty */
    ;

opt_enumBody_rest
    : SEMICOLON opt_nl opt_classMembers
    | /* empty */
    ;

/* ============================================================================ */
/* TYPE ALIAS */
/* ============================================================================ */

typeAliasDeclaration
    : opt_modifiers TYPE_ALIAS simpleIdentifier opt_typeParameters ASSIGNMENT type
        { free($3); }
    ;

/* ============================================================================ */
/* FUNCTION DECLARATION */
/* ============================================================================ */

functionDeclaration
    : opt_modifiers FUN opt_typeParameters opt_receiverType simpleIdentifier
      LPAREN opt_functionParameters RPAREN opt_colonType opt_typeConstraints opt_functionBody
        { printf("[Line %d] Function: %s\n", yylineno, $5); add_declaration($5, yylineno); free($5); }
    ;

opt_receiverType
    : type DOT
    | /* empty */
    ;

opt_functionParameters
    : functionParameterList
    | /* empty */
    ;

functionParameterList
    : functionParameter
    | functionParameterList COMMA functionParameter
    | functionParameterList NL functionParameter
    ;

functionParameter
    : opt_modifiers simpleIdentifier COLON type opt_equalExpression
        { free($2); }
    | opt_modifiers simpleIdentifier opt_equalExpression
        { free($2); }
    ;

opt_colonType
    : COLON type
    | /* empty */
    ;

opt_typeConstraints
    : typeConstraints
    | /* empty */
    ;

typeConstraints
    : WHERE typeConstraintList
    ;

typeConstraintList
    : typeConstraint
    | typeConstraintList COMMA typeConstraint
    ;

typeConstraint
    : simpleIdentifier COLON type
        { free($1); }
    ;

opt_functionBody
    : functionBody
    | /* empty */
    ;

functionBody
    : LCURL opt_nl statements opt_nl RCURL
    | LCURL opt_nl RCURL
    | ASSIGNMENT expression
    ;

/* ============================================================================ */
/* PROPERTY DECLARATION */
/* ============================================================================ */

propertyDeclaration
    : opt_modifiers val_or_var simpleIdentifier opt_typeParameters opt_colonType
      opt_propertyInitializer opt_propertyAccessors
        { free($3); }
    ;

val_or_var
    : VAL
    | VAR
    ;

opt_typeParameters
    : typeParameters
    | /* empty */
    ;

opt_colonType_arg
    : COLON type
    | /* empty */
    ;

opt_propertyInitializer
    : ASSIGNMENT expression
    | propertyDelegate
    | /* empty */
    ;

propertyDelegate
    : BY expression
    ;

opt_propertyAccessors
    : propertyAccessors
    | /* empty */
    ;

propertyAccessors
    : getter
    | setter
    | getter setter
    | setter getter
    ;

getter
    : opt_modifiers GET opt_propertyBody
    ;

setter
    : opt_modifiers SET opt_setterParameter opt_propertyBody
    ;

opt_setterParameter
    : LPAREN setterParameter RPAREN
    | /* empty */
    ;

setterParameter
    : simpleIdentifier
    | /* empty */
        { free($1); }
    ;

opt_propertyBody
    : LCURL statements RCURL
    | ASSIGNMENT expression
    | /* empty */
    ;

/* ============================================================================ */
/* STATEMENTS */
/* ============================================================================ */

statements
    : opt_statementList
    | semis
    | opt_statementList semis
    ;

opt_statementList
    : statementList
    | /* empty */
    ;

statementList
    : statement
    | statementList semis statement
    ;

semis
    : SEMICOLON
    | NL
    | semis SEMICOLON
    | semis NL
    ;

statement
    : opt_statementPrefix statementContent
    ;

opt_statementPrefix
    : statementPrefix
    | /* empty */
    ;

statementPrefix
    : annotationList
    | label
    ;

label
    : simpleIdentifier AT
        { free($1); }
    ;

statementContent
    : declaration
    | assignment
    | loopStatement
    | jumpStatement
    | tryStatement
    | expression
    ;

assignment
    : assignableExpression ASSIGNMENT expression
    | assignableExpression ADD_ASSIGN expression
    | assignableExpression SUB_ASSIGN expression
    | assignableExpression MULT_ASSIGN expression
    | assignableExpression DIV_ASSIGN expression
    | assignableExpression MOD_ASSIGN expression
    ;

assignableExpression
    : simpleIdentifier
    | parenthesizedAssignableExpression
    | assignableExpression DOT simpleIdentifier
    | assignableExpression LBRACK expression RBRACK
    ;

parenthesizedAssignableExpression
    : LPAREN assignableExpression RPAREN
    ;

loopStatement
    : forStatement
    | whileStatement
    | doWhileStatement
    ;

forStatement
    : FOR LPAREN variableDeclaration IN expression RPAREN controlStructureBody
    ;

whileStatement
    : WHILE LPAREN expression RPAREN controlStructureBody
    | WHILE LPAREN expression RPAREN SEMICOLON
    ;

doWhileStatement
    : DO controlStructureBody WHILE LPAREN expression RPAREN
    ;

controlStructureBody
    : LCURL opt_nl statements opt_nl RCURL
    | statement
    ;

jumpStatement
    : RETURN
    | RETURN expression
    | THROW expression
    | BREAK
    | CONTINUE
    | label BREAK
        { free($1); }
    | label CONTINUE
        { free($1); }
    ;

tryStatement
    : TRY block catchBlocks finallyBlock
    | TRY block catchBlocks
    | TRY block finallyBlock
    ;

catchBlocks
    : catchBlock
    | catchBlocks catchBlock
    ;

catchBlock
    : CATCH LPAREN variableDeclaration RPAREN block
    ;

finallyBlock
    : FINALLY block
    ;

/* ============================================================================ */
/* EXPRESSIONS */
/* ============================================================================ */

expression
    : disjunction
    | ifExpression
    | whenExpression
    | tryExpression
    | lambdaExpression
    ;

ifExpression
    : IF LPAREN expression RPAREN controlStructureBody %prec IF
    | IF LPAREN expression RPAREN controlStructureBody ELSE controlStructureBody
    ;

whenExpression
    : WHEN LPAREN expression RPAREN LCURL opt_nl whenEntries opt_nl RCURL
    | WHEN LCURL opt_nl whenEntries opt_nl RCURL
    ;

whenEntries
    : whenEntry
    | whenEntries NL whenEntry
    | whenEntries COMMA whenEntry
    ;

whenEntry
    : whenCondition ARROW controlStructureBody
    | ELSE ARROW controlStructureBody
    ;

whenCondition
    : expression
    | whenCondition COMMA expression
    ;

tryExpression
    : TRY expression catchBlocks finallyBlock
    | TRY expression catchBlocks
    | TRY expression finallyBlock
    ;

lambdaExpression
    : LCURL opt_nl opt_lambdaParameters ARROW opt_nl statements opt_nl RCURL
    ;

opt_lambdaParameters
    : lambdaParameterList
    | /* empty */
    ;

lambdaParameterList
    : lambdaParameter
    | lambdaParameterList COMMA lambdaParameter
    ;

lambdaParameter
    : variableDeclaration
    ;

variableDeclaration
    : simpleIdentifier
    | simpleIdentifier COLON type
        { free($1); }
    ;

disjunction
    : conjunction
    | disjunction OROR conjunction
    ;

conjunction
    : equality
    | conjunction ANDAND equality
    ;

equality
    : comparison
    | equality EQEQ comparison
    | equality EXCL_EQ comparison
    | equality EQEQEQ comparison
    | equality EXCL_EQEQ comparison
    ;

comparison
    : inclusionCheck
    | comparison LANGLE inclusionCheck
    | comparison RANGLE inclusionCheck
    | comparison LE inclusionCheck
    | comparison GE inclusionCheck
    ;

inclusionCheck
    : typeCheck
    | inclusionCheck IN typeCheck
    | inclusionCheck NOT_IN typeCheck
    ;

typeCheck
    : range
    | typeCheck IS type
    | typeCheck NOT_IS type
    | typeCheck AS type
    | typeCheck AS_SAFE type
    ;

range
    : additiveExpression
    | range RANGE additiveExpression
    | range RANGE_UNTIL additiveExpression
    | range ELVIS additiveExpression
    ;

additiveExpression
    : multiplicativeExpression
    | additiveExpression ADD multiplicativeExpression
    | additiveExpression SUB multiplicativeExpression
    ;

multiplicativeExpression
    : unaryExpression
    | multiplicativeExpression MULT unaryExpression
    | multiplicativeExpression DIV unaryExpression
    | multiplicativeExpression MOD unaryExpression
    ;

unaryExpression
    : prefixUnaryExpression
    | postfixExpression
    ;

prefixUnaryExpression
    : INCR unaryExpression
    | DECR unaryExpression
    | ADD unaryExpression
    | SUB unaryExpression
    | NOT unaryExpression
    ;

postfixExpression
    : primaryExpression
    | postfixExpression postfixUnarySuffix %prec CALL_SUFFIX
    | postfixExpression INCR
    | postfixExpression DECR
    | postfixExpression DOUBLE_EXCL
    ;

postfixUnarySuffix
    : DOT simpleIdentifier
    | DOT functionCall
    | SAFE_DOT simpleIdentifier
    | SAFE_DOT functionCall
    | DOUBLE_COLON simpleIdentifier
    | DOUBLE_COLON CLASS
    | LBRACK expression RBRACK
    | functionCall
    | typeArguments
    | lambdaExpression
    ;

functionCall
    : LPAREN opt_callArgumentList RPAREN
    ;

opt_typeArguments
    : typeArguments
    | /* empty */
    ;

typeArguments
    : LANGLE typeArgumentList RANGLE
    ;

typeArgumentList
    : typeArgument
    | typeArgumentList COMMA typeArgument
    ;

typeArgument
    : type
    | varianceModifier type
    ;

varianceModifier
    : OUT
    | IN
    ;

primaryExpression
    : parenthesizedExpression
    | simpleIdentifier
    | functionLiteral
    | THIS
    | SUPER
    | literalConstant
    | stringLiteral
    | collectionLiteral
    | callableReference
    ;

parenthesizedExpression
    : LPAREN expression RPAREN
    ;

functionLiteral
    : LCURL opt_nl statements opt_nl RCURL
    ;

literalConstant
    : INTEGER_LITERAL
    | REAL_LITERAL
    | HEX_LITERAL
    | BIN_LITERAL
    | LONG_LITERAL
    | UNSIGNED_LITERAL
    | CHARACTER_LITERAL
    | TRUE
    | FALSE
    | NULL_LITERAL
    ;

stringLiteral
    : QUOTE stringContent QUOTE
    | QUOTE QUOTE
    ;

stringContent
    : stringPart
    | stringContent stringPart
    ;

stringPart
    : STRING_LITERAL
    | DOLLAR simpleIdentifier
    | DOLLAR_LBRACE expression RCURL
    ;

collectionLiteral
    : LBRACK opt_collectionElements RBRACK
    ;

opt_collectionElements
    : collectionElements
    | /* empty */
    ;

collectionElements
    : expression
    | collectionElements COMMA expression
    | collectionElements NL expression
    ;

callableReference
    : DOUBLE_COLON simpleIdentifier
    | type DOUBLE_COLON simpleIdentifier
    | type DOUBLE_COLON CLASS
    ;

/* ============================================================================ */
/* TYPES */
/* ============================================================================ */

type
    : typeReference opt_typeModifiers
        { $$ = $1; }
    ;

opt_typeModifiers
    : typeModifiers
    | /* empty */
    ;

typeModifiers
    : typeModifier
    | typeModifiers typeModifier
    ;

typeModifier
    : QUEST
    | AMPER
    ;

typeReference
    : annotationList type
    | userType
    | nullableType
    | functionType
    ;

nullableType
    : typeReference QUEST
    ;

userType
    : simpleIdentifier opt_typeArguments
        { $$ = $1; }
    | userType DOT simpleIdentifier opt_typeArguments
        { 
            char* res = malloc(strlen($1) + strlen($3) + 2);
            sprintf(res, "%s.%s", $1, $3);
            free($1); free($3);
            $$ = res;
        }
    ;

typeParameters
    : LANGLE typeParameterList RANGLE
    ;

typeParameterList
    : typeParameter
    | typeParameterList COMMA typeParameter
    ;

typeParameter
    : opt_typeParameterModifiers simpleIdentifier opt_colonType
        { free($2); }
    ;

opt_typeParameterModifiers
    : typeParameterModifiers
    | /* empty */
    ;

typeParameterModifiers
    : typeParameterModifier
    | typeParameterModifiers typeParameterModifier
    ;

typeParameterModifier
    : REIFIED
    | varianceModifier
    ;

functionType
    : LPAREN opt_functionTypeParameters RPAREN ARROW type
    ;

opt_functionTypeParameters
    : functionTypeParameterList
    | /* empty */
    ;

functionTypeParameterList
    : type
    | functionTypeParameterList COMMA type
    ;

/* ============================================================================ */
/* IDENTIFIERS */
/* ============================================================================ */

identifier
    : simpleIdentifier
        { $$ = $1; }
    | identifier DOT simpleIdentifier
        {
            char* res = malloc(strlen($1) + strlen($3) + 2);
            sprintf(res, "%s.%s", $1, $3);
            free($1); free($3);
            $$ = res;
        }
    ;

simpleIdentifier
    : IDENTIFIER
        { $$ = $1; }
    | ABSTRACT { $$ = $1; }
    | ANNOTATION { $$ = $1; }
    | BY { $$ = $1; }
    | CATCH { $$ = $1; }
    | COMPANION { $$ = $1; }
    | CONSTRUCTOR { $$ = $1; }
    | CROSSINLINE { $$ = $1; }
    | DATA { $$ = $1; }
    | DELEGATE { $$ = $1; }
    | DYNAMIC { $$ = $1; }
    | ENUM { $$ = $1; }
    | EXPECT_LITERAL { $$ = $1; }
    | EXTERNAL { $$ = $1; }
    | FIELD { $$ = $1; }
    | FILE_KW { $$ = $1; }
    | FINAL { $$ = $1; }
    | FINALLY { $$ = $1; }
    | GET { $$ = $1; }
    | IMPORT { $$ = $1; }
    | INFIX { $$ = $1; }
    | INIT { $$ = $1; }
    | INLINE { $$ = $1; }
    | INNER { $$ = $1; }
    | INTERNAL { $$ = $1; }
    | LATEINIT { $$ = $1; }
    | NOINLINE { $$ = $1; }
    | OPEN { $$ = $1; }
    | OPERATOR { $$ = $1; }
    | OUT { $$ = $1; }
    | OVERRIDE { $$ = $1; }
    | PARAM { $$ = $1; }
    | PRIVATE { $$ = $1; }
    | PROPERTY { $$ = $1; }
    | PROTECTED { $$ = $1; }
    | PUBLIC { $$ = $1; }
    | RECEIVER { $$ = $1; }
    | REIFIED { $$ = $1; }
    | SEALED { $$ = $1; }
    | SET { $$ = $1; }
    | SETPARAM { $$ = $1; }
    | SUSPEND { $$ = $1; }
    | TAILREC { $$ = $1; }
    | VARARG { $$ = $1; }
    | VALUE { $$ = $1; }
    | ACTUAL { $$ = $1; }
    | WHERE { $$ = $1; }
    | CONST_LITERAL { $$ = $1; }
    ;

/* ============================================================================ */
/* MODIFIERS */
/* ============================================================================ */

opt_modifiers
    : modifiers
    | /* empty */
    ;

modifiers
    : modifier
    | modifiers modifier
    ;

modifier
    : ABSTRACT
    | FINAL
    | OPEN
    | PUBLIC
    | PRIVATE
    | INTERNAL
    | PROTECTED
    | OVERRIDE
    | LATEINIT
    | DATA
    | INLINE
    | INNER
    | SEALED
    | ENUM
    | TAILREC
    | EXTERNAL
    | INFIX
    | OPERATOR
    | SUSPEND
    | EXPECT_LITERAL
    | ACTUAL
    | CONST_LITERAL
    | CROSSINLINE
    | NOINLINE
    | REIFIED
    | VARARG
    ;

/* ============================================================================ */
/* ANNOTATIONS */
/* ============================================================================ */

annotationList
    : annotation
    | annotationList annotation
    ;

annotation
    : AT simpleIdentifier
    | AT simpleIdentifier LPAREN opt_callArgumentList RPAREN
    ;

/* ============================================================================ */
/* OPTIONAL EXPRESSIONS */
/* ============================================================================ */

opt_equalExpression
    : ASSIGNMENT expression
    | /* empty */
    ;

%%

void yyerror(const char *s) {
    error_count++;
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }
    
    printf("========================================\n");
    printf("Kotlin Parser - Starting analysis\n");
    printf("========================================\n\n");
    
    int parse_result = yyparse();
    
    printf("\n========================================\n");
    printf("Analysis Report\n");
    printf("========================================\n");
    printf("Total declarations found: %d\n", decl_count);
    printf("Total errors found: %d\n", error_count);
    
    if (decl_count > 0) {
        printf("\nDeclarations:\n");
        for (int i = 0; i < decl_count; i++) {
            printf("  Line %d: %s\n", declarations[i].line, declarations[i].name);
        }
    }
    
    printf("\n========================================\n");
    if (parse_result == 0 && error_count == 0) {
        printf("Result: SUCCESS - File is valid Kotlin code\n");
    } else {
        printf("Result: FAILURE - File contains errors\n");
    }
    printf("========================================\n");
    
    return (parse_result == 0 && error_count == 0) ? 0 : 1;
}
