/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 14 "../src/parser.y"

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

#line 146 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_SOFT_KW = 4,                    /* SOFT_KW  */
  YYSYMBOL_STRING_LIT = 5,                 /* STRING_LIT  */
  YYSYMBOL_INT_LIT = 6,                    /* INT_LIT  */
  YYSYMBOL_REAL_LIT = 7,                   /* REAL_LIT  */
  YYSYMBOL_CHAR_LIT = 8,                   /* CHAR_LIT  */
  YYSYMBOL_BOOL_LIT = 9,                   /* BOOL_LIT  */
  YYSYMBOL_NL = 10,                        /* NL  */
  YYSYMBOL_NULL_LIT = 11,                  /* NULL_LIT  */
  YYSYMBOL_PACKAGE = 12,                   /* PACKAGE  */
  YYSYMBOL_IMPORT = 13,                    /* IMPORT  */
  YYSYMBOL_CLASS = 14,                     /* CLASS  */
  YYSYMBOL_INTERFACE = 15,                 /* INTERFACE  */
  YYSYMBOL_OBJECT = 16,                    /* OBJECT  */
  YYSYMBOL_FUN = 17,                       /* FUN  */
  YYSYMBOL_VAL = 18,                       /* VAL  */
  YYSYMBOL_VAR = 19,                       /* VAR  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_ELSE = 21,                      /* ELSE  */
  YYSYMBOL_WHEN = 22,                      /* WHEN  */
  YYSYMBOL_FOR = 23,                       /* FOR  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_DO = 25,                        /* DO  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_BREAK = 27,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 28,                  /* CONTINUE  */
  YYSYMBOL_THROW = 29,                     /* THROW  */
  YYSYMBOL_TRY = 30,                       /* TRY  */
  YYSYMBOL_CATCH = 31,                     /* CATCH  */
  YYSYMBOL_FINALLY = 32,                   /* FINALLY  */
  YYSYMBOL_THIS = 33,                      /* THIS  */
  YYSYMBOL_SUPER = 34,                     /* SUPER  */
  YYSYMBOL_IN = 35,                        /* IN  */
  YYSYMBOL_NOT_IN = 36,                    /* NOT_IN  */
  YYSYMBOL_IS = 37,                        /* IS  */
  YYSYMBOL_NOT_IS = 38,                    /* NOT_IS  */
  YYSYMBOL_AS = 39,                        /* AS  */
  YYSYMBOL_AS_SAFE = 40,                   /* AS_SAFE  */
  YYSYMBOL_TYPEALIAS = 41,                 /* TYPEALIAS  */
  YYSYMBOL_ENUM = 42,                      /* ENUM  */
  YYSYMBOL_INIT = 43,                      /* INIT  */
  YYSYMBOL_CONSTRUCTOR = 44,               /* CONSTRUCTOR  */
  YYSYMBOL_BY = 45,                        /* BY  */
  YYSYMBOL_GET = 46,                       /* GET  */
  YYSYMBOL_SET = 47,                       /* SET  */
  YYSYMBOL_EQEQEQ = 48,                    /* EQEQEQ  */
  YYSYMBOL_NEQEQ = 49,                     /* NEQEQ  */
  YYSYMBOL_EQEQ = 50,                      /* EQEQ  */
  YYSYMBOL_NEQ = 51,                       /* NEQ  */
  YYSYMBOL_LEQ = 52,                       /* LEQ  */
  YYSYMBOL_GEQ = 53,                       /* GEQ  */
  YYSYMBOL_ANDAND = 54,                    /* ANDAND  */
  YYSYMBOL_OROR = 55,                      /* OROR  */
  YYSYMBOL_INCR = 56,                      /* INCR  */
  YYSYMBOL_DECR = 57,                      /* DECR  */
  YYSYMBOL_PLUS_EQ = 58,                   /* PLUS_EQ  */
  YYSYMBOL_MINUS_EQ = 59,                  /* MINUS_EQ  */
  YYSYMBOL_STAR_EQ = 60,                   /* STAR_EQ  */
  YYSYMBOL_SLASH_EQ = 61,                  /* SLASH_EQ  */
  YYSYMBOL_MOD_EQ = 62,                    /* MOD_EQ  */
  YYSYMBOL_RANGE = 63,                     /* RANGE  */
  YYSYMBOL_RANGE_UNTIL = 64,               /* RANGE_UNTIL  */
  YYSYMBOL_ARROW = 65,                     /* ARROW  */
  YYSYMBOL_SAFE_DOT = 66,                  /* SAFE_DOT  */
  YYSYMBOL_ELVIS = 67,                     /* ELVIS  */
  YYSYMBOL_COLONCOLON = 68,                /* COLONCOLON  */
  YYSYMBOL_DBL_EXCL = 69,                  /* DBL_EXCL  */
  YYSYMBOL_70_ = 70,                       /* '='  */
  YYSYMBOL_71_ = 71,                       /* '<'  */
  YYSYMBOL_72_ = 72,                       /* '>'  */
  YYSYMBOL_INFIX_FN = 73,                  /* INFIX_FN  */
  YYSYMBOL_74_ = 74,                       /* '+'  */
  YYSYMBOL_75_ = 75,                       /* '-'  */
  YYSYMBOL_76_ = 76,                       /* '*'  */
  YYSYMBOL_77_ = 77,                       /* '/'  */
  YYSYMBOL_78_ = 78,                       /* '%'  */
  YYSYMBOL_79_ = 79,                       /* '!'  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 81,                     /* UPLUS  */
  YYSYMBOL_82_ = 82,                       /* '.'  */
  YYSYMBOL_83_ = 83,                       /* '('  */
  YYSYMBOL_84_ = 84,                       /* '['  */
  YYSYMBOL_THEN = 85,                      /* THEN  */
  YYSYMBOL_86_ = 86,                       /* ';'  */
  YYSYMBOL_87_ = 87,                       /* '@'  */
  YYSYMBOL_88_ = 88,                       /* ')'  */
  YYSYMBOL_89_ = 89,                       /* ':'  */
  YYSYMBOL_90_ = 90,                       /* ','  */
  YYSYMBOL_91_ = 91,                       /* '{'  */
  YYSYMBOL_92_ = 92,                       /* '}'  */
  YYSYMBOL_93_ = 93,                       /* '?'  */
  YYSYMBOL_94_ = 94,                       /* ']'  */
  YYSYMBOL_95___ = 95,                     /* '_'  */
  YYSYMBOL_YYACCEPT = 96,                  /* $accept  */
  YYSYMBOL_file = 97,                      /* file  */
  YYSYMBOL_opt_seps = 98,                  /* opt_seps  */
  YYSYMBOL_seps = 99,                      /* seps  */
  YYSYMBOL_sep = 100,                      /* sep  */
  YYSYMBOL_topItems = 101,                 /* topItems  */
  YYSYMBOL_topItem = 102,                  /* topItem  */
  YYSYMBOL_packageDecl = 103,              /* packageDecl  */
  YYSYMBOL_importDecl = 104,               /* importDecl  */
  YYSYMBOL_qualifiedName = 105,            /* qualifiedName  */
  YYSYMBOL_identifier = 106,               /* identifier  */
  YYSYMBOL_declaration = 107,              /* declaration  */
  YYSYMBOL_modifiers = 108,                /* modifiers  */
  YYSYMBOL_modifierItem = 109,             /* modifierItem  */
  YYSYMBOL_annotation = 110,               /* annotation  */
  YYSYMBOL_classDecl = 111,                /* classDecl  */
  YYSYMBOL_objectDecl = 112,               /* objectDecl  */
  YYSYMBOL_opt_typeParams = 113,           /* opt_typeParams  */
  YYSYMBOL_typeParamList = 114,            /* typeParamList  */
  YYSYMBOL_typeParam = 115,                /* typeParam  */
  YYSYMBOL_opt_primCtor = 116,             /* opt_primCtor  */
  YYSYMBOL_opt_comma = 117,                /* opt_comma  */
  YYSYMBOL_ctorParamList = 118,            /* ctorParamList  */
  YYSYMBOL_ctorParam = 119,                /* ctorParam  */
  YYSYMBOL_opt_supertypes = 120,           /* opt_supertypes  */
  YYSYMBOL_supertypeList = 121,            /* supertypeList  */
  YYSYMBOL_supertype = 122,                /* supertype  */
  YYSYMBOL_opt_classBody = 123,            /* opt_classBody  */
  YYSYMBOL_classBody = 124,                /* classBody  */
  YYSYMBOL_members = 125,                  /* members  */
  YYSYMBOL_member = 126,                   /* member  */
  YYSYMBOL_initBlock = 127,                /* initBlock  */
  YYSYMBOL_secondaryCtor = 128,            /* secondaryCtor  */
  YYSYMBOL_opt_ctorParams = 129,           /* opt_ctorParams  */
  YYSYMBOL_opt_ctorDelegation = 130,       /* opt_ctorDelegation  */
  YYSYMBOL_enumEntries = 131,              /* enumEntries  */
  YYSYMBOL_enumEntry = 132,                /* enumEntry  */
  YYSYMBOL_funDecl = 133,                  /* funDecl  */
  YYSYMBOL_funHead = 134,                  /* funHead  */
  YYSYMBOL_opt_paramList = 135,            /* opt_paramList  */
  YYSYMBOL_paramList = 136,                /* paramList  */
  YYSYMBOL_param = 137,                    /* param  */
  YYSYMBOL_opt_retType = 138,              /* opt_retType  */
  YYSYMBOL_opt_whereClause = 139,          /* opt_whereClause  */
  YYSYMBOL_typeConstraintList = 140,       /* typeConstraintList  */
  YYSYMBOL_typeConstraint = 141,           /* typeConstraint  */
  YYSYMBOL_opt_funBody = 142,              /* opt_funBody  */
  YYSYMBOL_propDecl = 143,                 /* propDecl  */
  YYSYMBOL_declTarget = 144,               /* declTarget  */
  YYSYMBOL_destructList = 145,             /* destructList  */
  YYSYMBOL_opt_init = 146,                 /* opt_init  */
  YYSYMBOL_opt_accessors = 147,            /* opt_accessors  */
  YYSYMBOL_accessor = 148,                 /* accessor  */
  YYSYMBOL_typeAliasDecl = 149,            /* typeAliasDecl  */
  YYSYMBOL_type = 150,                     /* type  */
  YYSYMBOL_typeRef = 151,                  /* typeRef  */
  YYSYMBOL_opt_typeArgList = 152,          /* opt_typeArgList  */
  YYSYMBOL_typeArgList = 153,              /* typeArgList  */
  YYSYMBOL_typeArgItem = 154,              /* typeArgItem  */
  YYSYMBOL_block = 155,                    /* block  */
  YYSYMBOL_stmts = 156,                    /* stmts  */
  YYSYMBOL_stmt = 157,                     /* stmt  */
  YYSYMBOL_labelStmt = 158,                /* labelStmt  */
  YYSYMBOL_forStmt = 159,                  /* forStmt  */
  YYSYMBOL_forVar = 160,                   /* forVar  */
  YYSYMBOL_whileStmt = 161,                /* whileStmt  */
  YYSYMBOL_doWhileStmt = 162,              /* doWhileStmt  */
  YYSYMBOL_expr = 163,                     /* expr  */
  YYSYMBOL_primary = 164,                  /* primary  */
  YYSYMBOL_jumpExpr = 165,                 /* jumpExpr  */
  YYSYMBOL_lambda = 166,                   /* lambda  */
  YYSYMBOL_lambdaParamList = 167,          /* lambdaParamList  */
  YYSYMBOL_lambdaParam = 168,              /* lambdaParam  */
  YYSYMBOL_ifExpr = 169,                   /* ifExpr  */
  YYSYMBOL_whenExpr = 170,                 /* whenExpr  */
  YYSYMBOL_whenEntries = 171,              /* whenEntries  */
  YYSYMBOL_whenEntry = 172,                /* whenEntry  */
  YYSYMBOL_whenCondList = 173,             /* whenCondList  */
  YYSYMBOL_whenCond = 174,                 /* whenCond  */
  YYSYMBOL_tryExpr = 175,                  /* tryExpr  */
  YYSYMBOL_catchList = 176,                /* catchList  */
  YYSYMBOL_catchClause = 177,              /* catchClause  */
  YYSYMBOL_opt_modifiers = 178,            /* opt_modifiers  */
  YYSYMBOL_objectLit = 179,                /* objectLit  */
  YYSYMBOL_opt_args = 180,                 /* opt_args  */
  YYSYMBOL_argList = 181,                  /* argList  */
  YYSYMBOL_arg = 182                       /* arg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3545

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  304
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  613

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,     2,     2,    78,     2,     2,
      83,    88,    76,    74,    90,    75,    82,    77,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    89,    86,
      71,    70,    72,    93,    87,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    94,     2,    95,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,     2,    92,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    73,    80,    81,    85
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   137,   137,   138,   141,   141,   144,   145,   147,   147,
     150,   151,   152,   158,   159,   160,   168,   173,   175,   177,
     182,   183,   196,   197,   198,   199,   200,   201,   202,   210,
     211,   212,   213,   214,   218,   219,   223,   224,   225,   229,
     230,   231,   232,   236,   238,   243,   245,   250,   251,   255,
     256,   260,   261,   265,   266,   267,   268,   269,   272,   272,
     275,   276,   280,   281,   282,   283,   284,   285,   289,   290,
     294,   295,   299,   300,   301,   305,   306,   310,   311,   315,
     316,   317,   327,   328,   329,   330,   331,   335,   339,   342,
     343,   346,   347,   348,   352,   353,   360,   361,   362,   363,
     367,   376,   377,   378,   379,   383,   384,   388,   389,   393,
     394,   398,   399,   403,   404,   408,   409,   413,   417,   418,
     419,   423,   425,   430,   431,   432,   433,   437,   438,   439,
     440,   444,   445,   446,   450,   451,   452,   457,   458,   459,
     460,   461,   465,   480,   481,   482,   483,   487,   488,   489,
     490,   494,   495,   499,   500,   504,   505,   506,   507,   515,
     516,   520,   521,   522,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   547,   551,   552,   556,
     557,   558,   562,   563,   567,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   612,   613,   614,   615,   616,   617,   621,   622,
     623,   624,   625,   626,   627,   628,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   659,   660,
     661,   662,   663,   664,   668,   669,   673,   674,   675,   676,
     680,   681,   685,   686,   687,   688,   689,   690,   694,   695,
     699,   700,   704,   705,   709,   710,   711,   712,   713,   717,
     718,   719,   723,   724,   728,   732,   733,   737,   741,   742,
     746,   747,   751,   752,   753
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "SOFT_KW", "STRING_LIT", "INT_LIT", "REAL_LIT", "CHAR_LIT", "BOOL_LIT",
  "NL", "NULL_LIT", "PACKAGE", "IMPORT", "CLASS", "INTERFACE", "OBJECT",
  "FUN", "VAL", "VAR", "IF", "ELSE", "WHEN", "FOR", "WHILE", "DO",
  "RETURN", "BREAK", "CONTINUE", "THROW", "TRY", "CATCH", "FINALLY",
  "THIS", "SUPER", "IN", "NOT_IN", "IS", "NOT_IS", "AS", "AS_SAFE",
  "TYPEALIAS", "ENUM", "INIT", "CONSTRUCTOR", "BY", "GET", "SET", "EQEQEQ",
  "NEQEQ", "EQEQ", "NEQ", "LEQ", "GEQ", "ANDAND", "OROR", "INCR", "DECR",
  "PLUS_EQ", "MINUS_EQ", "STAR_EQ", "SLASH_EQ", "MOD_EQ", "RANGE",
  "RANGE_UNTIL", "ARROW", "SAFE_DOT", "ELVIS", "COLONCOLON", "DBL_EXCL",
  "'='", "'<'", "'>'", "INFIX_FN", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'!'", "UMINUS", "UPLUS", "'.'", "'('", "'['", "THEN", "';'", "'@'",
  "')'", "':'", "','", "'{'", "'}'", "'?'", "']'", "'_'", "$accept",
  "file", "opt_seps", "seps", "sep", "topItems", "topItem", "packageDecl",
  "importDecl", "qualifiedName", "identifier", "declaration", "modifiers",
  "modifierItem", "annotation", "classDecl", "objectDecl",
  "opt_typeParams", "typeParamList", "typeParam", "opt_primCtor",
  "opt_comma", "ctorParamList", "ctorParam", "opt_supertypes",
  "supertypeList", "supertype", "opt_classBody", "classBody", "members",
  "member", "initBlock", "secondaryCtor", "opt_ctorParams",
  "opt_ctorDelegation", "enumEntries", "enumEntry", "funDecl", "funHead",
  "opt_paramList", "paramList", "param", "opt_retType", "opt_whereClause",
  "typeConstraintList", "typeConstraint", "opt_funBody", "propDecl",
  "declTarget", "destructList", "opt_init", "opt_accessors", "accessor",
  "typeAliasDecl", "type", "typeRef", "opt_typeArgList", "typeArgList",
  "typeArgItem", "block", "stmts", "stmt", "labelStmt", "forStmt",
  "forVar", "whileStmt", "doWhileStmt", "expr", "primary", "jumpExpr",
  "lambda", "lambdaParamList", "lambdaParam", "ifExpr", "whenExpr",
  "whenEntries", "whenEntry", "whenCondList", "whenCond", "tryExpr",
  "catchList", "catchClause", "opt_modifiers", "objectLit", "opt_args",
  "argList", "arg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-466)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-267)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,  -466,  -466,    24,   166,    21,  -466,  -466,   616,   616,
      96,  -466,  -466,  -466,  -466,   182,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,  -466,   -31,
    -466,     4,    21,  -466,    64,  -466,    72,    75,    20,    32,
     405,   405,   616,  -466,   678,  -466,  -466,   616,   616,   494,
    -466,  -466,    32,    32,     1,   427,    22,  -466,   616,   616,
      30,   -16,   -16,    32,    44,    71,  -466,  -466,  -466,   163,
       1,    22,   380,    93,    57,  -466,   -11,    88,    21,  -466,
    -466,   229,   -32,  -466,  -466,   264,    94,   155,   427,  3128,
    3128,   287,   287,   107,   616,  2966,   104,   132,     1,   191,
    -466,   427,   427,  -466,  -466,   135,   161,  -466,   380,   427,
    3128,  2966,   518,  -466,    13,   230,   153,  -466,  -466,   380,
     616,   159,  -466,   427,   169,   616,  -466,  -466,  -466,  -466,
    -466,  -466,  -466,     1,   195,   -45,  3209,   200,   202,  3128,
     203,   210,    -2,  3128,  3128,   552,  3128,  3128,  3128,  3128,
      21,  -466,  2480,  -466,  -466,  -466,  -466,  -466,  -466,  -466,
    2480,   220,   222,  -466,   287,  -466,   427,   239,  3128,   261,
    2480,   267,   278,  -466,  -466,   462,   282,  -466,   290,   191,
     616,    22,  -466,  -466,  -466,   286,   380,   285,  -466,  2480,
     289,   380,  -466,   203,  -466,  -466,   325,    25,  -466,  -466,
    -466,   291,  -466,  -466,   427,  -466,   285,  -466,   229,   135,
     292,  -466,  -466,   427,   304,    22,  3128,  3047,    21,   616,
      89,   616,   616,    89,    21,   181,   616,   427,   616,    89,
      89,  -466,  -466,    89,    89,    89,  1943,   742,  3128,  3128,
    3128,  3128,   427,   427,   427,   427,  3128,  3128,  3128,  3128,
    3128,  3128,  3128,  3128,  -466,  -466,  3128,  3128,   616,  3128,
     625,  -466,  3128,  3128,  3128,  3128,  3128,  3128,  3128,   616,
    2966,  2966,  -466,   307,   616,  -466,  -466,  2966,  2480,  3128,
    -466,  2966,  -466,   616,   616,   313,   308,   315,   316,    22,
     321,   326,  -466,  -466,   352,  -466,   380,   347,  -466,   135,
    -466,   126,   338,    21,   330,   302,    21,  -466,   357,   343,
     345,  -466,  -466,   427,  -466,  2000,   616,  2057,  1310,  3275,
    -466,  -466,  1616,   354,   203,   306,  -466,  -466,   370,  -466,
    -466,   151,   361,   363,  2828,    21,  3128,  -466,  -466,  -466,
      52,  -466,  -466,  -466,  -466,  -466,  1066,   -24,  -466,   876,
     876,   323,   323,  -466,  -466,  -466,  -466,  3311,  3311,  3311,
    3311,  3368,  3368,  1219,  2877,  3408,  3408,  -466,   574,  -466,
    -466,  3368,  3368,  3454,  3454,   224,   224,   224,  -466,   365,
     128,   356,   263,   366,  2480,  -466,   371,   373,   427,  -466,
    -466,  -466,   282,  -466,   427,   616,   427,  -466,   367,  2966,
    -466,   376,  -466,  -466,  -466,  -466,  -466,   427,   356,  -466,
    -466,  3128,    38,   368,   402,  3128,  3128,   427,   427,  -466,
    2480,    21,  -466,    14,  -466,    89,   381,  -466,    52,    23,
    -466,   203,  -466,  -466,  2828,   427,   393,  3128,   453,  1706,
     167,   189,    21,   387,  1436,  3128,  3128,  3128,  3128,  3128,
    3128,    21,    19,   392,  2966,  -466,   427,   -18,   -18,   427,
    -466,   427,   427,   416,   399,  -466,  -466,  -466,   424,   404,
     400,   407,    97,  -466,   430,   191,    29,  3128,   427,    21,
    2828,  2480,  2480,  -466,  -466,   411,  1886,  2828,  2569,   419,
     149,   616,  -466,  -466,  -466,   616,   229,   477,  2114,   431,
    -466,    52,  -466,  -466,  -466,  -466,  2480,  2480,  2480,  2480,
    2480,  2480,  1796,   426,   616,  -466,  -466,  -466,  3128,  -466,
    -466,  -466,   425,   446,   447,  3128,  -466,   427,    22,  -466,
     434,  3128,   -18,  3128,  2171,   449,  1526,  -466,  -466,  -466,
    -466,  -466,  -466,   152,   435,   198,   436,  3128,  2650,  3128,
     428,  -466,    52,  2480,   -18,  3128,  3128,  2480,  -466,  -466,
     331,   -18,  2480,  -466,    33,   438,  3128,  -466,    21,   427,
    -466,   427,  2228,  -466,  -466,  2285,  -466,   441,  -466,  2480,
    2480,   445,   451,  -466,    21,  2342,   454,   442,  -466,  2739,
    -466,  -466,  2966,  2966,  2431,   452,  -466,   203,  -466,  -466,
     457,   463,    21,    21,  -466,  -466,  -466,   458,  2431,  -466,
      21,   460,  -466
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     8,     9,     0,    34,     5,     6,     1,     0,     0,
       0,    10,    13,    14,    15,     0,    29,    30,    31,    32,
      33,     7,    22,    23,    25,    24,    26,    27,    28,    16,
      20,    17,     0,     3,    34,    36,     0,     0,    68,    47,
       0,     0,     0,    37,     0,    35,    38,     0,     0,     0,
      12,    11,    47,    47,    68,     0,    75,    34,     0,     0,
     123,   131,   131,    47,    23,    39,    21,    19,    18,    53,
      68,    75,   151,   147,    69,    70,    72,   143,     4,    46,
      76,     0,     0,    49,   101,     0,   127,     0,     0,     0,
       0,   134,   134,     0,     0,   298,    34,     0,    68,   113,
      45,    23,     0,   156,   155,    58,   152,   153,     0,     0,
       0,   298,     0,   144,    34,    36,    51,    48,    34,     0,
       0,    34,   104,     0,   125,     0,   124,   230,   228,   229,
     231,   232,   233,    68,     0,     0,   249,   253,   254,     0,
       0,   235,   237,     0,     0,     0,     0,     0,     0,     0,
       4,   234,   133,   227,   248,   241,   242,   243,   244,   245,
     132,   140,   141,   121,   135,   122,     0,    41,     0,   234,
     302,     0,    58,   300,    54,     0,    58,    60,     0,   113,
       0,    75,   157,   158,    59,     0,     0,    58,    71,    74,
       0,   151,   149,     0,    77,    82,     0,     0,    79,    83,
      85,    86,    94,    84,     0,    50,    58,   102,     0,    58,
     106,   107,   128,     0,   129,     0,     0,     0,     4,     0,
     250,     0,     0,   257,     4,     0,     0,     0,     0,   214,
     215,   247,   246,   212,   211,   213,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   216,   217,     0,     0,     0,     0,
       0,   218,     0,     0,     0,     0,     0,     0,     0,     0,
     298,     0,   225,     0,     0,   136,   142,   298,   304,     0,
      40,    59,   299,     0,     0,     0,    34,     0,    34,    75,
       0,   114,   115,    44,     0,   154,    59,     0,    73,    58,
      87,    96,     0,     0,     0,    34,     4,    52,     0,     0,
       0,    34,   126,     0,   297,     0,     0,     0,     0,   251,
     255,   256,    34,     0,     0,   289,   292,   236,     0,   238,
     240,    22,     0,     0,    34,     4,     0,   258,   269,   164,
       0,   161,   175,   172,   173,   174,   165,     0,   264,   204,
     205,   195,   196,   197,   198,   199,   200,   189,   190,   187,
     188,   193,   194,   186,   185,   201,   202,   220,   203,   222,
     221,   191,   192,   206,   207,   208,   209,   210,   219,     0,
       0,   111,     0,     0,   303,   301,     0,     0,     0,    61,
      55,    56,    58,    43,     0,     0,     0,   148,     0,   298,
      99,    34,    81,    78,    80,    34,   103,     0,   111,   108,
     130,     0,     0,     0,     0,     0,     0,     0,     0,   272,
     284,     4,   278,     0,   282,   252,    22,   159,     0,   295,
     291,     0,   293,   239,    34,     0,    34,     0,     0,    34,
     234,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     4,     0,   223,     0,   226,     0,   118,   118,     0,
      42,     0,     0,    62,     0,   117,   116,   145,     0,     0,
      90,     0,     0,    95,   109,   113,   270,     0,     0,     4,
      34,   285,   286,   287,   288,     0,     5,    34,     0,     0,
       0,     0,   290,   176,   267,     0,     0,     0,     0,     0,
     262,     0,   268,   163,   259,   162,   167,   168,   169,   170,
     171,   166,    34,   266,     0,   265,   224,   112,     0,   137,
     119,   138,     0,    64,    65,     0,    57,     0,    97,    34,
      91,     0,   118,     0,     0,     0,     0,   281,   273,   279,
     280,   283,   160,   296,     0,     0,   179,     0,    34,     0,
       0,   260,     0,   120,   118,     0,     0,    63,   146,    98,
       0,   118,   110,   100,   271,     0,     0,   274,     4,     0,
     181,     0,     0,   183,   182,     0,   263,     0,   139,    66,
      67,     0,     0,    88,     4,     0,     0,     0,   180,    34,
     184,   261,   298,   298,     0,     0,   275,     0,   178,   177,
       0,     0,     4,     4,   294,    92,    93,     0,     0,   276,
       4,     0,   277
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -466,  -466,   -10,    -8,    -4,  -466,   519,  -466,  -466,   362,
      40,     8,   -51,    67,  -466,  -466,  -466,   158,  -466,   450,
    -466,  -162,  -269,  -277,   -15,  -466,   466,   -55,  -210,  -466,
     254,  -466,  -466,  -466,  -466,  -466,   164,  -466,  -466,  -466,
    -466,   260,   171,  -171,  -466,   177,  -438,  -466,   541,   -52,
     525,   496,  -103,  -466,   618,  -466,   398,    85,  -165,  -136,
    -309,  -319,  -466,  -466,  -466,  -466,  -466,   437,  -466,  -466,
     853,  -466,   138,  -466,  -466,  -465,   105,  -466,   115,  -466,
    -466,   279,  -466,  -466,  -108,   335,  -264
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,     4,     5,     6,    10,    11,    12,    13,    73,
     151,   339,    15,    45,    46,    16,    17,    58,    82,    83,
      98,   185,   176,   177,    56,    74,    75,    79,    80,   197,
     198,   199,   200,   471,   561,   201,   202,    18,    85,   209,
     210,   211,   457,   181,   291,   292,   519,    19,    61,   441,
      91,   163,   164,    20,   104,    77,   105,   106,   107,   520,
     340,   341,   342,   343,   497,   344,   345,   346,   153,   154,
     155,   347,   348,   156,   157,   421,   422,   423,   424,   158,
     325,   326,   491,   159,   171,   172,   173
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    21,    34,   190,   225,   314,    81,    87,   289,   389,
     282,   203,    14,   428,   287,   438,   100,   385,    97,   392,
     521,   295,   513,    54,     7,   297,   303,   -34,    50,    89,
      21,     1,   238,   239,   110,     1,   238,   239,   217,    71,
     117,   451,    14,    48,   308,   175,   218,   310,    30,    30,
     533,    47,   518,   442,    90,    99,   193,   300,   118,   161,
     162,   275,     1,   196,    -5,   -34,   452,    81,   114,   227,
     208,   568,   111,   224,     1,    52,     8,     9,    53,   487,
      60,    60,    63,   179,    65,   228,    49,    66,    67,    66,
      55,   400,   238,   239,   563,    30,    -4,    32,    84,    86,
     301,    35,   514,    57,   488,   194,     1,     2,   477,    55,
     -34,     2,    30,    78,   338,   493,   578,    -4,   215,    88,
     150,   116,   195,   583,   150,   505,   293,   478,    30,   602,
     501,   295,   470,    94,   167,   169,    35,   398,     2,    43,
     237,    30,    30,   610,    -4,   254,   255,   109,    30,    30,
       2,   169,   192,    35,    95,   258,   -35,   260,   261,    30,
     207,   537,   379,    30,   108,   214,    -2,   -34,   540,   383,
     112,   269,   270,   271,    43,    47,   178,   166,     8,     9,
     150,   113,     2,   123,    44,   232,    35,   304,   430,   305,
     385,    43,   174,   187,   -35,   180,    36,    37,    38,    39,
      40,    41,   203,   552,   206,   -34,    30,   -34,   318,   399,
      69,    70,   323,   324,   322,   285,  -266,    78,   454,    44,
     290,    93,   455,    42,    43,   184,    30,   238,   239,   574,
     464,    30,    22,   115,   393,   175,    44,   175,   434,   -35,
     435,  -266,   204,   124,    30,   125,    96,  -105,   309,  -105,
     -34,   186,   389,    30,   196,  -127,   123,  -127,   213,   319,
     208,   320,   321,   244,   245,   -23,   327,    30,   329,    44,
     599,    43,    24,    25,    26,    27,    28,   502,   216,   125,
     254,   255,    30,    30,    30,    30,   570,   221,   125,   222,
     258,   469,   260,   261,   224,   492,   405,   226,   367,   402,
     370,    21,   -23,   273,   532,   274,   269,   270,   271,   378,
     169,   169,     1,   195,   382,   150,    44,   169,   559,   -23,
     -23,   169,   277,   386,   387,   439,   238,   239,   301,    35,
     443,   279,   444,   161,   162,   119,    30,   323,   431,    36,
      37,    38,    39,    40,    41,   193,   120,   121,   161,   162,
     175,   458,   459,    30,   472,   280,   412,   122,  -267,  -267,
    -267,  -267,   244,   245,   581,   582,    42,    43,   281,   302,
      29,    31,   286,   288,   294,   296,   440,   298,   490,   254,
     255,   306,   311,    22,   101,   496,   256,   257,     2,   258,
     259,   260,   261,   313,    -5,   381,   -59,   264,   265,   266,
     267,   268,   388,   390,   391,   269,   270,   271,    22,    23,
     394,   485,    44,   486,   150,   102,   395,   396,   489,   397,
     444,   401,   403,    24,    25,    26,    27,    28,    30,   406,
      22,    23,   407,   408,    30,   290,    30,   429,   503,   169,
      21,   512,   433,   545,   436,   456,   437,    30,    24,    25,
      26,    27,    28,   453,   460,   468,   103,    30,    30,   479,
     461,   604,   462,    72,   -89,    22,   115,   480,   434,   536,
      24,    25,    26,    27,    28,    30,   495,   499,   175,   504,
     283,   284,    21,   150,   600,   601,   525,   526,    59,   527,
     529,   550,   528,   444,   169,   530,    30,    22,    23,    30,
     531,    30,    30,   538,    43,    24,    25,    26,    27,    28,
      72,   542,   547,   554,   549,   435,   555,   556,    30,   566,
     576,    22,    23,   560,   569,   571,   152,   160,   592,   584,
     597,   544,   170,   591,   593,    86,   546,    24,    25,    26,
      27,    28,   577,   603,   444,   605,   596,   189,   170,    44,
     609,   606,   612,    51,    86,    22,    23,   543,   586,   404,
     486,    24,    25,    26,    27,    28,   231,    30,   205,   473,
      68,   409,   466,   220,   594,   188,   223,   238,   239,   475,
     229,   230,    62,   233,   234,   235,   236,    92,   165,   299,
     515,   539,   607,   608,   486,    24,    25,    26,    27,    28,
     611,   191,   486,   541,   432,   278,   380,     0,     0,    30,
       0,    30,     0,   244,   245,     0,     0,     0,     0,    22,
      23,     0,     0,     0,     0,     0,     0,     0,    22,    23,
     254,   255,   169,   169,     0,     0,     0,   256,   257,   369,
     258,   259,   260,   261,     0,     0,     0,     0,   264,   265,
     266,   267,   268,   315,   317,     0,   269,   270,   271,    24,
      25,    26,    27,    28,     0,   150,     0,     0,    24,    25,
      26,    27,    28,    76,     0,   349,   350,   351,   352,     0,
       0,    22,    64,   357,   358,   359,   360,   361,   362,   363,
     364,     0,     0,   365,   366,     0,   368,     0,     0,   371,
     372,   373,   374,   375,   376,   377,   126,   170,   170,     0,
       0,     0,     0,     0,   170,     0,   384,     0,   170,   182,
     183,    24,    25,    26,    27,    28,     0,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   212,     0,     0,     0,   331,    23,   127,   128,   129,
     130,   131,     0,   132,     0,   420,   425,     0,   133,     0,
       0,     0,   134,     0,   135,   332,   333,   334,   136,   137,
     138,   139,   140,   236,     0,   141,   142,     0,     0,     0,
       0,     0,     0,     0,   276,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
       0,     0,     0,     0,     0,     0,     0,   335,     0,     0,
     145,     0,     0,     0,     0,     0,   146,   147,     0,     0,
       0,   148,   307,     0,     0,   336,     0,     0,     0,     0,
       0,   312,     0,   150,   337,     0,   170,   338,     0,     0,
       0,     0,     0,     0,     0,   328,     0,     0,   476,     0,
       0,     0,   481,   482,     0,     0,     0,     0,     0,     0,
     353,   354,   355,   356,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   498,     0,     0,     0,     0,   238,
     239,     0,   506,   507,   508,   509,   510,   511,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   534,   244,   245,     0,     0,     0,
       0,     0,     0,   420,     0,   420,     0,     0,     0,     0,
       0,   410,   254,   255,     0,     0,     0,     0,     0,   256,
     257,     0,   258,     0,   260,   261,     0,     0,     0,     0,
     264,   265,   266,   267,   268,   553,     0,     0,   269,   270,
     271,     0,   557,     0,     0,     0,     0,   150,   562,     0,
     564,     0,     0,   420,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   572,     0,   575,     0,     0,     0,
       0,     0,   579,   580,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   585,     0,   272,   463,     0,     0,     0,
       0,     0,   465,   272,   467,     0,     0,     0,     0,     0,
       0,     0,     0,   272,     0,   474,     0,     0,     0,   170,
     170,   420,     0,     0,     0,   483,   484,     0,     0,     0,
       0,     0,   272,     0,     0,   420,     0,     0,     0,     0,
       0,     0,     0,   494,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   238,
     239,     0,     0,   272,   517,     0,   272,   522,     0,   523,
     524,     0,   272,   272,     0,     0,   272,   272,   272,   272,
       0,     0,     0,     0,     0,     0,   535,     0,     0,     0,
       0,   240,   241,   242,   243,   244,   245,     0,     0,     0,
       0,     0,     0,     0,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   445,   446,   447,   448,   449,   256,
     257,   272,   258,   259,   260,   261,   450,   262,   263,     0,
     264,   265,   266,   267,   268,   558,     0,     0,   269,   270,
     271,     0,     0,     0,     0,     0,     0,   150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   272,     0,
     272,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   587,     0,   588,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   272,
       0,     0,   272,   272,   272,   272,     0,     0,     0,     0,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
       0,   272,   238,   239,   272,   272,   272,   272,   272,   272,
     272,     0,     0,     0,     0,     0,     0,   272,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   240,   241,   242,   243,   244,   245,
       0,     0,     0,     0,     0,     0,     0,   246,   247,   248,
     249,   250,   251,   272,     0,   254,   255,     0,   272,     0,
       0,     0,   256,   257,     0,   258,   259,   260,   261,     0,
     262,   263,     0,   264,   265,   266,   267,   268,     0,     0,
       0,   269,   270,   271,     0,     0,   516,     0,     0,     0,
     150,     0,     0,    22,    23,   127,   128,   129,   130,   131,
       0,   132,     0,     0,     0,     0,   133,     0,     0,   272,
     134,   414,   135,     0,   272,   272,   136,   137,   138,   139,
     140,     0,     0,   141,   142,   415,   416,   417,   418,     0,
       0,   272,     0,    24,    25,    26,    27,    28,     0,   272,
     272,   272,   272,   272,   272,     0,   143,   144,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   145,     0,
       0,     0,     0,     0,   146,   147,     0,   272,     0,   148,
       0,     0,     0,   149,     0,     0,     0,     0,     0,     0,
       0,   150,   419,     0,     0,     0,   272,     0,     0,     0,
     272,     0,     0,     0,     0,   272,     0,   272,     0,     0,
       0,     0,     0,     0,     0,   272,     0,     0,   272,     0,
       0,     0,   272,   272,     0,     0,     0,     0,   272,   426,
      23,   127,   128,   129,   130,   131,     1,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,     0,   135,   332,
     333,   334,   136,   137,   138,   139,   140,     0,     0,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   149,
       0,     0,     2,     0,     0,     0,     0,   150,    -5,    22,
      23,   127,   128,   129,   130,   131,     0,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,   414,   135,     0,
       0,     0,   136,   137,   138,   139,   140,     0,     0,   141,
     142,   415,   416,   417,   418,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,   150,   567,   426,
      23,   127,   128,   129,   130,   131,     0,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,     0,   135,   332,
     333,   334,   136,   137,   138,   139,   140,     0,     0,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,   150,   427,   426,
      23,   127,   128,   129,   130,   131,     0,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,     0,   135,   332,
     333,   334,   136,   137,   138,   139,   140,     0,     0,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,   150,   500,   426,
      23,   127,   128,   129,   130,   131,     0,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,     0,   135,   332,
     333,   334,   136,   137,   138,   139,   140,     0,     0,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,   150,   551,    22,
      23,   127,   128,   129,   130,   131,     1,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,   414,   135,     0,
       0,     0,   136,   137,   138,   139,   140,     0,     0,   141,
     142,   415,   416,   417,   418,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,   238,   239,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,     0,     0,     0,   148,     0,     0,     0,   149,
       0,     0,     2,     0,     0,     0,     0,   150,   240,   241,
     242,   243,   244,   245,     0,     0,     0,     0,     0,     0,
       0,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,     0,     0,   238,   239,     0,   256,   257,     0,   258,
     259,   260,   261,     0,   262,   263,     0,   264,   265,   266,
     267,   268,     0,     0,     0,   269,   270,   271,     0,     0,
       0,   330,     0,     0,   150,   240,   241,   242,   243,   244,
     245,     0,     0,     0,     0,     0,     0,     0,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,     0,     0,
     238,   239,     0,   256,   257,     0,   258,   259,   260,   261,
       0,   262,   263,     0,   264,   265,   266,   267,   268,     0,
       0,     0,   269,   270,   271,     0,     0,     0,   411,     0,
       0,   150,   240,   241,   242,   243,   244,   245,     0,     0,
       0,     0,     0,     0,     0,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,     0,     0,   238,   239,     0,
     256,   257,     0,   258,   259,   260,   261,     0,   262,   263,
       0,   264,   265,   266,   267,   268,     0,     0,     0,   269,
     270,   271,     0,     0,     0,   413,     0,     0,   150,   240,
     241,   242,   243,   244,   245,     0,     0,     0,     0,     0,
       0,     0,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,     0,     0,   238,   239,     0,   256,   257,     0,
     258,   259,   260,   261,     0,   262,   263,     0,   264,   265,
     266,   267,   268,     0,     0,     0,   269,   270,   271,     0,
       0,     0,   548,     0,     0,   150,   240,   241,   242,   243,
     244,   245,     0,     0,     0,     0,     0,     0,     0,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,     0,
       0,   238,   239,     0,   256,   257,     0,   258,   259,   260,
     261,     0,   262,   263,     0,   264,   265,   266,   267,   268,
       0,     0,     0,   269,   270,   271,     0,     0,     0,   565,
       0,     0,   150,   240,   241,   242,   243,   244,   245,     0,
       0,     0,     0,     0,     0,     0,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,     0,     0,   238,   239,
       0,   256,   257,     0,   258,   259,   260,   261,     0,   262,
     263,     0,   264,   265,   266,   267,   268,     0,     0,     0,
     269,   270,   271,     0,     0,     0,   589,     0,     0,   150,
     240,   241,   242,   243,   244,   245,     0,     0,     0,     0,
       0,     0,     0,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,     0,     0,   238,   239,     0,   256,   257,
       0,   258,   259,   260,   261,     0,   262,   263,     0,   264,
     265,   266,   267,   268,     0,     0,     0,   269,   270,   271,
       0,     0,     0,   590,     0,     0,   150,   240,   241,   242,
     243,   244,   245,     0,     0,     0,     0,     0,     0,     0,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
       0,     0,     0,     0,     0,   256,   257,     0,   258,   259,
     260,   261,     0,   262,   263,     0,   264,   265,   266,   267,
     268,     0,     0,     0,   269,   270,   271,     0,     0,     0,
     595,     0,     0,   150,    22,    23,   127,   128,   129,   130,
     131,     0,   132,     0,     0,     0,     0,   133,     0,     0,
       0,   134,   414,   135,     0,     0,     0,   136,   137,   138,
     139,   140,     0,     0,   141,   142,   415,   416,   417,   418,
       0,     0,     0,     0,    24,    25,    26,    27,    28,     0,
       0,     0,     0,   238,   239,     0,     0,   143,   144,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   145,
       0,     0,     0,     0,     0,   146,   147,     0,     0,     0,
     148,     0,     0,     0,   149,   240,   241,   242,   243,   244,
     245,     0,   150,     0,     0,     0,     0,     0,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,     0,     0,
       0,     0,     0,   256,   257,     0,   258,   259,   260,   261,
       0,   262,   263,     0,   264,   265,   266,   267,   268,     0,
       0,     0,   269,   270,   271,     0,     0,     0,     0,     0,
       0,   150,    22,    23,   127,   128,   129,   130,   131,     0,
     132,     0,     0,     0,     0,   133,     0,     0,     0,   134,
       0,   135,     0,     0,     0,   136,   137,   138,   139,   140,
       0,     0,   141,   142,   415,   416,   417,   418,     0,     0,
       0,     0,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   145,     0,     0,
       0,     0,     0,   146,   147,     0,     0,     0,   148,     0,
       0,     0,   149,   426,    23,   127,   128,   129,   130,   131,
     150,   132,     0,     0,     0,     0,   133,     0,     0,     0,
     134,     0,   135,   332,   333,   334,   136,   137,   138,   139,
     140,     0,     0,   141,   142,     0,     0,     0,     0,     0,
       0,     0,     0,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,   143,   144,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   145,     0,
       0,     0,     0,     0,   146,   147,     0,     0,     0,   148,
       0,     0,     0,   149,     0,     0,   573,     0,     0,     0,
       0,   150,   426,    23,   127,   128,   129,   130,   131,     0,
     132,     0,     0,     0,     0,   133,     0,     0,     0,   134,
       0,   135,   332,   333,   334,   136,   137,   138,   139,   140,
       0,     0,   141,   142,     0,     0,     0,     0,     0,     0,
       0,     0,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   145,     0,     0,
       0,     0,     0,   146,   147,     0,     0,     0,   148,     0,
       0,     0,   149,     0,     0,   598,     0,     0,     0,     0,
     150,   426,    23,   127,   128,   129,   130,   131,     0,   132,
       0,     0,     0,     0,   133,     0,     0,     0,   134,     0,
     135,   332,   333,   334,   136,   137,   138,   139,   140,     0,
       0,   141,   142,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    25,    26,    27,    28,     0,     0,     0,     0,
     238,   239,     0,     0,   143,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,     0,     0,     0,
       0,     0,   146,   147,     0,     0,     0,   148,     0,     0,
       0,   149,   240,   241,   242,   243,   244,   245,     0,   150,
       0,     0,     0,     0,     0,   246,   247,   248,   249,   250,
     251,   252,     0,   254,   255,     0,     0,     0,     0,     0,
     256,   257,     0,   258,   259,   260,   261,     0,   262,   263,
       0,   264,   265,   266,   267,   268,     0,     0,     0,   269,
     270,   271,     0,     0,     0,     0,     0,     0,   150,    22,
      23,   127,   128,   129,   130,   131,     0,   132,     0,     0,
       0,     0,   133,     0,     0,     0,   134,     0,   135,     0,
       0,     0,   136,   137,   138,   139,   140,     0,     0,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,     0,     0,
     146,   147,   168,     0,     0,   148,     0,     0,     0,   149,
      22,    23,   127,   128,   129,   130,   131,   150,   132,     0,
       0,     0,     0,   133,     0,   316,     0,   134,     0,   135,
       0,     0,     0,   136,   137,   138,   139,   140,     0,     0,
     141,   142,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   144,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,   146,   147,     0,     0,     0,   148,     0,     0,     0,
     149,    22,    23,   127,   128,   129,   130,   131,   150,   132,
       0,     0,     0,     0,   133,     0,     0,     0,   134,     0,
     135,     0,     0,     0,   136,   137,   138,   139,   140,     0,
       0,   141,   142,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,     0,     0,     0,
       0,     0,   146,   147,     0,     0,     0,   148,     0,     0,
       0,   149,    22,    23,   127,   128,   129,   130,   131,   150,
     132,     0,     0,     0,     0,   133,     0,     0,     0,   134,
       0,   135,     0,     0,     0,   136,   137,   138,   139,   140,
       0,     0,   141,   142,     0,     0,     0,     0,     0,     0,
       0,     0,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   145,    22,    23,
     127,   128,   129,   130,   131,     0,   132,     0,   148,     0,
       0,   133,   149,     0,     0,   134,   219,   135,     0,     0,
     150,   136,   137,   138,   139,   140,     0,     0,   141,   142,
       0,     0,     0,     0,   238,   239,     0,     0,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,   143,   144,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   145,     0,     0,   240,   241,   242,   243,
     244,   245,     0,     0,   148,     0,     0,     0,   149,     0,
       0,     0,     0,   250,   251,     0,   150,   254,   255,     0,
       0,   238,   239,     0,   256,   257,     0,   258,   259,   260,
     261,     0,   262,   263,     0,   264,   265,   266,   267,   268,
       0,     0,     0,   269,   270,   271,     0,     0,     0,     0,
       0,     0,   150,   240,   241,   242,   243,   244,   245,     0,
       0,   238,   239,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   254,   255,     0,     0,     0,     0,
       0,   256,   257,     0,   258,   259,   260,   261,     0,     0,
       0,     0,   264,   265,   266,   267,   268,   244,   245,     0,
     269,   270,   271,     0,     0,     0,     0,   238,   239,   150,
       0,     0,     0,     0,   254,   255,     0,     0,     0,     0,
       0,  -267,  -267,     0,   258,     0,   260,   261,     0,     0,
       0,     0,   264,   265,   266,   267,   268,     0,     0,     0,
     269,   270,   271,   244,   245,     0,     0,     0,     0,   150,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     254,   255,     0,     0,     0,     0,     0,     0,     0,     0,
     258,     0,   260,   261,     0,     0,     0,     0,     0,     0,
     266,   267,   268,     0,     0,     0,   269,   270,   271,     0,
       0,     0,     0,     0,     0,   150
};

static const yytype_int16 yycheck[] =
{
      10,     5,    10,   111,   140,   215,    57,    59,   179,   286,
     172,   114,     4,   322,   176,   334,    71,   281,    69,   288,
     458,   186,     3,     3,     0,   187,     1,     4,    32,    45,
      34,    10,     3,     4,    45,    10,     3,     4,    83,    54,
      72,    65,    34,    39,   206,    96,    91,   209,     8,     9,
      21,    82,    70,     1,    70,    70,    43,   193,    90,    46,
      47,   164,    10,   114,     0,    42,    90,   118,    78,    71,
     121,   536,    83,    91,    10,     3,    12,    13,     3,    65,
      40,    41,    42,    98,    44,    87,    82,    47,    48,    49,
      89,   301,     3,     4,   532,    55,     0,     1,    58,    59,
       3,     4,    83,    71,    90,    92,    10,    86,    70,    89,
      87,    86,    72,    91,    95,   434,   554,    92,   133,    89,
      91,    81,   114,   561,    91,   444,   181,    89,    88,   594,
     439,   296,   401,    89,    94,    95,     4,   299,    86,    42,
     150,   101,   102,   608,    92,    56,    57,    90,   108,   109,
      86,   111,   112,     4,    83,    66,     4,    68,    69,   119,
     120,   480,   270,   123,    71,   125,     0,     4,   487,   277,
      82,    82,    83,    84,    42,    82,    44,    70,    12,    13,
      91,    93,    86,    89,    87,   145,     4,   197,   324,   197,
     454,    42,    88,   108,    42,     4,    14,    15,    16,    17,
      18,    19,   305,   512,   119,    42,   166,    44,   218,    83,
      52,    53,    31,    32,   224,   175,    65,    91,    90,    87,
     180,    63,    94,    41,    42,    90,   186,     3,     4,   548,
     392,   191,     3,     4,   289,   286,    87,   288,    87,    87,
      89,    90,    89,    88,   204,    90,    83,    88,   208,    90,
      87,    90,   529,   213,   305,    88,    89,    90,    89,   219,
     311,   221,   222,    39,    40,    35,   226,   227,   228,    87,
     589,    42,    43,    44,    45,    46,    47,    88,    83,    90,
      56,    57,   242,   243,   244,   245,    88,    87,    90,    87,
      66,   399,    68,    69,    91,   431,   306,    87,   258,   303,
     260,   305,    72,    83,   475,    83,    82,    83,    84,   269,
     270,   271,    10,   305,   274,    91,    87,   277,   528,    89,
      90,   281,    83,   283,   284,   335,     3,     4,     3,     4,
     340,    70,   340,    46,    47,    71,   296,    31,    32,    14,
      15,    16,    17,    18,    19,    43,    82,    83,    46,    47,
     401,    88,    89,   313,   405,    88,   316,    93,    35,    36,
      37,    38,    39,    40,    33,    34,    41,    42,    90,    44,
       8,     9,    90,    83,    88,    90,   336,    88,   429,    56,
      57,    90,    90,     3,     4,   436,    63,    64,    86,    66,
      67,    68,    69,    89,    92,    88,    88,    74,    75,    76,
      77,    78,    89,    88,    88,    82,    83,    84,     3,     4,
      89,   421,    87,   421,    91,    35,    90,    65,   428,    72,
     428,    83,    92,    43,    44,    45,    46,    47,   388,    72,
       3,     4,    89,    88,   394,   395,   396,    83,   442,   399,
     444,   451,    72,   495,    83,    89,    83,   407,    43,    44,
      45,    46,    47,    88,    88,    88,    76,   417,   418,    91,
      89,   597,    89,    83,    88,     3,     4,    65,    87,   479,
      43,    44,    45,    46,    47,   435,    83,    24,   529,    92,
      18,    19,   486,    91,   592,   593,    70,    88,    83,    65,
      90,   501,    88,   501,   454,    88,   456,     3,     4,   459,
      70,   461,   462,    92,    42,    43,    44,    45,    46,    47,
      83,    92,    35,    88,    83,    89,    70,    70,   478,    70,
      92,     3,     4,    89,    89,    89,    89,    90,    83,    91,
      88,   491,    95,    92,    83,   495,   496,    43,    44,    45,
      46,    47,   552,    91,   552,    88,    92,   110,   111,    87,
      92,    88,    92,    34,   514,     3,     4,   490,   568,   305,
     568,    43,    44,    45,    46,    47,    14,   527,   118,   405,
      76,   311,   395,   136,   584,   109,   139,     3,     4,   408,
     143,   144,    41,   146,   147,   148,   149,    62,    92,   191,
     452,   486,   602,   603,   602,    43,    44,    45,    46,    47,
     610,    83,   610,   488,   325,   168,   271,    -1,    -1,   569,
      -1,   571,    -1,    39,    40,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      56,    57,   592,   593,    -1,    -1,    -1,    63,    64,    14,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    74,    75,
      76,    77,    78,   216,   217,    -1,    82,    83,    84,    43,
      44,    45,    46,    47,    -1,    91,    -1,    -1,    43,    44,
      45,    46,    47,    55,    -1,   238,   239,   240,   241,    -1,
      -1,     3,     4,   246,   247,   248,   249,   250,   251,   252,
     253,    -1,    -1,   256,   257,    -1,   259,    -1,    -1,   262,
     263,   264,   265,   266,   267,   268,    88,   270,   271,    -1,
      -1,    -1,    -1,    -1,   277,    -1,   279,    -1,   281,   101,
     102,    43,    44,    45,    46,    47,    -1,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   123,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    -1,   318,   319,    -1,    16,    -1,
      -1,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   336,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,
      -1,    79,   204,    -1,    -1,    83,    -1,    -1,    -1,    -1,
      -1,   213,    -1,    91,    92,    -1,   399,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,    -1,    -1,   411,    -1,
      -1,    -1,   415,   416,    -1,    -1,    -1,    -1,    -1,    -1,
     242,   243,   244,   245,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   437,    -1,    -1,    -1,    -1,     3,
       4,    -1,   445,   446,   447,   448,   449,   450,    -1,    -1,
      -1,   454,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   477,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,   486,    -1,   488,    -1,    -1,    -1,    -1,
      -1,   313,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    78,   518,    -1,    -1,    82,    83,
      84,    -1,   525,    -1,    -1,    -1,    -1,    91,   531,    -1,
     533,    -1,    -1,   536,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   547,    -1,   549,    -1,    -1,    -1,
      -1,    -1,   555,   556,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   566,    -1,   152,   388,    -1,    -1,    -1,
      -1,    -1,   394,   160,   396,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   170,    -1,   407,    -1,    -1,    -1,   592,
     593,   594,    -1,    -1,    -1,   417,   418,    -1,    -1,    -1,
      -1,    -1,   189,    -1,    -1,   608,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   435,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,   220,   456,    -1,   223,   459,    -1,   461,
     462,    -1,   229,   230,    -1,    -1,   233,   234,   235,   236,
      -1,    -1,    -1,    -1,    -1,    -1,   478,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,   278,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    77,    78,   527,    -1,    -1,    82,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   315,    -1,
     317,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   569,    -1,   571,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   346,
      -1,    -1,   349,   350,   351,   352,    -1,    -1,    -1,    -1,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
      -1,   368,     3,     4,   371,   372,   373,   374,   375,   376,
     377,    -1,    -1,    -1,    -1,    -1,    -1,   384,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,   420,    -1,    56,    57,    -1,   425,    -1,
      -1,    -1,    63,    64,    -1,    66,    67,    68,    69,    -1,
      71,    72,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    82,    83,    84,    -1,    -1,   453,    -1,    -1,    -1,
      91,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    -1,    -1,    -1,    -1,    16,    -1,    -1,   476,
      20,    21,    22,    -1,   481,   482,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    37,    38,    -1,
      -1,   498,    -1,    43,    44,    45,    46,    47,    -1,   506,
     507,   508,   509,   510,   511,    -1,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    74,    75,    -1,   534,    -1,    79,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    92,    -1,    -1,    -1,   553,    -1,    -1,    -1,
     557,    -1,    -1,    -1,    -1,   562,    -1,   564,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   572,    -1,    -1,   575,    -1,
      -1,    -1,   579,   580,    -1,    -1,    -1,    -1,   585,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,
      -1,    -1,    86,    -1,    -1,    -1,    -1,    91,    92,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    21,    22,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    21,    22,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,     3,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    83,
      -1,    -1,    86,    -1,    -1,    -1,    -1,    91,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    -1,     3,     4,    -1,    63,    64,    -1,    66,
      67,    68,    69,    -1,    71,    72,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    82,    83,    84,    -1,    -1,
      -1,    88,    -1,    -1,    91,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
       3,     4,    -1,    63,    64,    -1,    66,    67,    68,    69,
      -1,    71,    72,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    82,    83,    84,    -1,    -1,    -1,    88,    -1,
      -1,    91,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    -1,     3,     4,    -1,
      63,    64,    -1,    66,    67,    68,    69,    -1,    71,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    82,
      83,    84,    -1,    -1,    -1,    88,    -1,    -1,    91,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    -1,     3,     4,    -1,    63,    64,    -1,
      66,    67,    68,    69,    -1,    71,    72,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    82,    83,    84,    -1,
      -1,    -1,    88,    -1,    -1,    91,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      -1,     3,     4,    -1,    63,    64,    -1,    66,    67,    68,
      69,    -1,    71,    72,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    82,    83,    84,    -1,    -1,    -1,    88,
      -1,    -1,    91,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,     3,     4,
      -1,    63,    64,    -1,    66,    67,    68,    69,    -1,    71,
      72,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      82,    83,    84,    -1,    -1,    -1,    88,    -1,    -1,    91,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    -1,     3,     4,    -1,    63,    64,
      -1,    66,    67,    68,    69,    -1,    71,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    82,    83,    84,
      -1,    -1,    -1,    88,    -1,    -1,    91,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    63,    64,    -1,    66,    67,
      68,    69,    -1,    71,    72,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    82,    83,    84,    -1,    -1,    -1,
      88,    -1,    -1,    91,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    20,    21,    22,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,     3,     4,    -1,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    83,    35,    36,    37,    38,    39,
      40,    -1,    91,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    66,    67,    68,    69,
      -1,    71,    72,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    91,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,
      -1,    22,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    83,     3,     4,     5,     6,     7,     8,     9,
      91,    11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      20,    -1,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    83,    -1,    -1,    86,    -1,    -1,    -1,
      -1,    91,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    83,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      91,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
       3,     4,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    83,    35,    36,    37,    38,    39,    40,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      63,    64,    -1,    66,    67,    68,    69,    -1,    71,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    82,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    91,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    79,    -1,    -1,    -1,    83,
       3,     4,     5,     6,     7,     8,     9,    91,    11,    -1,
      -1,    -1,    -1,    16,    -1,    18,    -1,    20,    -1,    22,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      83,     3,     4,     5,     6,     7,     8,     9,    91,    11,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,    -1,
      22,    -1,    -1,    -1,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    83,     3,     4,     5,     6,     7,     8,     9,    91,
      11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,
      -1,    22,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    -1,    79,    -1,
      -1,    16,    83,    -1,    -1,    20,    87,    22,    -1,    -1,
      91,    26,    27,    28,    29,    30,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    79,    -1,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    52,    53,    -1,    91,    56,    57,    -1,
      -1,     3,     4,    -1,    63,    64,    -1,    66,    67,    68,
      69,    -1,    71,    72,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    35,    36,    37,    38,    39,    40,    -1,
      -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    39,    40,    -1,
      82,    83,    84,    -1,    -1,    -1,    -1,     3,     4,    91,
      -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    64,    -1,    66,    -1,    68,    69,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      82,    83,    84,    39,    40,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    -1,    -1,    -1,    82,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    91
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    86,    97,    98,    99,   100,     0,    12,    13,
     101,   102,   103,   104,   107,   108,   111,   112,   133,   143,
     149,   100,     3,     4,    43,    44,    45,    46,    47,   105,
     106,   105,     1,    98,    99,     4,    14,    15,    16,    17,
      18,    19,    41,    42,    87,   109,   110,    82,    39,    82,
     100,   102,     3,     3,     3,    89,   120,    71,   113,    83,
     106,   144,   144,   106,     4,   106,   106,   106,    76,   113,
     113,   120,    83,   105,   121,   122,   150,   151,    91,   123,
     124,   108,   114,   115,   106,   134,   106,   145,    89,    45,
      70,   146,   146,   113,    89,    83,    83,   108,   116,   120,
     123,     4,    35,    76,   150,   152,   153,   154,    71,    90,
      45,    83,    82,    93,    98,     4,   106,    72,    90,    71,
      82,    83,    93,    89,    88,    90,   150,     5,     6,     7,
       8,     9,    11,    16,    20,    22,    26,    27,    28,    29,
      30,    33,    34,    56,    57,    68,    74,    75,    79,    83,
      91,   106,   163,   164,   165,   166,   169,   170,   175,   179,
     163,    46,    47,   147,   148,   147,    70,   106,    76,   106,
     163,   180,   181,   182,    88,   108,   118,   119,    44,   120,
       4,   139,   150,   150,    90,   117,    90,   153,   122,   163,
     180,    83,   106,    43,    92,   107,   108,   125,   126,   127,
     128,   131,   132,   148,    89,   115,   153,   106,   108,   135,
     136,   137,   150,    89,   106,   120,    83,    83,    91,    87,
     163,    87,    87,   163,    91,   155,    87,    71,    87,   163,
     163,    14,   106,   163,   163,   163,   163,    98,     3,     4,
      35,    36,    37,    38,    39,    40,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    63,    64,    66,    67,
      68,    69,    71,    72,    74,    75,    76,    77,    78,    82,
      83,    84,   166,    83,    83,   148,   150,    83,   163,    70,
      88,    90,   117,    18,    19,   106,    90,   117,    83,   139,
     106,   140,   141,   123,    88,   154,    90,   117,    88,   152,
     155,     3,    44,     1,    98,    99,    90,   150,   117,   106,
     117,    90,   150,    89,   124,   163,    18,   163,    98,   106,
     106,   106,    98,    31,    32,   176,   177,   106,   150,   106,
      88,     3,    23,    24,    25,    65,    83,    92,    95,   107,
     156,   157,   158,   159,   161,   162,   163,   167,   168,   163,
     163,   163,   163,   150,   150,   150,   150,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   106,   163,    14,
     106,   163,   163,   163,   163,   163,   163,   163,   106,   180,
     181,    88,   106,   180,   163,   182,   106,   106,    89,   119,
      88,    88,   118,   123,    89,    90,    65,    72,   117,    83,
     124,    83,   100,    92,   126,    98,    72,    89,    88,   137,
     150,    88,   106,    88,    21,    35,    36,    37,    38,    92,
     163,   171,   172,   173,   174,   163,     3,    92,   156,    83,
     155,    32,   177,    72,    87,    89,    83,    83,   157,    98,
     106,   145,     1,    98,    99,    58,    59,    60,    61,    62,
      70,    65,    90,    88,    90,    94,    89,   138,    88,    89,
      88,    89,    89,   150,   117,   150,   141,   150,    88,   180,
     118,   129,   108,   132,   150,   138,   163,    70,    89,    91,
      65,   163,   163,   150,   150,    98,    99,    65,    90,    98,
     108,   178,   155,   157,   150,    83,   108,   160,   163,    24,
      92,   156,    88,   100,    92,   157,   163,   163,   163,   163,
     163,   163,    98,     3,    83,   168,   166,   150,    70,   142,
     155,   142,   150,   150,   150,    70,    88,    65,    88,    90,
      88,    70,   139,    21,   163,   150,    98,   157,    92,   172,
     157,   174,    92,   109,   106,   145,   106,    35,    88,    83,
      98,    92,   156,   163,    88,    70,    70,   163,   150,   124,
      89,   130,   163,   142,   163,    88,    70,    92,   171,    89,
      88,    89,   163,    86,   157,   163,    92,    98,   142,   163,
     163,    33,    34,   142,    91,   163,    98,   150,   150,    88,
      88,    92,    83,    83,    98,    88,    92,    88,    86,   157,
     180,   180,   171,    91,   155,    88,    88,    98,    98,    92,
     171,    98,    92
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   102,   102,   103,   104,   104,   104,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   109,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   116,   116,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   119,   119,   119,   119,   120,   120,
     121,   121,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   125,   126,   126,   126,   126,   126,   127,   128,   129,
     129,   130,   130,   130,   131,   131,   132,   132,   132,   132,
     133,   134,   134,   134,   134,   135,   135,   136,   136,   137,
     137,   138,   138,   139,   139,   140,   140,   141,   142,   142,
     142,   143,   143,   144,   144,   144,   144,   145,   145,   145,
     145,   146,   146,   146,   147,   147,   147,   148,   148,   148,
     148,   148,   149,   150,   150,   150,   150,   151,   151,   151,
     151,   152,   152,   153,   153,   154,   154,   154,   154,   155,
     155,   156,   156,   156,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   158,   159,   159,   160,
     160,   160,   161,   161,   162,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   166,   166,
     166,   166,   166,   166,   167,   167,   168,   168,   168,   168,
     169,   169,   170,   170,   170,   170,   170,   170,   171,   171,
     172,   172,   173,   173,   174,   174,   174,   174,   174,   175,
     175,   175,   176,   176,   177,   178,   178,   179,   180,   180,
     181,   181,   182,   182,   182
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     0,     1,     1,     2,     1,     1,
       1,     3,     3,     1,     1,     1,     2,     2,     4,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     1,     1,     1,     2,
       5,     4,     7,     8,     7,     5,     4,     0,     3,     1,
       3,     2,     4,     0,     2,     4,     4,     6,     0,     1,
       1,     3,     4,     6,     5,     5,     7,     7,     0,     2,
       1,     3,     1,     4,     3,     0,     1,     3,     5,     1,
       3,     3,     1,     1,     1,     1,     1,     2,     7,     0,
       1,     0,     5,     5,     1,     4,     2,     5,     6,     3,
      11,     1,     3,     5,     2,     0,     1,     1,     3,     4,
       6,     0,     2,     0,     2,     1,     3,     3,     0,     1,
       2,     5,     5,     1,     3,     3,     5,     1,     3,     3,
       5,     0,     2,     2,     0,     1,     2,     5,     5,     7,
       1,     1,     6,     1,     2,     6,     8,     1,     5,     3,
       7,     0,     1,     1,     3,     1,     1,     2,     2,     3,
       5,     1,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     3,     7,     7,     2,
       4,     3,     5,     5,     6,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     4,     5,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     4,
       3,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     3,     4,     1,     1,     3,     3,     2,     3,     5,
       6,     8,     5,     7,     1,     3,     1,     3,     3,     1,
       5,     7,     4,     6,     7,     9,    12,    14,     1,     3,
       3,     3,     1,     3,     1,     2,     2,     2,     2,     3,
       5,     4,     1,     2,     8,     0,     2,     3,     0,     2,
       1,     3,     1,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 12: /* topItems: topItems error sep  */
#line 153 "../src/parser.y"
        { yyerrok;   /* error already counted by yyerror; this is just recovery */
          fprintf(stderr, "         (recovered at top level around line %d)\n", line_num); }
#line 2335 "parser.tab.c"
    break;

  case 16: /* packageDecl: PACKAGE qualifiedName  */
#line 169 "../src/parser.y"
        { printf("[Line %d] Package: %s\n", line_num, (yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2341 "parser.tab.c"
    break;

  case 17: /* importDecl: IMPORT qualifiedName  */
#line 174 "../src/parser.y"
        { printf("[Line %d] Import:  %s\n", line_num, (yyvsp[0].str)); free((yyvsp[0].str)); }
#line 2347 "parser.tab.c"
    break;

  case 18: /* importDecl: IMPORT qualifiedName '.' '*'  */
#line 176 "../src/parser.y"
        { printf("[Line %d] Import:  %s.*\n", line_num, (yyvsp[-2].str)); free((yyvsp[-2].str)); }
#line 2353 "parser.tab.c"
    break;

  case 19: /* importDecl: IMPORT qualifiedName AS identifier  */
#line 178 "../src/parser.y"
        { printf("[Line %d] Import:  %s as %s\n", line_num, (yyvsp[-2].str), (yyvsp[0].str)); free((yyvsp[-2].str)); free((yyvsp[0].str)); }
#line 2359 "parser.tab.c"
    break;

  case 20: /* qualifiedName: identifier  */
#line 182 "../src/parser.y"
                                       { (yyval.str) = (yyvsp[0].str); }
#line 2365 "parser.tab.c"
    break;

  case 21: /* qualifiedName: qualifiedName '.' identifier  */
#line 184 "../src/parser.y"
        { char *r = malloc(strlen((yyvsp[-2].str))+strlen((yyvsp[0].str))+2);
          sprintf(r, "%s.%s", (yyvsp[-2].str), (yyvsp[0].str));
          free((yyvsp[-2].str)); free((yyvsp[0].str)); (yyval.str) = r; }
#line 2373 "parser.tab.c"
    break;

  case 22: /* identifier: IDENTIFIER  */
#line 196 "../src/parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 2379 "parser.tab.c"
    break;

  case 23: /* identifier: SOFT_KW  */
#line 197 "../src/parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 2385 "parser.tab.c"
    break;

  case 24: /* identifier: CONSTRUCTOR  */
#line 198 "../src/parser.y"
                     { (yyval.str) = strdup("constructor"); }
#line 2391 "parser.tab.c"
    break;

  case 25: /* identifier: INIT  */
#line 199 "../src/parser.y"
                     { (yyval.str) = strdup("init"); }
#line 2397 "parser.tab.c"
    break;

  case 26: /* identifier: BY  */
#line 200 "../src/parser.y"
                     { (yyval.str) = strdup("by"); }
#line 2403 "parser.tab.c"
    break;

  case 27: /* identifier: GET  */
#line 201 "../src/parser.y"
                     { (yyval.str) = strdup("get"); }
#line 2409 "parser.tab.c"
    break;

  case 28: /* identifier: SET  */
#line 202 "../src/parser.y"
                     { (yyval.str) = strdup("set"); }
#line 2415 "parser.tab.c"
    break;

  case 43: /* classDecl: modifiers CLASS IDENTIFIER opt_typeParams opt_primCtor opt_supertypes opt_whereClause opt_classBody  */
#line 237 "../src/parser.y"
        { printf("[Line %d] Class:     %s\n", line_num, (yyvsp[-5].str)); add_decl("class", (yyvsp[-5].str), line_num); free((yyvsp[-5].str)); }
#line 2421 "parser.tab.c"
    break;

  case 44: /* classDecl: modifiers INTERFACE IDENTIFIER opt_typeParams opt_supertypes opt_whereClause opt_classBody  */
#line 239 "../src/parser.y"
        { printf("[Line %d] Interface: %s\n", line_num, (yyvsp[-4].str)); add_decl("interface", (yyvsp[-4].str), line_num); free((yyvsp[-4].str)); }
#line 2427 "parser.tab.c"
    break;

  case 45: /* objectDecl: modifiers OBJECT IDENTIFIER opt_supertypes opt_classBody  */
#line 244 "../src/parser.y"
        { printf("[Line %d] Object:    %s\n", line_num, (yyvsp[-2].str)); add_decl("object", (yyvsp[-2].str), line_num); free((yyvsp[-2].str)); }
#line 2433 "parser.tab.c"
    break;

  case 46: /* objectDecl: modifiers OBJECT opt_supertypes opt_classBody  */
#line 246 "../src/parser.y"
        { printf("[Line %d] Object:    <anonymous>\n", line_num); add_decl("object", "<anon>", line_num); }
#line 2439 "parser.tab.c"
    break;

  case 51: /* typeParam: modifiers identifier  */
#line 260 "../src/parser.y"
                                      { free((yyvsp[0].str)); }
#line 2445 "parser.tab.c"
    break;

  case 52: /* typeParam: modifiers identifier ':' type  */
#line 261 "../src/parser.y"
                                      { free((yyvsp[-2].str)); }
#line 2451 "parser.tab.c"
    break;

  case 62: /* ctorParam: modifiers identifier ':' type  */
#line 280 "../src/parser.y"
                                                       { free((yyvsp[-2].str)); }
#line 2457 "parser.tab.c"
    break;

  case 63: /* ctorParam: modifiers identifier ':' type '=' expr  */
#line 281 "../src/parser.y"
                                                       { free((yyvsp[-4].str)); }
#line 2463 "parser.tab.c"
    break;

  case 64: /* ctorParam: modifiers VAL identifier ':' type  */
#line 282 "../src/parser.y"
                                                       { free((yyvsp[-2].str)); }
#line 2469 "parser.tab.c"
    break;

  case 65: /* ctorParam: modifiers VAR identifier ':' type  */
#line 283 "../src/parser.y"
                                                       { free((yyvsp[-2].str)); }
#line 2475 "parser.tab.c"
    break;

  case 66: /* ctorParam: modifiers VAL identifier ':' type '=' expr  */
#line 284 "../src/parser.y"
                                                       { free((yyvsp[-4].str)); }
#line 2481 "parser.tab.c"
    break;

  case 67: /* ctorParam: modifiers VAR identifier ':' type '=' expr  */
#line 285 "../src/parser.y"
                                                       { free((yyvsp[-4].str)); }
#line 2487 "parser.tab.c"
    break;

  case 81: /* members: members error sep  */
#line 318 "../src/parser.y"
        { yyerrok;   /* error already counted by yyerror; this is just recovery */
          fprintf(stderr, "         (recovered in class body around line %d)\n", line_num); }
#line 2494 "parser.tab.c"
    break;

  case 96: /* enumEntry: modifiers IDENTIFIER  */
#line 360 "../src/parser.y"
                                                        { free((yyvsp[0].str)); }
#line 2500 "parser.tab.c"
    break;

  case 97: /* enumEntry: modifiers IDENTIFIER '(' opt_args ')'  */
#line 361 "../src/parser.y"
                                                        { free((yyvsp[-3].str)); }
#line 2506 "parser.tab.c"
    break;

  case 98: /* enumEntry: modifiers IDENTIFIER '(' opt_args ')' classBody  */
#line 362 "../src/parser.y"
                                                        { free((yyvsp[-4].str)); }
#line 2512 "parser.tab.c"
    break;

  case 99: /* enumEntry: modifiers IDENTIFIER classBody  */
#line 363 "../src/parser.y"
                                                        { free((yyvsp[-1].str)); }
#line 2518 "parser.tab.c"
    break;

  case 100: /* funDecl: modifiers FUN opt_typeParams funHead '(' opt_paramList opt_comma ')' opt_retType opt_whereClause opt_funBody  */
#line 368 "../src/parser.y"
        { printf("[Line %d] Function declared\n", line_num); add_decl("fun", "<fn>", line_num); }
#line 2524 "parser.tab.c"
    break;

  case 101: /* funHead: identifier  */
#line 376 "../src/parser.y"
                                                          { free((yyvsp[0].str)); }
#line 2530 "parser.tab.c"
    break;

  case 102: /* funHead: funHead '.' identifier  */
#line 377 "../src/parser.y"
                                                          { free((yyvsp[0].str)); }
#line 2536 "parser.tab.c"
    break;

  case 109: /* param: modifiers identifier ':' type  */
#line 393 "../src/parser.y"
                                                     { free((yyvsp[-2].str)); }
#line 2542 "parser.tab.c"
    break;

  case 110: /* param: modifiers identifier ':' type '=' expr  */
#line 394 "../src/parser.y"
                                                     { free((yyvsp[-4].str)); }
#line 2548 "parser.tab.c"
    break;

  case 117: /* typeConstraint: identifier ':' type  */
#line 413 "../src/parser.y"
                            { free((yyvsp[-2].str)); }
#line 2554 "parser.tab.c"
    break;

  case 121: /* propDecl: modifiers VAL declTarget opt_init opt_accessors  */
#line 424 "../src/parser.y"
        { printf("[Line %d] Val\n", line_num); add_decl("val", "<val>", line_num); }
#line 2560 "parser.tab.c"
    break;

  case 122: /* propDecl: modifiers VAR declTarget opt_init opt_accessors  */
#line 426 "../src/parser.y"
        { printf("[Line %d] Var\n", line_num); add_decl("var", "<var>", line_num); }
#line 2566 "parser.tab.c"
    break;

  case 123: /* declTarget: identifier  */
#line 430 "../src/parser.y"
                                            { free((yyvsp[0].str)); }
#line 2572 "parser.tab.c"
    break;

  case 124: /* declTarget: identifier ':' type  */
#line 431 "../src/parser.y"
                                            { free((yyvsp[-2].str)); }
#line 2578 "parser.tab.c"
    break;

  case 127: /* destructList: identifier  */
#line 437 "../src/parser.y"
                                            { free((yyvsp[0].str)); }
#line 2584 "parser.tab.c"
    break;

  case 128: /* destructList: identifier ':' type  */
#line 438 "../src/parser.y"
                                            { free((yyvsp[-2].str)); }
#line 2590 "parser.tab.c"
    break;

  case 129: /* destructList: destructList ',' identifier  */
#line 439 "../src/parser.y"
                                            { free((yyvsp[0].str)); }
#line 2596 "parser.tab.c"
    break;

  case 130: /* destructList: destructList ',' identifier ':' type  */
#line 440 "../src/parser.y"
                                            { free((yyvsp[-2].str)); }
#line 2602 "parser.tab.c"
    break;

  case 138: /* accessor: SET '(' identifier ')' opt_funBody  */
#line 458 "../src/parser.y"
                                                        { free((yyvsp[-2].str)); }
#line 2608 "parser.tab.c"
    break;

  case 139: /* accessor: SET '(' identifier ':' type ')' opt_funBody  */
#line 459 "../src/parser.y"
                                                        { free((yyvsp[-4].str)); }
#line 2614 "parser.tab.c"
    break;

  case 142: /* typeAliasDecl: modifiers TYPEALIAS identifier opt_typeParams '=' type  */
#line 466 "../src/parser.y"
        { printf("[Line %d] Typealias: %s\n", line_num, (yyvsp[-3].str)); add_decl("typealias", (yyvsp[-3].str), line_num); free((yyvsp[-3].str)); }
#line 2620 "parser.tab.c"
    break;

  case 147: /* typeRef: qualifiedName  */
#line 487 "../src/parser.y"
                                             { free((yyvsp[0].str)); }
#line 2626 "parser.tab.c"
    break;

  case 148: /* typeRef: qualifiedName '<' typeArgList opt_comma '>'  */
#line 488 "../src/parser.y"
                                                    { free((yyvsp[-4].str)); }
#line 2632 "parser.tab.c"
    break;

  case 149: /* typeRef: typeRef '.' identifier  */
#line 489 "../src/parser.y"
                                             { free((yyvsp[0].str)); }
#line 2638 "parser.tab.c"
    break;

  case 150: /* typeRef: typeRef '.' identifier '<' typeArgList opt_comma '>'  */
#line 490 "../src/parser.y"
                                                            { free((yyvsp[-4].str)); }
#line 2644 "parser.tab.c"
    break;

  case 163: /* stmts: stmts error sep  */
#line 523 "../src/parser.y"
        { yyerrok;   /* error already counted by yyerror; this is just recovery */
          fprintf(stderr, "         (recovered in block around line %d)\n", line_num); }
#line 2651 "parser.tab.c"
    break;

  case 176: /* labelStmt: IDENTIFIER '@' stmt  */
#line 547 "../src/parser.y"
                                 { free((yyvsp[-2].str)); }
#line 2657 "parser.tab.c"
    break;

  case 179: /* forVar: modifiers identifier  */
#line 556 "../src/parser.y"
                                            { free((yyvsp[0].str)); }
#line 2663 "parser.tab.c"
    break;

  case 180: /* forVar: modifiers identifier ':' type  */
#line 557 "../src/parser.y"
                                            { free((yyvsp[-2].str)); }
#line 2669 "parser.tab.c"
    break;

  case 219: /* expr: expr '.' identifier  */
#line 609 "../src/parser.y"
                                                    { free((yyvsp[0].str)); }
#line 2675 "parser.tab.c"
    break;

  case 220: /* expr: expr SAFE_DOT identifier  */
#line 610 "../src/parser.y"
                                                    { free((yyvsp[0].str)); }
#line 2681 "parser.tab.c"
    break;

  case 221: /* expr: expr COLONCOLON identifier  */
#line 611 "../src/parser.y"
                                                    { free((yyvsp[0].str)); }
#line 2687 "parser.tab.c"
    break;

  case 228: /* primary: INT_LIT  */
#line 621 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2693 "parser.tab.c"
    break;

  case 229: /* primary: REAL_LIT  */
#line 622 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2699 "parser.tab.c"
    break;

  case 230: /* primary: STRING_LIT  */
#line 623 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2705 "parser.tab.c"
    break;

  case 231: /* primary: CHAR_LIT  */
#line 624 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2711 "parser.tab.c"
    break;

  case 232: /* primary: BOOL_LIT  */
#line 625 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2717 "parser.tab.c"
    break;

  case 234: /* primary: identifier  */
#line 627 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2723 "parser.tab.c"
    break;

  case 236: /* primary: THIS '@' identifier  */
#line 629 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2729 "parser.tab.c"
    break;

  case 238: /* primary: SUPER '@' identifier  */
#line 631 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2735 "parser.tab.c"
    break;

  case 246: /* primary: COLONCOLON identifier  */
#line 639 "../src/parser.y"
                                                 { free((yyvsp[0].str)); }
#line 2741 "parser.tab.c"
    break;

  case 251: /* jumpExpr: RETURN '@' identifier  */
#line 648 "../src/parser.y"
                                                            { free((yyvsp[0].str)); }
#line 2747 "parser.tab.c"
    break;

  case 252: /* jumpExpr: RETURN '@' identifier expr  */
#line 649 "../src/parser.y"
                                                            { free((yyvsp[-1].str)); }
#line 2753 "parser.tab.c"
    break;

  case 255: /* jumpExpr: BREAK '@' identifier  */
#line 652 "../src/parser.y"
                                                            { free((yyvsp[0].str)); }
#line 2759 "parser.tab.c"
    break;

  case 256: /* jumpExpr: CONTINUE '@' identifier  */
#line 653 "../src/parser.y"
                                                            { free((yyvsp[0].str)); }
#line 2765 "parser.tab.c"
    break;

  case 266: /* lambdaParam: IDENTIFIER  */
#line 673 "../src/parser.y"
                                               { free((yyvsp[0].str)); }
#line 2771 "parser.tab.c"
    break;

  case 267: /* lambdaParam: IDENTIFIER ':' type  */
#line 674 "../src/parser.y"
                                               { free((yyvsp[-2].str)); }
#line 2777 "parser.tab.c"
    break;

  case 276: /* whenExpr: WHEN '(' VAL identifier '=' expr ')' '{' opt_seps whenEntries opt_seps '}'  */
#line 689 "../src/parser.y"
                                                                                              { free((yyvsp[-8].str)); }
#line 2783 "parser.tab.c"
    break;

  case 277: /* whenExpr: WHEN '(' VAL identifier ':' type '=' expr ')' '{' opt_seps whenEntries opt_seps '}'  */
#line 690 "../src/parser.y"
                                                                                              { free((yyvsp[-10].str)); }
#line 2789 "parser.tab.c"
    break;

  case 294: /* catchClause: CATCH '(' opt_modifiers identifier ':' type ')' block  */
#line 728 "../src/parser.y"
                                                              { free((yyvsp[-4].str)); }
#line 2795 "parser.tab.c"
    break;

  case 303: /* arg: identifier '=' expr  */
#line 752 "../src/parser.y"
                            { free((yyvsp[-2].str)); }
#line 2801 "parser.tab.c"
    break;


#line 2805 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 756 "../src/parser.y"


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
