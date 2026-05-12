%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int line_num;
extern FILE *yyin;
void yyerror(const char *s);

int has_error = 0; 
%}

%union {
    int int_val;
    char* str_val;
}

%token <int_val> INTEGER_LITERAL INTEGER_NO_ZERO
%token <str_val> IDENTIFIER REAL_LITERAL HEX_LITERAL STRING_LITERAL BIN_LITERAL
%token <str_val> ABSTRACT ANNOTATION BY CATCH COMPANION CONSTRUCTOR CROSSINLINE DATA DYNAMIC
%token <str_val> ENUM EXTERNAL FINAL FINALLY GET IMPORT INFIX INIT INLINE EXPECT_LITERAL ACTUAL
%token <str_val> INNER INTERNAL LATEINIT NOINLINE OPEN OPERATOR OUT OVERRIDE PRIVATE VALUE
%token <str_val> PROTECTED PUBLIC REIFIED SEALED SET SUSPEND TAILREC VARARG WHERE CONST_LITERAL
%token <str_val> FIELD PROPERTY RECEIVER PARAM SETPARAM DELEGATE FILE_KW UNSIGNED_LITERAL
%token NL DOLLAR QUOTE CHARACTER_LITERAL QUEST LONG_LITERAL
%token AS AS_SAFE BREAK CLASS CONTINUE DO ELSE FOR FUN IF IN NOT_IN THIS_AT
%token INTERFACE IS NOT_IS OBJECT PACKAGE RETURN SUPER THIS THROW TRY RETURN_AT
%token TYPE_ALIAS VAL VAR WHEN WHILE TRUE FALSE NULL_LITERAL SUPER_AT
%token EQEQEQ EXCL_EQEQ EQEQ EXCL_EQ LE GE ANDAND OROR CONTINUE_AT
%token INCR DECR ADD_ASSIGN SUB_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN 
%token RANGE RANGE_UNTIL DOUBLE_EXCL SAFE_DOT ELVIS DOUBLE_COLON ARROW BREAK_AT
%token ADD SUB MULT DIV MOD ASSIGNMENT NOT LANGLE RANGLE AMPER 
%token LPAREN RPAREN LBRACK RBRACK LCURL RCURL DOT COMMA COLON SEMICOLON AT

%type <str_val> simpleIdentifier

%start kotlinFile

%%

/* Разделители */
opt_separators 
    : separators 
    | /* empty */ 
    ;
separators 
    : separator
    | separators separator 
    ;
separator 
    : SEMICOLON /* Точка с запятой */
    | NL /* Перенос строки */
    ;
semi
    : separator separators /* (';' | NL) {NL} */
    ;
semis   
    : SEMICOLON
    | separators

/* Точка входа */
kotlinFile
    : opt_separators topLevelElements opt_separators
    | opt_separators
    ;

topLevelElements
    : topLevelElement
    | topLevelElements separators topLevelElement
    ;

topLevelElement
    : packageHeader
    | importHeader
    | declaration
    | error { yyerrok; yyclearin; }
    ;

/* --- Заголовки --- */
packageHeader
    : PACKAGE identifier
    ;

identifier
    : simpleIdentifier
    | identifier DOT simpleIdentifier
    ;

importHeader
    : IMPORT identifier 
    | IMPORT identifier DOT MULT opt_semi
    | IMPORT identifier AS simpleIdentifier
    ;  

/* --- Декларации --- */
declaration
    : classDeclaration
    | objectDeclaration
    | functionDeclaration
    | propertyDeclaration
    | typeAlias
    ;

typeAlias
    : opt_modifiers TYPE_ALIAS opt_separators simpleIdentifier opt_separators opt_typeParams opt_separators ASSIGNMENT opt_separators type
    ;

objectDeclaration
    : opt_modifiers OBJECT opt_separators simpleIdentifier opt_colon_delegationSpecs opt_separators classBody
    | opt_modifiers OBJECT opt_separators simpleIdentifier opt_colon_delegationSpecs opt_separators
    ;

functionDeclaration
    : opt_modifiers FUN opt_separators opt_typeParams opt_separators opt_receiverTypeDot opt_separators simpleIdentifier opt_separators functionValueParameters opt_colonType opt_typeConstraints opt_functionBody
    ;

propertyDeclaration
    : opt_modifiers opt_val_var opt_typeParams opt_receiverTypeDot opt_separators multi_singleVariableDeclaration opt_separators opt_typeConstraints opt_separators equalExpression_PropertyDelegate opt_separators opt_semicolon opt_separators getter_setter
    ;

multi_singleVariableDeclaration
    : multiVariableDeclaration
    | variableDeclaration
    ;

equalExpression_PropertyDelegate
    : equalExpression
    | propertyDelegate
    ;

propertyDelegate
    : BY opt_separators expression
    ;

getter_setter
    : opt_getter opt_separators opt_semi_setter
    ;

opt_getter
    : getter
    | /* empty */
    ;

opt_semi_setter
    : opt_semi setter
    | /* empty */
    ;

getter
    : opt_modifiers GET 
    | opt_modifiers GET opt_separators LPAREN opt_separators RPAREN opt_type_annotation opt_separators functionBody
    ;

setter
    : opt_modifiers SET
    | opt_modifiers SET opt_separators LPAREN opt_separators functionValueParameterWithOptionalType opt_trailing_comma opt_separators RPAREN opt_type_annotation opt_separators functionBody
    ;

classDeclaration
    : opt_modifiers class_or_interface opt_separators simpleIdentifier opt_separators opt_typeParams opt_separators opt_primaryConstr opt_colon_delegationSpecs opt_typeConstraints opt_separators opt_classBody_enumClassBody { printf("[Line %d] Class/Interface declared: %s\n", line_num,  $4); free($4); }
    ;

opt_classBody_enumClassBody
    : classBody
    | enumClassBody
    ;

enumClassBody
    : LCURL opt_separators opt_enumEntries opt_trailing_comma opt_semicolon_classMemberDeclarations opt_separators RCURL
    ;

opt_semicolon_classMemberDeclarations
    : opt_separators SEMICOLON opt_separators classMemberDeclarations
    ;

opt_enumEntries
    : enumEntries
    | /* empty */
    ;

enumEntries
    : enumEntry
    | enumEntries opt_separators COMMA opt_separators enumEntry

enumEntry
    : opt_modifiers opt_separators simpleIdentifier opt_separators opt_valueArguments opt_separators classBody
    | opt_modifiers opt_separators simpleIdentifier opt_separators opt_valueArguments opt_separators

opt_typeConstraints
    : typeConstraints
    | /* empty */
    ;

typeConstraints
    : WHERE opt_separators typeConstraintList
    ;

typeConstraintList
    : typeConstraint
    | typeConstraintList opt_separators COMMA opt_separators typeConstraint
    ;

typeConstraint
    : annotationList simpleIdentifier opt_separators COLON opt_separators type
    ;

opt_primaryConstr
    : opt_modifiers CONSTRUCTOR opt_separators classParameters
    | classParameters
    ;

classParameters
    : LPAREN opt_separators opt_classParameterList opt_trailing_comma opt_separators RPAREN
    ;

opt_classParameterList
    : classParameterList
    | /* empty */
    ;

classParameterList
    : classParameter
    | classParameterList opt_separators COMMA opt_separators classParameter
    ;

classParameter
    : opt_modifiers opt_val_var opt_separators simpleIdentifier COLON opt_separators type opt_equalExpression
    ;

opt_val_var
    : VAL | VAR
    ;

opt_typeParams
    : typeParameters
    | /* empty */
    ;

typeParameters
    : LANGLE opt_separators typeParameterList opt_trailing_comma opt_separators RANGLE
    ;

typeParameterList
    : typeParameter
    | typeParameterList opt_separators COMMA opt_separators typeParameter
    ;

typeParameter
    : opt_typeParameterModifiers opt_separators simpleIdentifier opt_colonType
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
    : reificationModifier opt_separators
    | varianceModfier opt_separators
    | annotation
    ;

reificationModifier
    : REIFIED
    ;

class_or_interface
    : CLASS | opt_fun INTERFACE
    ;

opt_fun
    : FUN opt_separators
    | /* empty */
    ;

opt_modifiers
    : modifiers
    | /* empty */
    ;

modifiers
    : modifier_item
    | modifiers modifier_item
    ;

modifier_item
    : annotation
    | modifier
    ;

modifier
    : classModifier opt_separators
    | memberModifier opt_separators
    | visibilityModifier opt_separators
    | functionModifier opt_separators
    | propertyModifier opt_separators
    | inheritanceModifier opt_separators
    | parameterModifier opt_separators
    | platformModifier opt_separators
    ;

classModifier
    : ENUM | SEALED | ANNOTATION | DATA | INNER | VALUE ;

memberModifier
    : OVERRIDE | LATEINIT ;

visibilityModifier
    : PUBLIC | PRIVATE | INTERNAL | PROTECTED ;

functionModifier
    : TAILREC | OPERATOR | INFIX | INLINE | EXTERNAL | SUSPEND ;

propertyModifier
    : CONST_LITERAL

inheritanceModifier
    : ABSTRACT | FINAL | OPEN

parameterModifier
    : VARARG | NOINLINE | CROSSINLINE

platformModifier
    : EXPECT_LITERAL | ACTUAL

annotation
    : singleAnnotation opt_separators
    | multiAnnotation opt_separators
    ;

multiAnnotation
    : annotationUseSiteTarget opt_separators LBRACK unescapedAnnotationList RBRACK
    | AT LBRACK unescapedAnnotationList RBRACK
    ;

unescapedAnnotationList
    : unescapedAnnotation
    | unescapedAnnotationList unescapedAnnotation

singleAnnotation
    : annotationUseSiteTarget opt_separators unescapedAnnotation
    | opt_separators AT unescapedAnnotation
    ;

annotationUseSiteTarget
    : opt_separators AT siteTarget opt_separators COLON
    ;

siteTarget
    : FIELD | PROPERTY | GET | SET | RECEIVER | PARAM | SETPARAM | DELEGATE ;

unescapedAnnotation
    : constructorInvocation
    | userType
    ;

constructorInvocation
    : userType opt_separators valueArguments

userType
    : simpleUserType
    | userType opt_separators DOT opt_separators simpleUserType
    ;

simpleUserType
    : simpleIdentifier opt_type_args
    ;

simpleIdentifier
    : IDENTIFIER
    | ABSTRACT | ANNOTATION | BY | CATCH | COMPANION | CONSTRUCTOR | CROSSINLINE | DATA | DYNAMIC | ENUM
    | EXTERNAL | FINAL | FINALLY | GET | IMPORT | INFIX | INIT | INLINE | INNER | INTERNAL | LATEINIT 
    | NOINLINE | OPEN | OPERATOR | OUT | OVERRIDE | PRIVATE | PROTECTED | PUBLIC | REIFIED | SEALED
    | TAILREC | SET | VARARG | WHERE | FIELD | PROPERTY | RECEIVER | PARAM | SETPARAM | DELEGATE | FILE_KW
    | EXPECT_LITERAL | ACTUAL | CONST_LITERAL | SUSPEND | VALUE

opt_type_args
    : opt_separators typeArguments
    | /* empty */
    ;

typeArguments
    : LANGLE opt_separators typeProjectionList opt_trailing_comma opt_separators RANGLE
    ;

typeProjectionList
    : typeProjection
    | typeProjectionList opt_separators COMMA opt_separators typeProjection
    ;

typeProjection
    : opt_typeProjectionalModifiers type
    | MULT
    ;

opt_typeProjectionalModifiers
    : typeProjectionalModifiers
    | /* empty */
    ;

typeProjectionalModifiers
    : typeProjectionalModifier
    | typeProjectionalModifiers typeProjectionalModifier
    ;

typeProjectionalModifier
    : varianceModfier opt_separators
    | annotation
    ;

type
    : opt_typeModifiers type_of_type
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
    : annotation
    | SUSPEND opt_separators
    ;

type_of_type
    : functionType
    | parenthesizedType
    | nullableType
    | typeReference
    | definitelyNonNullableType
    ;

functionType
    : opt_receiverTypeDot functionTypeParameters opt_separators ARROW opt_separators type
    ;

functionTypeParameters
    : LPAREN opt_separators opt_parameter_or_type_list opt_trailing_comma opt_separators RPAREN
    ;

opt_parameter_or_type_list
    : parameter_or_type_list
    | /* empty */
    ;

parameter_or_type_list
    : parameter_or_type
    | parameter_or_type_list opt_separators COMMA opt_separators parameter_or_type
    ;

parameter_or_type
    : parameter
    | type
    ;

parameter
    : simpleIdentifier opt_separators COLON opt_separators type
    ;

parenthesizedType
    : LPAREN opt_separators type opt_separators RPAREN
    ;

nullableType
    : typeReference opt_separators quesList
    | parenthesizedType opt_separators quesList
    ;

typeReference
    : userType
    ;

quesList
    : QUEST
    | quesList QUEST
    ;

definitelyNonNullableType
    : opt_typeModifiers userType_or_parenthesizedUserType opt_separators AMPER opt_separators opt_typeModifiers userType_or_parenthesizedUserType
    ;

userType_or_parenthesizedUserType
    : userType
    | parenthesizedType
    ;

opt_receiverTypeDot
    : receiverType opt_separators DOT opt_separators
    | /* empty */
    ;

receiverType
    : opt_typeModifiers parenthesizedType
    | opt_typeModifiers nullableType
    | opt_typeModifiers typeReference
    ;

varianceModfier
    : IN | OUT ;

opt_trailing_comma
    : opt_separators COMMA
    | /* empty */
    ;

opt_valueArguments
    : valueArguments
    | /* empty */
    ;

valueArguments
    : LPAREN opt_separators opt_valueArgumentList opt_trailing_comma opt_separators RPAREN
    ;

opt_valueArgumentList
    : valueArgumentList
    | /* empty */
    ;

valueArgumentList
    : valueArgument
    | valueArgumentList opt_separators COMMA opt_separators valueArgument
    ;

valueArgument
    : opt_annotation opt_separators opt_namedArgument opt_separators opt_mult opt_separators expression
    ;

opt_annotation
    : annotation
    | /* empty */
    ;

opt_namedArgument
    : simpleIdentifier opt_separators ASSIGNMENT
    ;

opt_mult
    : MULT
    | /* empty */
    ;

expression
    : disjunction
    ;

disjunction
    : conjunction
    | disjunction opt_separators OROR opt_separators conjunction
    ;

conjunction
    : equality
    | conjunction opt_separators ANDAND opt_separators equality
    ;

equality
    : comparison
    | equality equalityOperator opt_separators comparison
    ;

equalityOperator
    : EXCL_EQ | EXCL_EQEQ | EQEQ | EQEQEQ
    ;

comparison
    : genericCallLikeComparison
    | comparison comparisonOperator opt_separators genericCallLikeComparison
    ;

comparisonOperator
    : LANGLE | RANGE | LE | GE
    ;

genericCallLikeComparison
    : infixOperation
    | infixOperation callSuffixList

callSuffixList
    : callSuffix
    | callSuffixList callSuffix
    ;

infixOperation
    : elvisExpression
    | infixOperation inOperator opt_separators elvisExpression
    | infixOperation isOperator opt_separators type
    ;

inOperator
    : IN | NOT_IN
    ;

isOperator
    : IS | NOT_IS
    ;

elvisExpression
    : infixFunctionCall
    | elvisExpression opt_separators ELVIS opt_separators infixFunctionCall
    ;

infixFunctionCall
    : rangeExpression
    | infixFunctionCall simpleIdentifier opt_separators rangeExpression
    ;

rangeExpression
    : additiveExpression
    | rangeExpression RANGE opt_separators additiveExpression
    | rangeExpression RANGE_UNTIL opt_separators additiveExpression
    ;

additiveExpression
    : multiplicativeExpression
    | additiveExpression additiveOperator opt_separators multiplicativeExpression
    ;

additiveOperator
    : ADD | SUB
    ;

multiplicativeExpression
    : asExpression
    | multiplicativeExpression multiplicativeOperator opt_separators asExpression
    ;

multiplicativeOperator
    : MULT | DIV | MOD
    ;

asExpression
    : prefixUnaryExpression
    | asExpression opt_separators asOperator opt_separators type
    ;

asOperator
    : AS | AS_SAFE
    ;

prefixUnaryExpression
    : opt_unaryPrefix postfixUnaryExpression
    ;

postfixUnaryExpression
    : primaryExpression
    | postfixUnaryExpression postfixUnarySuffix

primaryExpression
    : parenthesizedExpression
    | simpleIdentifier
    | literalConstant
    | STRING_LITERAL
    | callableReference
    | functionLiteral
    | objectLiteral
    | collectionLiteral
    | thisExpression
    | superExpression
    | ifExpression
    | whenExpression
    | tryExpression
    | jumpExpression
    ;

jumpExpression
    : THROW opt_separators expression
    | RETURN opt_expression
    | RETURN_AT opt_expression
    | CONTINUE
    | CONTINUE_AT
    | BREAK
    | BREAK_AT
    ;

opt_expression
    : expression
    | /* empty */
    ;

tryExpression
    : TRY opt_separators block opt_separators catchBlockList opt_finallyBlock
    | TRY opt_separators block opt_separators finallyBlock
    ;

opt_finallyBlock
    : finallyBlock
    | /* empty */
    ;

finallyBlock
    : FINALLY opt_separators block
    ;

catchBlockList
    : catchBlock
    | catchBlockList opt_separators catchBlock
    ;

catchBlock
    : CATCH opt_separators LPAREN annotationList simpleIdentifier COLON type opt_trailing_comma RPAREN opt_separators block
    ;

whenExpression
    : WHEN opt_separators whenSubject opt_separators LCURL opt_separators whenEntryList opt_separators RCURL
    | WHEN opt_separators LCURL opt_separators whenEntryList opt_separators RCURL
    ;

whenSubject
    : LPAREN opt_valDeclaration expression RPAREN
    ;

opt_valDeclaration
    : annotationList opt_separators VAL opt_separators variableDeclaration opt_separators ASSIGNMENT opt_separators
    ;

whenEntryList
    : whenEntry
    | whenEntryList opt_separators whenEntry
    ;

whenEntry
    : whenConditionList opt_trailing_comma opt_separators ARROW opt_separators controlStructureBody opt_semi
    | ELSE opt_separators ARROW opt_separators controlStructureBody opt_semi
    ;

whenConditionList
    : whenCondition
    | whenConditionList opt_separators COMMA opt_separators whenCondition
    ;

whenCondition
    : expression
    | rangeTest
    | typeTest
    ;

rangeTest
    : inOperator opt_separators expression
    ;

typeTest
    : isOperator opt_separators type
    ;

opt_semi
    : semi
    | /* empty */
    ;

ifExpression
    : IF opt_separators LPAREN opt_separators expression opt_separators RPAREN opt_separators controlStructureBody
    | IF opt_separators LPAREN opt_separators expression opt_separators RPAREN opt_separators SEMICOLON
    | IF opt_separators LPAREN opt_separators expression opt_separators RPAREN opt_separators opt_controlStructureBody opt_separators opt_semicolon opt_separators ELSE opt_separators
    ;

opt_semicolon
    : SEMICOLON
    | /* empty */
    ;

superExpression
    : SUPER opt_angle_type AT simpleIdentifier
    | SUPER opt_angle_type
    | SUPER_AT

opt_angle_type
    : LANGLE opt_separators type opt_separators LANGLE
    ;

thisExpression
    : THIS
    | THIS_AT
    ;

collectionLiteral
    : LBRACK opt_separators opt_expressionList opt_trailing_comma opt_separators RBRACK
    ;

opt_expressionList
    : expressionList
    | /* empty */
    ;

objectLiteral
    : opt_data opt_separators OBJECT opt_colon_delegationSpecs opt_separators classBody
    | opt_data opt_separators OBJECT opt_colon_delegationSpecs
    ;

classBody
    : LCURL opt_separators classMemberDeclarations opt_separators RCURL
    ;

classMemberDeclarations
    : classMemberDeclaration
    | classMemberDeclarations semis classMemberDeclaration
    ;

classMemberDeclaration
    : declaration
    | companionObject
    | anonymousInitializer
    | secondaryConstructor
    ;

secondaryConstructor
    : opt_modifiers CONSTRUCTOR opt_separators functionValueParameters opt_colon_constructorDelegationCall opt_separators block
    | opt_modifiers CONSTRUCTOR opt_separators functionValueParameters opt_colon_constructorDelegationCall opt_separators
    ;

opt_colon_constructorDelegationCall
    : colon_constructorDelegationCall
    | /* empty */
    ;

colon_constructorDelegationCall
    : opt_separators COLON opt_separators constructorDelegationCall
    ;

constructorDelegationCall
    : THIS opt_separators valueArguments
    | SUPER opt_separators valueArguments

functionValueParameters
    : LPAREN opt_separators opt_functionValueParameterList opt_trailing_comma opt_separators RPAREN;

opt_functionValueParameterList
    : functionValueParameterList
    | /* empty */
    ;

functionValueParameterList
    : functionValueParameter
    | functionValueParameterList opt_separators COMMA opt_separators functionValueParameter

functionValueParameter
    : opt_parameterModifiers parameter opt_equalExpression
    ;

opt_parameterModifiers
    : parameterModifiers
    | /* empty */
    ;

parameterModifiers
    : modifiers

anonymousInitializer
    : INIT opt_separators block
    ;

companionObject
    : opt_modifiers COMPANION opt_separators opt_data opt_separators OBJECT opt_simpleIdenrifier opt_colon_delegationSpecs opt_separators classBody
    | opt_modifiers COMPANION opt_separators opt_data opt_separators OBJECT opt_simpleIdenrifier opt_colon_delegationSpecs
    ;

opt_simpleIdenrifier
    : opt_separators simpleIdentifier
    | /* empty */
    ;

opt_colon_delegationSpecs
    : colon_delegationSpecs
    | /* empty */
    ;

colon_delegationSpecs
    : opt_separators COLON opt_separators delegationSpecifiers
    ;

delegationSpecifiers
    : annotatedDelegationSpecifier
    | delegationSpecifiers opt_separators COMMA opt_separators annotatedDelegationSpecifier
    ;

annotatedDelegationSpecifier
    : annotationList opt_separators delegationSpecifier

delegationSpecifier
    : constructorInvocation
    | explicitDelegation
    | userType
    | SUSPEND opt_separators functionType

explicitDelegation
    : userType opt_separators BY opt_separators expression
    | functionType opt_separators BY opt_separators expression
    ;

opt_data 
    : DATA
    | /* empty */
    ;

functionLiteral
    : lambdaLiteral
    | anonymousFunction
    ;

anonymousFunction
    : opt_suspend opt_separators FUN opt_typeDot opt_separators parametersWithOptionalType opt_colonType opt_separators opt_typeConstraints opt_separators opt_functionBody
    ;

opt_functionBody
    : functionBody
    | /* empty */
    ;

functionBody
    : block
    | ASSIGNMENT opt_separators expression
    ;

block
    : LCURL opt_separators statements opt_separators RCURL
    ;

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

statement
    : statementPrefixes statementContent
    ;

statementPrefixes
    : statementPrefixes statementPrefix
    | /* empty */
    ;

statementPrefix
    : label
    | annotation
    ;

statementContent
    : declaration
    | assignment
    | loopStatement
    | expression
    ;

loopStatement
    : forStatement
    | whileStatement
    | doWhileStatement
    ;

doWhileStatement
    : DO opt_separators opt_controlStructureBody opt_separators WHILE opt_separators LPAREN expression RPAREN
    ;

whileStatement
    : WHILE opt_separators LPAREN expression RPAREN opt_separators controlStructureBody
    | WHILE opt_separators LPAREN expression RPAREN opt_separators SEMICOLON
    ;

forStatement
    : FOR opt_separators LPAREN annotationList variableDeclaration IN expression RPAREN opt_separators opt_controlStructureBody
    | FOR opt_separators LPAREN annotationList multiVariableDeclaration IN expression RPAREN opt_separators opt_controlStructureBody
    ;

opt_controlStructureBody
    : controlStructureBody
    | /* empty */
    ;

controlStructureBody
    : block
    | statement
    ;

assignment
    : directlyAssignableExpression ASSIGNMENT opt_separators expression
    | assignableExpression assignmentAndOperator opt_separators expression
    ;

assignmentAndOperator
    : ADD_ASSIGN | SUB_ASSIGN | MULT_ASSIGN | DIV_ASSIGN | MOD_ASSIGN
    ;

assignableExpression
    : prefixUnaryExpression
    | parenthesizedAssignableExpression
    ;

parenthesizedAssignableExpression
    : LPAREN opt_separators assignableExpression opt_separators RPAREN
    ;

directlyAssignableExpression
    : postfixUnaryExpression assignableSuffix
    | simpleIdentifier
    | parenthesizedDirectlyAssignableExpression
    ;

parenthesizedDirectlyAssignableExpression
    : LPAREN opt_separators directlyAssignableExpression opt_separators RPAREN
    ;

assignableSuffix
    : typeArguments
    | indexingSuffix
    | navigationSuffix
    ;

parametersWithOptionalType
    : LPAREN opt_separators opt_functionValueParameterWithOptionalTypeList opt_trailing_comma opt_separators RPAREN
    ;

opt_functionValueParameterWithOptionalTypeList
    : functionValueParameterWithOptionalTypeList
    | /* empty */
    ;

functionValueParameterWithOptionalTypeList
    : functionValueParameterWithOptionalType
    | functionValueParameterWithOptionalTypeList opt_separators COMMA opt_separators functionValueParameterWithOptionalType
    ;

functionValueParameterWithOptionalType
    : opt_modifiers parameterWithOptionalType opt_equalExpression
    ;

parameterWithOptionalType
    : simpleIdentifier opt_separators
    | simpleIdentifier opt_separators COLON opt_separators type
    ;

opt_equalExpression
    : equalExpression
    | /* empty */
    ;

equalExpression
    : opt_separators ASSIGNMENT opt_separators expression
    ;

opt_colonType
    : opt_separators COLON opt_separators type
    | /* empty */
    ;

opt_typeDot
    : opt_separators type opt_separators DOT
    | /* empty */
    ;

opt_suspend
    : SUSPEND
    | /* empty */
    ;

callableReference
    : opt_receiverType DOUBLE_COLON opt_separators simpleIdentifier
    | opt_receiverType DOUBLE_COLON opt_separators CLASS
    ;

opt_receiverType
    : receiverType
    | /*empty*/
    ;

literalConstant
    : BooleanLiteral
    | INTEGER_LITERAL
    | INTEGER_NO_ZERO
    | HEX_LITERAL
    | BIN_LITERAL
    | CHARACTER_LITERAL
    | REAL_LITERAL
    | NULL_LITERAL
    | LONG_LITERAL
    | UNSIGNED_LITERAL
    ;

BooleanLiteral
    : TRUE | FALSE
    ;

postfixUnarySuffix
    : postfixUnaryOperator | typeArguments | callSuffix | indexingSuffix | navigationSuffix
    ;

navigationSuffix
    : memberAccessOperator opt_separators simpleIdentifier
    | memberAccessOperator opt_separators parenthesizedExpression
    | memberAccessOperator opt_separators CLASS
    ;

memberAccessOperator
    : opt_separators DOT
    | opt_separators SAFE_DOT
    | DOUBLE_COLON
    ;

parenthesizedExpression
    : LPAREN opt_separators expression opt_separators RPAREN
    ;

indexingSuffix
    : LBRACK opt_separators expressionList opt_trailing_comma opt_separators RBRACK
    ;

expressionList
    : expression
    | expressionList opt_separators COMMA opt_separators expression
    ;

callSuffix
    : opt_type_args opt_valueArguments annotatedLambda
    | opt_type_args valueArguments
    ;

annotatedLambda
    : annotationList opt_label opt_separators lambdaLiteral
    ;

lambdaLiteral
    : LCURL opt_separators opt_param_ARROW statements opt_separators RCURL
    ;

opt_param_ARROW
    : opt_lambdaParameters opt_separators ARROW opt_separators
    | /* empty */
    ;

opt_lambdaParameters
    : lambdaParameters
    | /* empty */
    ;

lambdaParameters
    : lambdaParameterList opt_trailing_comma
    ;

lambdaParameterList
    : lambdaParameter
    | lambdaParameterList opt_separators COMMA opt_separators lambdaParameter
    ;

lambdaParameter
    : variableDeclaration
    | multiVariableDeclaration opt_separators opt_type_annotation
    ;

variableDeclaration
    : annotationList opt_separators simpleIdentifier opt_type_annotation
    ;

multiVariableDeclaration
    : LPAREN opt_separators variableDeclaration variableDeclarationList opt_trailing_comma opt_separators RPAREN
    ;

variableDeclarationList
    : variableDeclaration
    | variableDeclarationList opt_separators COMMA opt_separators variableDeclaration
    ;

opt_type_annotation
    : opt_separators COLON opt_separators type
    | /* empty */

annotationList
    : annotation
    | annotationList annotation
    ;

opt_label
    : label
    | /* empty */
    ;

postfixUnaryOperator
    : INCR | DECR | DOUBLE_EXCL

opt_unaryPrefix
    : unaryPrefix
    | /* empty */
    ;

unaryPrefix
    : annotation
    | label
    | prefixUnaryOperator opt_separators
    ;

label
    : simpleIdentifier AT opt_separators
    ;

prefixUnaryOperator
    : INCR | DECR | SUB | ADD | NOT




%%

void yyerror(const char *s) {
    fprintf(stderr, "Lexical/Syntax Error at line %d: %s\n", line_num, s);
    has_error = 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }
    
    if (yyparse() == 0 && has_error == 0) {
        printf("\nResult: Program is correct.\n");
    } else {
        printf("\nResult: Program is NOT correct (errors found).\n");
    }
    return 0;
}
