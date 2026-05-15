/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    SOFT_KW = 259,                 /* SOFT_KW  */
    STRING_LIT = 260,              /* STRING_LIT  */
    INT_LIT = 261,                 /* INT_LIT  */
    REAL_LIT = 262,                /* REAL_LIT  */
    CHAR_LIT = 263,                /* CHAR_LIT  */
    BOOL_LIT = 264,                /* BOOL_LIT  */
    NL = 265,                      /* NL  */
    NULL_LIT = 266,                /* NULL_LIT  */
    PACKAGE = 267,                 /* PACKAGE  */
    IMPORT = 268,                  /* IMPORT  */
    CLASS = 269,                   /* CLASS  */
    INTERFACE = 270,               /* INTERFACE  */
    OBJECT = 271,                  /* OBJECT  */
    FUN = 272,                     /* FUN  */
    VAL = 273,                     /* VAL  */
    VAR = 274,                     /* VAR  */
    IF = 275,                      /* IF  */
    ELSE = 276,                    /* ELSE  */
    WHEN = 277,                    /* WHEN  */
    FOR = 278,                     /* FOR  */
    WHILE = 279,                   /* WHILE  */
    DO = 280,                      /* DO  */
    RETURN = 281,                  /* RETURN  */
    BREAK = 282,                   /* BREAK  */
    CONTINUE = 283,                /* CONTINUE  */
    THROW = 284,                   /* THROW  */
    TRY = 285,                     /* TRY  */
    CATCH = 286,                   /* CATCH  */
    FINALLY = 287,                 /* FINALLY  */
    THIS = 288,                    /* THIS  */
    SUPER = 289,                   /* SUPER  */
    IN = 290,                      /* IN  */
    NOT_IN = 291,                  /* NOT_IN  */
    IS = 292,                      /* IS  */
    NOT_IS = 293,                  /* NOT_IS  */
    AS = 294,                      /* AS  */
    AS_SAFE = 295,                 /* AS_SAFE  */
    TYPEALIAS = 296,               /* TYPEALIAS  */
    ENUM = 297,                    /* ENUM  */
    INIT = 298,                    /* INIT  */
    CONSTRUCTOR = 299,             /* CONSTRUCTOR  */
    BY = 300,                      /* BY  */
    GET = 301,                     /* GET  */
    SET = 302,                     /* SET  */
    EQEQEQ = 303,                  /* EQEQEQ  */
    NEQEQ = 304,                   /* NEQEQ  */
    EQEQ = 305,                    /* EQEQ  */
    NEQ = 306,                     /* NEQ  */
    LEQ = 307,                     /* LEQ  */
    GEQ = 308,                     /* GEQ  */
    ANDAND = 309,                  /* ANDAND  */
    OROR = 310,                    /* OROR  */
    INCR = 311,                    /* INCR  */
    DECR = 312,                    /* DECR  */
    PLUS_EQ = 313,                 /* PLUS_EQ  */
    MINUS_EQ = 314,                /* MINUS_EQ  */
    STAR_EQ = 315,                 /* STAR_EQ  */
    SLASH_EQ = 316,                /* SLASH_EQ  */
    MOD_EQ = 317,                  /* MOD_EQ  */
    RANGE = 318,                   /* RANGE  */
    RANGE_UNTIL = 319,             /* RANGE_UNTIL  */
    ARROW = 320,                   /* ARROW  */
    SAFE_DOT = 321,                /* SAFE_DOT  */
    ELVIS = 322,                   /* ELVIS  */
    COLONCOLON = 323,              /* COLONCOLON  */
    DBL_EXCL = 324,                /* DBL_EXCL  */
    INFIX_FN = 325,                /* INFIX_FN  */
    UMINUS = 326,                  /* UMINUS  */
    UPLUS = 327,                   /* UPLUS  */
    THEN = 328                     /* THEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 77 "../src/parser.y"

    char *str;

#line 141 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
