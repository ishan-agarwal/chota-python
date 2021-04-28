/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "python.y"

#include<stdio.h> 
#include<stdlib.h> 
#include "y.tab.h"
#include<string.h>
#define MAXQUADS 250



FILE *fp_icg, *fp_quad;
char temp_var[100];
int m = 0;        //string length for temp_var
int unop =0;
int paramno=0;
char final_out[1024];

typedef struct Node
{
  struct Node *parent;
  struct Node *sibling;
  struct Node *child;
  char *token;
  int leaf;
}Node;

typedef struct tree
{
  Node *node;
}tree;

typedef struct Quad
{
  char *Res;
  char *A1;
  char *A2;
  char *Op;
  int I;
  
} Quad;

Quad* allQuads=NULL;
int qIndex = 0; // quadruple entry no
//allQuads = 


tree *tree_init();
Node* create_node(Node *parent, char *token, int leaf);
void push(Node* node);
void printTree(tree* T);
void print(Node* node);


tree *tree_init()
{
  tree *temp= (tree*)malloc(sizeof(tree));
  temp->node = NULL;
  return(temp);
}

void makeQuad(char *Op, char *A1, char *A2, char *Res)
  {
    
    allQuads[qIndex].Res = (char*)malloc(strlen(Res)+1);
    allQuads[qIndex].Op = (char*)malloc(strlen(Op)+1);
    allQuads[qIndex].A1 = (char*)malloc(strlen(A1)+1);
    allQuads[qIndex].A2 = (char*)malloc(strlen(A2)+1);
    
    strcpy(allQuads[qIndex].Res, Res);
    strcpy(allQuads[qIndex].A1, A1);
    strcpy(allQuads[qIndex].A2, A2);
    strcpy(allQuads[qIndex].Op, Op);
    allQuads[qIndex].I = qIndex;
 
    qIndex++;
    
    return;
  }


Node* create_node(Node *parent, char *token, int leaf) 
{
  Node *newnode = (Node*)malloc(sizeof(Node));
  newnode->token = (char*)malloc(strlen(token)*sizeof(char));
  strcpy(newnode->token, token);
  newnode->parent = parent;
  newnode->sibling = NULL;
  newnode->child = NULL;
  newnode->leaf=leaf;
  return(newnode);
}

void print(Node* node) 
{ 
    if(node == NULL) 
        return; 

    printf("%s ",node->token);
    print(node->child);  
    print(node->sibling); 
}

void printTree(tree* T)
{
  print(T->node);
  printf("\n");
}

void first_val(char *first, char *temp)
{
    int i=0;int n=strlen(first);
    while(i<n && first[i]!=',')
    {
      temp[i]=first[i];i++;
    }
}

void expand(char *str, char *temp)
{
  char *pt;int a=0,b=0,c=0,i=0; char buffer[1024]="";
  pt = strtok(str,",");
  if(pt==NULL)
  {
    if(strlen(str)==0)
    {
    strcat(temp,"");
    return;
    }
  }
  a=atoi(pt);
  pt = strtok(NULL,",");
  if(pt==NULL)
  {
    i=0;
    while(i<a-1)
    {
      sprintf(buffer,"%d",i);
      strcat(temp,buffer);strcat(temp,",");
      i++;
    }
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);
    return;
  }
  b=atoi(pt);
  pt = strtok (NULL,",");
  if(pt==NULL)
  {
    i=a;
    while(i<b-1)
    {
      sprintf(buffer,"%d",i);
      strcat(temp,buffer);strcat(temp,",");
      i++;
    }
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);
    return;
  }  
  c=atoi(pt);
  i=a;
  if(c>0)
  {
  while(i<b-c)
  {
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);strcat(temp,",");
    i+=c;
  }
  sprintf(buffer,"%d",i);
  strcat(temp,buffer);
  return;
  }
  else 
  {

    while(i>b-c)
    {
      sprintf(buffer,"%d",i);
      strcat(temp,buffer);strcat(temp,",");
      i+=c;
    }
    sprintf(buffer,"%d",i);
    strcat(temp,buffer);
    return; 
  }

}

void len(char *val,char *temp)
{
  int t=strlen(val);
  t=t-t/2;
  sprintf(temp,"%d",t);
}

tree *head = NULL;

void add_child(Node* parent, Node* child)
{
  if(parent==NULL)
    return;
  
  if(parent->child==NULL)
  {
    parent->child = child;
  }
  else
  {
    Node *n = parent->child;
    while(n->sibling!=NULL)
    {
      n=n->sibling;
    }
    n->sibling = child;
  }
  child->parent = parent;
}

void add_sibling(Node* left, Node* new)
{
  if(left==NULL)
  {
    left = new;
    return;
  }
  
  if(left->sibling==NULL)
  {
    left->sibling = new;
  }
  else
  {
    Node *n = left;
    while(n->sibling!=NULL)
    {
      n=n->sibling;
    }
    n->sibling = new;
  }
}

Node* end_node(Node* left)
{
  if(left==NULL)
    return NULL;
  
  if(left->sibling==NULL)
  {
    return left;
  }
  else
  {
    Node *n = left;
    while(n->sibling!=NULL)
    {
      n=n->sibling;
    }
    return n;
  }
}



int tempno = 0, ln = 0; //temp variable no, label no
int exprno = -1; //expr no


#line 339 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    DOT = 258,                     /* DOT  */
    LINE = 259,                    /* LINE  */
    FALSE = 260,                   /* FALSE  */
    NONE = 261,                    /* NONE  */
    TRUE = 262,                    /* TRUE  */
    LAND = 263,                    /* LAND  */
    BREAK = 264,                   /* BREAK  */
    CONTINUE = 265,                /* CONTINUE  */
    ELIF = 266,                    /* ELIF  */
    DEL = 267,                     /* DEL  */
    ELSE = 268,                    /* ELSE  */
    FOR = 269,                     /* FOR  */
    IF = 270,                      /* IF  */
    IN = 271,                      /* IN  */
    NOT = 272,                     /* NOT  */
    LOR = 273,                     /* LOR  */
    WHILE = 274,                   /* WHILE  */
    INPUT = 275,                   /* INPUT  */
    PRINT = 276,                   /* PRINT  */
    INT = 277,                     /* INT  */
    FLOAT = 278,                   /* FLOAT  */
    STR = 279,                     /* STR  */
    LIST = 280,                    /* LIST  */
    SPLIT = 281,                   /* SPLIT  */
    MAP = 282,                     /* MAP  */
    APPEND = 283,                  /* APPEND  */
    POP = 284,                     /* POP  */
    INSERT = 285,                  /* INSERT  */
    LEN = 286,                     /* LEN  */
    ID = 287,                      /* ID  */
    CINT = 288,                    /* CINT  */
    CFLOAT = 289,                  /* CFLOAT  */
    SEMI = 290,                    /* SEMI  */
    COMMA = 291,                   /* COMMA  */
    CSTR = 292,                    /* CSTR  */
    EPOP = 293,                    /* EPOP  */
    MUL = 294,                     /* MUL  */
    DIV = 295,                     /* DIV  */
    FDIV = 296,                    /* FDIV  */
    MOD = 297,                     /* MOD  */
    ADD = 298,                     /* ADD  */
    SUB = 299,                     /* SUB  */
    ASOP = 300,                    /* ASOP  */
    G = 301,                       /* G  */
    L = 302,                       /* L  */
    GE = 303,                      /* GE  */
    LE = 304,                      /* LE  */
    EOP = 305,                     /* EOP  */
    NEOP = 306,                    /* NEOP  */
    XOR = 307,                     /* XOR  */
    BAND = 308,                    /* BAND  */
    BOR = 309,                     /* BOR  */
    LBRACE = 310,                  /* LBRACE  */
    RBRACE = 311,                  /* RBRACE  */
    LPAREN = 312,                  /* LPAREN  */
    RPAREN = 313,                  /* RPAREN  */
    LBRACKET = 314,                /* LBRACKET  */
    RBRACKET = 315,                /* RBRACKET  */
    RANGE = 316,                   /* RANGE  */
    COLON = 317                    /* COLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define DOT 258
#define LINE 259
#define FALSE 260
#define NONE 261
#define TRUE 262
#define LAND 263
#define BREAK 264
#define CONTINUE 265
#define ELIF 266
#define DEL 267
#define ELSE 268
#define FOR 269
#define IF 270
#define IN 271
#define NOT 272
#define LOR 273
#define WHILE 274
#define INPUT 275
#define PRINT 276
#define INT 277
#define FLOAT 278
#define STR 279
#define LIST 280
#define SPLIT 281
#define MAP 282
#define APPEND 283
#define POP 284
#define INSERT 285
#define LEN 286
#define ID 287
#define CINT 288
#define CFLOAT 289
#define SEMI 290
#define COMMA 291
#define CSTR 292
#define EPOP 293
#define MUL 294
#define DIV 295
#define FDIV 296
#define MOD 297
#define ADD 298
#define SUB 299
#define ASOP 300
#define G 301
#define L 302
#define GE 303
#define LE 304
#define EOP 305
#define NEOP 306
#define XOR 307
#define BAND 308
#define BOR 309
#define LBRACE 310
#define RBRACE 311
#define LPAREN 312
#define RPAREN 313
#define LBRACKET 314
#define RBRACKET 315
#define RANGE 316
#define COLON 317

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 269 "python.y"
 struct{char value[1024]; int type;struct Node *node;char lhs[1024]  ;char code[1024];char begin[1024]; char end[1024];}ctype; char val[1024]; 

#line 518 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DOT = 3,                        /* DOT  */
  YYSYMBOL_LINE = 4,                       /* LINE  */
  YYSYMBOL_FALSE = 5,                      /* FALSE  */
  YYSYMBOL_NONE = 6,                       /* NONE  */
  YYSYMBOL_TRUE = 7,                       /* TRUE  */
  YYSYMBOL_LAND = 8,                       /* LAND  */
  YYSYMBOL_BREAK = 9,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_ELIF = 11,                      /* ELIF  */
  YYSYMBOL_DEL = 12,                       /* DEL  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_IN = 16,                        /* IN  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_LOR = 18,                       /* LOR  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_INPUT = 20,                     /* INPUT  */
  YYSYMBOL_PRINT = 21,                     /* PRINT  */
  YYSYMBOL_INT = 22,                       /* INT  */
  YYSYMBOL_FLOAT = 23,                     /* FLOAT  */
  YYSYMBOL_STR = 24,                       /* STR  */
  YYSYMBOL_LIST = 25,                      /* LIST  */
  YYSYMBOL_SPLIT = 26,                     /* SPLIT  */
  YYSYMBOL_MAP = 27,                       /* MAP  */
  YYSYMBOL_APPEND = 28,                    /* APPEND  */
  YYSYMBOL_POP = 29,                       /* POP  */
  YYSYMBOL_INSERT = 30,                    /* INSERT  */
  YYSYMBOL_LEN = 31,                       /* LEN  */
  YYSYMBOL_ID = 32,                        /* ID  */
  YYSYMBOL_CINT = 33,                      /* CINT  */
  YYSYMBOL_CFLOAT = 34,                    /* CFLOAT  */
  YYSYMBOL_SEMI = 35,                      /* SEMI  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_CSTR = 37,                      /* CSTR  */
  YYSYMBOL_EPOP = 38,                      /* EPOP  */
  YYSYMBOL_MUL = 39,                       /* MUL  */
  YYSYMBOL_DIV = 40,                       /* DIV  */
  YYSYMBOL_FDIV = 41,                      /* FDIV  */
  YYSYMBOL_MOD = 42,                       /* MOD  */
  YYSYMBOL_ADD = 43,                       /* ADD  */
  YYSYMBOL_SUB = 44,                       /* SUB  */
  YYSYMBOL_ASOP = 45,                      /* ASOP  */
  YYSYMBOL_G = 46,                         /* G  */
  YYSYMBOL_L = 47,                         /* L  */
  YYSYMBOL_GE = 48,                        /* GE  */
  YYSYMBOL_LE = 49,                        /* LE  */
  YYSYMBOL_EOP = 50,                       /* EOP  */
  YYSYMBOL_NEOP = 51,                      /* NEOP  */
  YYSYMBOL_XOR = 52,                       /* XOR  */
  YYSYMBOL_BAND = 53,                      /* BAND  */
  YYSYMBOL_BOR = 54,                       /* BOR  */
  YYSYMBOL_LBRACE = 55,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 56,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 57,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 58,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 59,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 60,                  /* RBRACKET  */
  YYSYMBOL_RANGE = 61,                     /* RANGE  */
  YYSYMBOL_COLON = 62,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_Start = 64,                     /* Start  */
  YYSYMBOL_Translation_unit = 65,          /* Translation_unit  */
  YYSYMBOL_Stmt = 66,                      /* Stmt  */
  YYSYMBOL_Assignment_stmt = 67,           /* Assignment_stmt  */
  YYSYMBOL_Simple_stmt = 68,               /* Simple_stmt  */
  YYSYMBOL_Compound_stmt = 69,             /* Compound_stmt  */
  YYSYMBOL_Jump_stmt = 70,                 /* Jump_stmt  */
  YYSYMBOL_Print_stmt = 71,                /* Print_stmt  */
  YYSYMBOL_Param_list = 72,                /* Param_list  */
  YYSYMBOL_If_stmt = 73,                   /* If_stmt  */
  YYSYMBOL_Elif_stmt = 74,                 /* Elif_stmt  */
  YYSYMBOL_Else_stmt = 75,                 /* Else_stmt  */
  YYSYMBOL_While_stmt = 76,                /* While_stmt  */
  YYSYMBOL_For_stmt = 77,                  /* For_stmt  */
  YYSYMBOL_Iterable = 78,                  /* Iterable  */
  YYSYMBOL_Expression_stmt = 79,           /* Expression_stmt  */
  YYSYMBOL_Exp = 80,                       /* Exp  */
  YYSYMBOL_Const = 81,                     /* Const  */
  YYSYMBOL_Primary_Exp = 82,               /* Primary_Exp  */
  YYSYMBOL_Unary_Exp = 83,                 /* Unary_Exp  */
  YYSYMBOL_Pow_Exp = 84,                   /* Pow_Exp  */
  YYSYMBOL_Mul_Exp = 85,                   /* Mul_Exp  */
  YYSYMBOL_Add_Exp = 86,                   /* Add_Exp  */
  YYSYMBOL_Bit_Exp = 87,                   /* Bit_Exp  */
  YYSYMBOL_Rel_Exp = 88,                   /* Rel_Exp  */
  YYSYMBOL_Eq_Exp = 89,                    /* Eq_Exp  */
  YYSYMBOL_In_Exp = 90,                    /* In_Exp  */
  YYSYMBOL_And_Exp = 91,                   /* And_Exp  */
  YYSYMBOL_Or_Exp = 92                     /* Or_Exp  */
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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  157

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   274,   274,   281,   291,   299,   307,   314,   324,   341,
     346,   352,   359,   365,   372,   378,   384,   389,   399,   414,
     428,   457,   478,   486,   513,   524,   561,   590,   598,   610,
     620,   630,   644,   657,   670,   683,   696,   708,   725,   743,
     751,   763,   769,   781,   791,   801,   812,   842,   875,   906,
     915,   922,   949,   957,   982,  1007,  1027,  1049,  1057,  1082,
    1107,  1115,  1141,  1165,  1191,  1199,  1215,  1233,  1249,  1266,
    1273,  1291,  1309,  1317,  1326,  1334,  1353,  1362
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
  "\"end of file\"", "error", "\"invalid token\"", "DOT", "LINE", "FALSE",
  "NONE", "TRUE", "LAND", "BREAK", "CONTINUE", "ELIF", "DEL", "ELSE",
  "FOR", "IF", "IN", "NOT", "LOR", "WHILE", "INPUT", "PRINT", "INT",
  "FLOAT", "STR", "LIST", "SPLIT", "MAP", "APPEND", "POP", "INSERT", "LEN",
  "ID", "CINT", "CFLOAT", "SEMI", "COMMA", "CSTR", "EPOP", "MUL", "DIV",
  "FDIV", "MOD", "ADD", "SUB", "ASOP", "G", "L", "GE", "LE", "EOP", "NEOP",
  "XOR", "BAND", "BOR", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "RANGE", "COLON", "$accept", "Start", "Translation_unit",
  "Stmt", "Assignment_stmt", "Simple_stmt", "Compound_stmt", "Jump_stmt",
  "Print_stmt", "Param_list", "If_stmt", "Elif_stmt", "Else_stmt",
  "While_stmt", "For_stmt", "Iterable", "Expression_stmt", "Exp", "Const",
  "Primary_Exp", "Unary_Exp", "Pow_Exp", "Mul_Exp", "Add_Exp", "Bit_Exp",
  "Rel_Exp", "Eq_Exp", "In_Exp", "And_Exp", "Or_Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
};
#endif

#define YYPACT_NINF (-55)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -55,   -55,   -55,   -55,   -55,   -25,    60,   108,    60,
     -36,   -24,    -3,     6,    19,    24,    50,   -55,   -55,   -55,
     108,   108,    60,    60,    41,    45,   -55,     3,    64,    67,
     -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,    73,    17,     5,    53,    22,   -12,   110,    98,
     -55,   104,   -55,    61,   -55,    65,    68,    60,    60,    60,
      60,   -29,    60,   -55,   -55,    71,   -31,   -55,    60,   -55,
     -55,   -55,   -55,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,   -29,    78,    79,   -55,   -30,    80,    85,    86,
      88,   -55,   -55,    60,   -55,   -17,   -55,    73,    73,    73,
      73,    17,    17,     5,     5,     5,    53,    53,    53,    53,
     -55,    22,    22,   -55,   -55,    74,     3,     3,   -55,   -55,
     -55,   -55,   -55,   -55,   -55,    82,    66,    91,     3,   137,
     -55,    93,    60,   138,   -55,    90,    92,   -55,    95,   100,
       3,     3,    97,   101,   137,   -55,   -55
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    35,    36,    34,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    31,    32,    33,
       0,     0,     0,     0,     0,     0,     2,     4,     0,     0,
       6,    11,    10,    12,    13,    14,    41,     9,    29,    39,
      49,    50,    52,    57,    60,    64,    69,    72,    74,    76,
      30,     0,    38,     0,    48,     0,     0,     0,     0,     0,
       0,     0,     0,    47,    46,     0,     0,    19,     0,     1,
       3,     7,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     8,    40,     0,    27,     0,    51,    53,    54,    55,
      56,    58,    59,    61,    62,    63,    65,    67,    66,    68,
      73,    70,    71,    75,    77,     0,     0,     0,    17,    43,
      44,    45,    42,    18,    28,     0,     0,     0,     0,    22,
      25,     0,     0,    24,    26,     0,     0,    20,     0,     0,
       0,     0,     0,     0,    22,    23,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -26,   -55,   -55,   -55,   -55,   -55,   -55,   -54,
     -55,     4,   -55,   -55,   -55,   -50,   -55,    -7,   -55,    23,
      83,    -2,     0,    28,     2,     1,   -55,    72,    70,    75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    66,
      33,   143,   147,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    70,    55,    96,    87,   103,   103,    51,     1,     2,
       3,   100,     4,     5,   105,    65,    67,     6,     7,   103,
       8,    56,     9,    10,    11,    12,    13,    14,   128,   104,
      23,    54,    24,    57,    15,    16,    17,    18,    88,    89,
      19,   134,   125,    63,    64,    69,    20,    21,    78,    79,
      67,    97,    98,    99,    58,   101,    74,    75,    76,    77,
      22,    67,    23,    59,    24,     1,     2,     3,    83,    84,
      85,    86,   107,   108,   109,   110,    60,     8,   111,   112,
      10,    61,    12,    13,    14,   116,   117,   118,   119,   121,
     122,    15,    52,    17,    18,    62,   133,    19,    68,    71,
     136,   137,    72,    20,    21,    80,    81,    82,   113,   114,
     115,    73,   141,     1,     2,     3,    91,    22,    90,    23,
      92,    24,   139,    93,   152,   153,    95,    94,    10,   102,
      12,    13,    14,   126,   127,   145,   135,   138,   129,    15,
      52,    17,    18,   130,   131,    19,   132,   140,   142,   144,
     150,   146,   148,   154,   149,   151,   106,   155,   156,   120,
     123,     0,     0,     0,     0,    22,   124,    23,     0,    24
};

static const yytype_int16 yycheck[] =
{
       7,    27,     9,    57,    16,    36,    36,    32,     5,     6,
       7,    61,     9,    10,    68,    22,    23,    14,    15,    36,
      17,    57,    19,    20,    21,    22,    23,    24,    58,    60,
      59,     8,    61,    57,    31,    32,    33,    34,    50,    51,
      37,    58,    92,    20,    21,     0,    43,    44,    43,    44,
      57,    58,    59,    60,    57,    62,    39,    40,    41,    42,
      57,    68,    59,    57,    61,     5,     6,     7,    46,    47,
      48,    49,    74,    75,    76,    77,    57,    17,    78,    79,
      20,    57,    22,    23,    24,    83,    84,    85,    86,    88,
      89,    31,    32,    33,    34,    45,   103,    37,    57,    35,
     126,   127,    35,    43,    44,    52,    53,    54,    80,    81,
      82,    38,   138,     5,     6,     7,    18,    57,     8,    59,
      16,    61,    56,    62,   150,   151,    58,    62,    20,    58,
      22,    23,    24,    55,    55,   142,    62,    55,    58,    31,
      32,    33,    34,    58,    58,    37,    58,    56,    11,    56,
      55,    13,    62,    56,    62,    55,    73,    56,   154,    87,
      90,    -1,    -1,    -1,    -1,    57,    91,    59,    -1,    61
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     6,     7,     9,    10,    14,    15,    17,    19,
      20,    21,    22,    23,    24,    31,    32,    33,    34,    37,
      43,    44,    57,    59,    61,    64,    65,    66,    67,    68,
      69,    70,    71,    73,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    32,    32,    80,    82,    80,    57,    57,    57,    57,
      57,    57,    45,    82,    82,    80,    72,    80,    57,     0,
      65,    35,    35,    38,    39,    40,    41,    42,    43,    44,
      52,    53,    54,    46,    47,    48,    49,    16,    50,    51,
       8,    18,    16,    62,    62,    58,    72,    80,    80,    80,
      78,    80,    58,    36,    60,    72,    83,    84,    84,    84,
      84,    85,    85,    86,    86,    86,    87,    87,    87,    87,
      90,    88,    88,    91,    92,    78,    55,    55,    58,    58,
      58,    58,    58,    80,    58,    62,    65,    65,    55,    56,
      56,    65,    11,    74,    56,    80,    13,    75,    62,    62,
      55,    55,    65,    65,    56,    56,    74
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    66,    67,    68,
      68,    68,    69,    69,    69,    70,    70,    71,    72,    72,
      73,    74,    74,    75,    75,    76,    77,    78,    78,    79,
      80,    81,    81,    81,    81,    81,    81,    81,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      84,    84,    85,    85,    85,    85,    85,    86,    86,    86,
      87,    87,    87,    87,    88,    88,    88,    88,    88,    89,
      89,    89,    90,    90,    91,    91,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     1,
       8,     7,     0,     5,     0,     6,     8,     3,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       3,     1,     4,     4,     4,     4,     2,     2,     2,     1,
       1,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 2: /* Start: Translation_unit  */
#line 275 "python.y"
{
  /*add_child(head->node,create_node(NULL,"Translation_unit",0));
  add_child(head->node->child,$1.node);*/
  printf("%s",(yyvsp[0].ctype).code);
}
#line 1697 "y.tab.c"
    break;

  case 3: /* Translation_unit: Stmt Translation_unit  */
#line 282 "python.y"
{
  /*$$.node = create_node(NULL,"Stmt",0);
  add_child(end_node($$.node),$1.node);
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$2.node);*/
  //printf("TU\n%s",$1.code);
  //printf("TU2\n%s",$2.code);
  sprintf((yyval.ctype).code,"%s\n%s",(yyvsp[-1].ctype).code,(yyvsp[0].ctype).code);
}
#line 1711 "y.tab.c"
    break;

  case 4: /* Translation_unit: Stmt  */
#line 292 "python.y"
{
  /*$$.node = create_node(NULL,"Stmt",0);
  add_child(end_node($$.node),$1.node);*/
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  //printf("%s",$1.code);
}
#line 1722 "y.tab.c"
    break;

  case 5: /* Stmt: Simple_stmt SEMI  */
#line 300 "python.y"
{
  /*$$.node=create_node(NULL,"Simple_stmt",0);
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,";",0));*/
  strcpy((yyval.ctype).code,(yyvsp[-1].ctype).code);
  //printf("simp%s",$1.code);
}
#line 1734 "y.tab.c"
    break;

  case 6: /* Stmt: Compound_stmt  */
#line 308 "python.y"
{
  /*$$.node=create_node(NULL,"Compound_stmt",0);
  add_child($$.node,$1.node);*/
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  //printf("cmp%s",$1.code);
}
#line 1745 "y.tab.c"
    break;

  case 7: /* Stmt: Assignment_stmt SEMI  */
#line 315 "python.y"
{
  /*$$.node=create_node(NULL,"Assignment_stmt",0);
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,";",0));*/
  //printf("assg%s",$1.code);
  strcpy((yyval.ctype).code,(yyvsp[-1].ctype).code);

}
#line 1758 "y.tab.c"
    break;

  case 8: /* Assignment_stmt: ID ASOP Exp  */
#line 325 "python.y"
{
  char buff[3]="";
  sprintf(buff,"%d",(yyvsp[0].ctype).type);
  insert("ID",(yyvsp[-2].ctype).value,buff,(yyvsp[0].ctype).value,-1);
  /*$$.node=create_node(NULL,"ID",0);
  add_child($$.node,create_node(NULL,$1.value,0));
  add_sibling($$.node,create_node(NULL,"=",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf((yyval.ctype).code,"%s\n=\t%s\t\t%s\n",(yyvsp[0].ctype).code,(yyvsp[0].ctype).lhs,(yyvsp[-2].ctype).value);

  


}
#line 1779 "y.tab.c"
    break;

  case 9: /* Simple_stmt: Expression_stmt  */
#line 342 "python.y"
{
  //$$.node=create_node(NULL,"Expression_stmt",0);add_child($$.node,$1.node);
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
}
#line 1788 "y.tab.c"
    break;

  case 10: /* Simple_stmt: Print_stmt  */
#line 347 "python.y"
{
  paramno=0;
  //$$.node=create_node(NULL,"Print_stmt",0);add_child($$.node,$1.node);
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
}
#line 1798 "y.tab.c"
    break;

  case 11: /* Simple_stmt: Jump_stmt  */
#line 353 "python.y"
{
  //$$.node=create_node(NULL,"Jump_stmt",0);add_child($$.node,$1.node);
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);

}
#line 1808 "y.tab.c"
    break;

  case 12: /* Compound_stmt: If_stmt  */
#line 360 "python.y"
{
  //$$.node=create_node(NULL,"If_stmt",0);add_child($$.node,$1.node);
  //printf("IF STATEMENT\n%s",$1.code);
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
}
#line 1818 "y.tab.c"
    break;

  case 13: /* Compound_stmt: While_stmt  */
#line 366 "python.y"
{
  
  //$$.node=create_node(NULL,"While_stmt",0);add_child($$.node,$1.node);
  //printf("WHILE STATEMENT%s",$1.code);
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
}
#line 1829 "y.tab.c"
    break;

  case 14: /* Compound_stmt: For_stmt  */
#line 373 "python.y"
{
  //$$.node=create_node(NULL,"For_stmt",0);add_child($$.node,$1.node);

}
#line 1838 "y.tab.c"
    break;

  case 15: /* Jump_stmt: BREAK  */
#line 379 "python.y"
{
  //$$.node=create_node(NULL,"BREAK",0);
  sprintf((yyval.ctype).code,"goto\t \t \tL%d",ln);

}
#line 1848 "y.tab.c"
    break;

  case 16: /* Jump_stmt: CONTINUE  */
#line 385 "python.y"
{
  //$$.node=create_node(NULL,"CONTINUE",0);
}
#line 1856 "y.tab.c"
    break;

  case 17: /* Print_stmt: PRINT LPAREN Param_list RPAREN  */
#line 390 "python.y"
{
  /*$$.node=create_node(NULL,"PRINT",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,$3.node);
  add_sibling($$.node,create_node(NULL,")",0));*/
  //printf("call\t \tprint\t%d\n",paramno);
  sprintf((yyval.ctype).code,"%s\ncall\t \tprint\t%d\n",(yyvsp[-1].ctype).code,paramno);
}
#line 1869 "y.tab.c"
    break;

  case 18: /* Param_list: Param_list COMMA Exp  */
#line 400 "python.y"
{
  (yyval.ctype).type=50+(yyvsp[0].ctype).type;strcat((yyval.ctype).value,",");
  strcat((yyval.ctype).value,(yyvsp[0].ctype).value);
  /*$$.node = create_node(NULL,"Param_list",0);
  add_child(end_node($$.node),$1.node);
  add_sibling($$.node,create_node(NULL,",",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf((yyval.ctype).lhs,(yyvsp[-2].ctype).lhs);
  //printf("param\t \t%s\n",$3.lhs);
  sprintf((yyval.ctype).code,"%s\n\t%s\nparam\t \t \t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[0].ctype).lhs);
  paramno++;
}
#line 1888 "y.tab.c"
    break;

  case 19: /* Param_list: Exp  */
#line 415 "python.y"
{  
  /*$$.node = create_node(NULL,"EXP",0);
  add_child(end_node($$.node),$1.node);*/
  //strcpy($$.code,$1.code);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].ctype).lhs);
  //printf("%s\nparam\t \t%s\n",$1.code,$1.lhs);
  sprintf((yyval.ctype).code,"%s\nparam\t \t \t%s\n",(yyvsp[0].ctype).code,(yyvsp[0].ctype).lhs);
  paramno++;



}
#line 1905 "y.tab.c"
    break;

  case 20: /* If_stmt: IF Exp COLON LBRACE Translation_unit RBRACE Elif_stmt Else_stmt  */
#line 429 "python.y"
{
  /*$$.node = create_node(NULL,"IF",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$5.node);
  add_sibling($$.node,create_node(NULL,"}",0));
  add_sibling($$.node,create_node(NULL,"Elif_stmt",0));
  add_child(end_node($$.node),$7.node);
  add_sibling($$.node,create_node(NULL,"Else_stmt",0));
  add_child(end_node($$.node),$8.node);*/

  
  //strcpy($$.code,$2.code);
  //////printf("code is:\n If False %s goto L%d\n",$$.code,ln++);
  //printf("IfFalse\t%s\t \tL%d\n",$$.code,ln);

  sprintf((yyval.ctype).begin,"L%d",ln++);
  sprintf((yyval.ctype).end,"L%d",ln++);
  strcpy((yyval.ctype).end,(yyvsp[0].ctype).end);
  sprintf((yyval.ctype).code,"Label\t \t \t%s\n%sIfFalse\t%s\tgoto\t%s\n%s\ngoto\t \t \t%s\n%s\n%s\n",(yyval.ctype).begin,(yyvsp[-6].ctype).code,(yyvsp[-6].ctype).lhs,(yyvsp[-1].ctype).begin,(yyvsp[-3].ctype).code,(yyvsp[0].ctype).end,(yyvsp[-1].ctype).code,(yyvsp[0].ctype).code);

  

}
#line 1937 "y.tab.c"
    break;

  case 21: /* Elif_stmt: ELIF Exp COLON LBRACE Translation_unit RBRACE Elif_stmt  */
#line 458 "python.y"
{
  /*$$.node = create_node(NULL,"ELIF",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$5.node);
  add_sibling($$.node,create_node(NULL,"}",0));
  add_sibling($$.node,create_node(NULL,"Elif_stmt",0));
  add_child(end_node($$.node),$7.node);*/
  int l=ln;
  ln++;
  ////printf("code is:\n L%d\n",l);
  //printf("Label\t \t \tL%d\n",l);
  sprintf((yyval.ctype).begin,"L%d",ln++);
  sprintf((yyval.ctype).end,"L%d",ln++);
  //sprintf($$.code,"elif code");
  sprintf((yyval.ctype).code,"Label\t \t \t%s\n%sIfFalse\t%s\tgoto\t%s\n%s\ngoto\t \t \t%s\n%s\n",(yyval.ctype).begin,(yyvsp[-5].ctype).code,(yyvsp[-5].ctype).lhs,(yyvsp[0].ctype).begin,(yyvsp[-2].ctype).code,final_out,(yyvsp[0].ctype).code);
}
#line 1962 "y.tab.c"
    break;

  case 22: /* Elif_stmt: %empty  */
#line 478 "python.y"
  {int l=ln;
  //ln++;
  sprintf((yyval.ctype).begin,"L%d",ln);
  sprintf((yyval.ctype).end,"L%d",ln);
  sprintf((yyval.ctype).code,"Label\t \t \t%s\n",(yyval.ctype).end);

  }
#line 1974 "y.tab.c"
    break;

  case 23: /* Else_stmt: ELSE COLON LBRACE Translation_unit RBRACE  */
#line 487 "python.y"
{
  /*$$.node = create_node(NULL,"ELSE",0);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$4.node);
  add_sibling($$.node,create_node(NULL,"}",0));*/

  //int l=ln;
  //ln++;
  ////printf("code is:\n L%d\n",l);
  //printf($$.code,"Label\t \t \tL%d\n",l);


  int l=ln;
  ln++;
  ////printf("code is:\n L%d\n",l);
  //printf("Label\t \t \tL%d\n",l);
  sprintf((yyval.ctype).begin,"L%d",ln++);
  sprintf((yyval.ctype).end,"L%d",ln++);
  strcpy(final_out,(yyval.ctype).end);
  //sprintf($$.code,"else code");
  //sprintf($$.code,"Label\t \t \t%s\n%s\ngoto\t \t \t%s\nLabel\t \t \t%s\n",$$.begin,$4.code,$$.end,$$.end);
  sprintf((yyval.ctype).code,"%s\ngoto\t \t \t%s\nLabel\t \t \t%s",(yyvsp[-1].ctype).code,(yyval.ctype).end,(yyval.ctype).end);

}
#line 2005 "y.tab.c"
    break;

  case 24: /* Else_stmt: %empty  */
#line 513 "python.y"
  {
  int l=ln;
  //ln++;
  sprintf((yyval.ctype).begin,"L%d",ln);
  sprintf((yyval.ctype).end,"L%d",ln);
  ////printf("code is:\n L%d\n",l);
  //sprintf($$.code,"Label\t \t \tL%d\n",l);
  //sprintf($$.code,"Label\t \t \t%s\n",$$.end);

  }
#line 2020 "y.tab.c"
    break;

  case 25: /* While_stmt: WHILE Exp COLON LBRACE Translation_unit RBRACE  */
#line 525 "python.y"
{
  /*$$.node = create_node(NULL,"WHILE",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$5.node);
  add_sibling($$.node,create_node(NULL,"}",0));*/

  ////printf("code is : \nL%d:\n", ln);
  //printf("Label\t \t \tL%d\n",ln); //quad format: op =label a1=null a2=null res=l<ln>
  //ln++;
  //strcpy($$.code,$2.code);
  ////printf("code is If False %s goto L%d\n",$$.code,ln);
  ////printf("code is : \nL%d:\n", ln);


  sprintf((yyval.ctype).begin,"L%d",ln++);
  sprintf((yyval.ctype).end,"L%d",ln++);

  sprintf((yyval.ctype).code,"Label\t \t \t%s\n %s \nIfFalse\t%s\tgoto\t%s\n%s\ngoto\t \t \t%s\nLabel\t \t \t%s \n",(yyval.ctype).begin,(yyvsp[-4].ctype).code,(yyvsp[-4].ctype).lhs,(yyval.ctype).end,(yyvsp[-1].ctype).code,(yyval.ctype).begin,(yyval.ctype).end);

  //printf("%s",$$.code);
  /*printf("code is : \nL%d:\n", ln);
  //printf("Quadruple is:\n \tLabel\t  \t L%d\n\n", ln); //quad format: op =label a1=null a2=null res=l<ln>
  //ln++;
  //strcpy($$.code,$2.code);
  //printf("code is If False %s goto L%d\n",$$.code,ln);
  //printf("code is : \nL%d:\n", ln);*/




}
#line 2060 "y.tab.c"
    break;

  case 26: /* For_stmt: FOR ID IN Iterable COLON LBRACE Translation_unit RBRACE  */
#line 562 "python.y"
{
  char temp[1024]="";
  first_val((yyvsp[-4].ctype).value,temp);
  char buff[3]="";
  sprintf(buff,"%d",(yyvsp[-4].ctype).type%10);
  insert("ID",(yyvsp[-6].ctype).value,buff,temp,-1);
  /*$$.node = create_node(NULL,"FOR",0);
  add_sibling($$.node,create_node(NULL,"ID",0));
  add_child(end_node($$.node),create_node(NULL,$2.value,0));
  add_sibling($$.node,create_node(NULL,"in",0));
  add_sibling($$.node,create_node(NULL,"Iterable",0));
  add_child(end_node($$.node),$4.node);
  add_sibling($$.node,create_node(NULL,":",0));
  add_sibling($$.node,create_node(NULL,"{",0));
  add_sibling($$.node,create_node(NULL,"Translation_unit",0));
  add_child(end_node($$.node),$7.node);
  add_sibling($$.node,create_node(NULL,"}",0));*/


  ////printf("code is : \nL%d:\n", ln);
  printf("Label\t \t \tL%d\n",ln);//quad format: op =label a1=null a2=null res=l<ln>
  ln++;

  strcpy((yyval.ctype).code,(yyvsp[-6].ctype).code);
  ////printf("code is If False %s goto L%d\n",$$.code,ln);
  ////printf("code is : \nL%d:\n", ln);
}
#line 2092 "y.tab.c"
    break;

  case 27: /* Iterable: LBRACKET Param_list RBRACKET  */
#line 591 "python.y"
{
  (yyval.ctype)=(yyvsp[-1].ctype);
  /*$$.node = create_node(NULL,"[",0);
  add_sibling($$.node,create_node(NULL,"Param_list",0));
  add_child(end_node($$.node),$2.node);
  add_sibling($$.node,create_node(NULL,"]",0));*/
}
#line 2104 "y.tab.c"
    break;

  case 28: /* Iterable: RANGE LPAREN Param_list RPAREN  */
#line 599 "python.y"
{
  (yyval.ctype).type=51;
  char temp[1024]="";
  expand((yyvsp[-1].ctype).value,temp);strcpy((yyval.ctype).value,temp);
  /*$$.node = create_node(NULL,"RANGE",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"Param_list",0));
  add_child(end_node($$.node),$3.node);
  add_sibling($$.node,create_node(NULL,")",0));*/
}
#line 2119 "y.tab.c"
    break;

  case 29: /* Expression_stmt: Exp  */
#line 611 "python.y"
{
 /* $$.node = create_node(NULL,"Exp",0);
  add_child($$.node,$1.node);*/
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);


}
#line 2132 "y.tab.c"
    break;

  case 30: /* Exp: Or_Exp  */
#line 621 "python.y"
{
  /*$$.node = create_node(NULL,"Or_Exp",0);
  add_child($$.node,$1.node);*/
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);

  
}
#line 2145 "y.tab.c"
    break;

  case 31: /* Const: CINT  */
#line 631 "python.y"
{
  (yyval.ctype).type=1;
  strcpy((yyval.ctype).value,(yyvsp[0].val));
  /*$$.node = create_node(NULL,"CINT",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //printf("in const cint %s\n",$1);
  //strcpy($$.lhs,$1);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].val));
  exprno=0;

  //tempno++;
}
#line 2163 "y.tab.c"
    break;

  case 32: /* Const: CFLOAT  */
#line 645 "python.y"
{
  (yyval.ctype).type=2;
  strcpy((yyval.ctype).value,(yyvsp[0].val));
  /*$$.node = create_node(NULL,"CFLOAT",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //strcpy($$.code,$1);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].val));
  exprno=0;

  //tempno++;
}
#line 2180 "y.tab.c"
    break;

  case 33: /* Const: CSTR  */
#line 658 "python.y"
{
  (yyval.ctype).type=3;
  strcpy((yyval.ctype).value,(yyvsp[0].val));
  /*$$.node = create_node(NULL,"CSTR",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //strcpy($$.code,$1);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].val));
  exprno=0;

  //tempno++;
}
#line 2197 "y.tab.c"
    break;

  case 34: /* Const: TRUE  */
#line 671 "python.y"
{
  (yyval.ctype).type=4;
  strcpy((yyval.ctype).value,(yyvsp[0].val));
  /*$$.node = create_node(NULL,"TRUE",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/
  //strcpy($$.code,$1);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].val));
  exprno=0;

  //tempno++;

}
#line 2214 "y.tab.c"
    break;

  case 35: /* Const: FALSE  */
#line 684 "python.y"
{
  (yyval.ctype).type=4;
  strcpy((yyval.ctype).value,(yyvsp[0].val));
  /*$$.node = create_node(NULL,"FALSE",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/

  //strcpy($$.code,$1);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].val));
  exprno=0;

  //tempno++;
}
#line 2231 "y.tab.c"
    break;

  case 36: /* Const: NONE  */
#line 697 "python.y"
{
  (yyval.ctype).type=5;
  strcpy((yyval.ctype).value,(yyvsp[0].val));
  /*$$.node = create_node(NULL,"NONE",0);
  add_child($$.node,create_node(NULL,$$.value,0));*/
  //strcpy($$.code,$1);
  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].val));
  exprno=0;

  //tempno++;
}
#line 2247 "y.tab.c"
    break;

  case 37: /* Const: INPUT LPAREN RPAREN  */
#line 709 "python.y"
{
  (yyval.ctype).type=3;
  strcpy((yyval.ctype).value,"");
  /*$$.node = create_node(NULL,"INPUT",0);
  add_child($$.node,create_node(NULL,$$.value,0));
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,")",0));*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  //sprintf($$.code,temp_var);
  printf("call\t%s\tinput\t0\n",temp_var);
  sprintf((yyval.ctype).lhs,"%s",temp_var);
}
#line 2267 "y.tab.c"
    break;

  case 38: /* Primary_Exp: ID  */
#line 726 "python.y"
{
 
  (yyval.ctype)=(yyvsp[0].ctype); 
  /*$$.node = create_node(NULL,"ID",0); 
  add_child($$.node,create_node(NULL,$1.value,0));*/

  //strcpy($$.code,$1.value);
  //printf("in id %s\n",$1.value);

  sprintf((yyval.ctype).lhs,"%s",(yyvsp[0].ctype).value);
  exprno=0;
  //tempno++;

 


}
#line 2289 "y.tab.c"
    break;

  case 39: /* Primary_Exp: Const  */
#line 744 "python.y"
{
  (yyval.ctype)=(yyvsp[0].ctype);  
  /*$$.node = create_node(NULL,"Const",0); 
  add_child($$.node,$1.node);*/

  
}
#line 2301 "y.tab.c"
    break;

  case 40: /* Primary_Exp: LPAREN Exp RPAREN  */
#line 752 "python.y"
{
  (yyval.ctype)=(yyvsp[-1].ctype);
  /*$$.node = create_node(NULL,"(",0);
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$2.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/

  strcpy((yyval.ctype).code,(yyvsp[-1].ctype).code);
  sprintf((yyval.ctype).lhs,"%s",temp_var);
  exprno=1;
}
#line 2317 "y.tab.c"
    break;

  case 41: /* Primary_Exp: Iterable  */
#line 764 "python.y"
{
  (yyval.ctype)=(yyvsp[0].ctype);
  /*$$.node = create_node(NULL,"Iterable",0);
  add_child($$.node,$1.node);*/
}
#line 2327 "y.tab.c"
    break;

  case 42: /* Primary_Exp: LEN LPAREN Iterable RPAREN  */
#line 770 "python.y"
{
  (yyval.ctype).type=1;
  char buffer[10]="";
  len((yyvsp[-1].ctype).value,buffer) ;
  strcpy((yyval.ctype).value,buffer);
  /*$$.node = create_node(NULL,"LEN",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"Iterable",0));
  add_child(end_node($$.node),$3.node);
  add_sibling($$.node,create_node(NULL,")",0));*/
}
#line 2343 "y.tab.c"
    break;

  case 43: /* Primary_Exp: INT LPAREN Exp RPAREN  */
#line 782 "python.y"
{
  (yyval.ctype).type=1;
  strcpy((yyval.ctype).value,(yyvsp[-1].ctype).value);
  /*$$.node = create_node(NULL,"INT",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$3.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/
}
#line 2357 "y.tab.c"
    break;

  case 44: /* Primary_Exp: FLOAT LPAREN Exp RPAREN  */
#line 792 "python.y"
{
  (yyval.ctype).type=2;
  strcpy((yyval.ctype).value,(yyvsp[-1].ctype).value);
  /*$$.node = create_node(NULL,"FLOAT",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$3.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/
}
#line 2371 "y.tab.c"
    break;

  case 45: /* Primary_Exp: STR LPAREN Exp RPAREN  */
#line 802 "python.y"
{
  (yyval.ctype).type=3;
  strcpy((yyval.ctype).value,(yyvsp[-1].ctype).value);
  /*$$.node = create_node(NULL,"STR",0);
  add_sibling($$.node,create_node(NULL,"(",0));
  add_sibling($$.node,create_node(NULL,"EXP",0));
  add_child(end_node($$.node),create_node(NULL,$3.node,0));
  add_sibling($$.node,create_node(NULL,")",0));*/
}
#line 2385 "y.tab.c"
    break;

  case 46: /* Unary_Exp: SUB Primary_Exp  */
#line 813 "python.y"
{
  (yyval.ctype).type=(yyvsp[0].ctype).type;
  char buffer[1024]="-";
  strcat(buffer,(yyvsp[0].ctype).value);
  strcpy((yyval.ctype).value,buffer);
  /*$$.node = create_node(NULL,"-",0); 
  add_sibling($$.node,create_node(NULL,"Primary_Exp",0));
  add_child(end_node($$.node),$2.node);*/

  tempno++;
  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  //printf($$.code,"hi %s = - %s ",$2.lhs,$2.lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("Uminus\t%s\t \t%s\n",(yyvsp[0].ctype).lhs,(yyval.ctype).lhs);
  sprintf((yyval.ctype).code,"Uminus\t%s\t \t%s\n",(yyvsp[0].ctype).lhs,(yyval.ctype).lhs);

  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
  //printf("hi %s",$2.lhs);
  //sprintf($$.lhs,"%s",$1);
  exprno=2;
  unop=1;
}
#line 2419 "y.tab.c"
    break;

  case 47: /* Unary_Exp: ADD Primary_Exp  */
#line 843 "python.y"
{
  //$$=$2;
  /*$$.node = create_node(NULL,"+",0); 
  //add_sibling($$.node,create_node(NULL,"Primary_Exp",0));
  //add_child(end_node($$.node),$2.node);*/

  //strcpy($$.code,$2.code);

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).lhs);
  //printf("hi %s",$2.lhs);
  //sprintf($$.lhs,"%s",$1);
  exprno=2;
  unop=0;
  //tempno++;

  tempno++;
  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s = %s ",(yyval.ctype).lhs,(yyvsp[0].ctype).lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("Uplus\t%s\t \t%s\n",(yyvsp[0].ctype).lhs,(yyval.ctype).lhs);

  
  exprno=2;

}
#line 2456 "y.tab.c"
    break;

  case 48: /* Unary_Exp: NOT Primary_Exp  */
#line 876 "python.y"
{
  (yyval.ctype).type=(yyvsp[0].ctype).type;
  char buffer[1024]="-";
  strcat(buffer,(yyvsp[0].ctype).value);
  strcpy((yyval.ctype).value,buffer);
  /*$$.node = create_node(NULL,"!",0); 
  add_sibling($$.node,create_node(NULL,"Primary_Exp",0));
  add_child(end_node($$.node),$$.node);*/
  

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s = not %s ",temp_var,(yyvsp[0].ctype).lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("not\t%s\t\t%s\n",(yyvsp[0].ctype).lhs,(yyval.ctype).lhs);


  strcpy((yyval.ctype).code,(yyvsp[0].ctype).lhs);
  //printf("hi %s",$2.lhs);
  //sprintf($$.lhs,"%s",$1);
  exprno=2;
  unop=2;

}
#line 2491 "y.tab.c"
    break;

  case 49: /* Unary_Exp: Primary_Exp  */
#line 907 "python.y"
{
  /*$$.node = create_node(NULL,"Primary_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 2503 "y.tab.c"
    break;

  case 50: /* Pow_Exp: Unary_Exp  */
#line 916 "python.y"
{
  /*$$.node = create_node(NULL,"Unary_Exp",0); 
  add_child($$.node,$1.node);*/
  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);

  }
#line 2514 "y.tab.c"
    break;

  case 51: /* Pow_Exp: Pow_Exp EPOP Unary_Exp  */
#line 923 "python.y"
{
  /*$$.node = create_node(NULL,"Pow_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"**",0));
  add_sibling($$.node,create_node(NULL,"Unary_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n**\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  
  //printf("**\t%s\t%s\t%s\n",$1.lhs,$3.lhs,temp_var);

  //fprintf(fp_quad,"** \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
#line 2544 "y.tab.c"
    break;

  case 52: /* Mul_Exp: Pow_Exp  */
#line 950 "python.y"
{
  /*$$.node = create_node(NULL,"Pow_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 2556 "y.tab.c"
    break;

  case 53: /* Mul_Exp: Mul_Exp MUL Pow_Exp  */
#line 958 "python.y"
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"*",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n*\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("*\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //fprintf(fp_quad,"* \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;

}
#line 2585 "y.tab.c"
    break;

  case 54: /* Mul_Exp: Mul_Exp DIV Pow_Exp  */
#line 983 "python.y"
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"/",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n/\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  printf("/\t%s\t%s\t%s\n",(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).code,temp_var);

  //fprintf(fp_quad,"/ \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
#line 2614 "y.tab.c"
    break;

  case 55: /* Mul_Exp: Mul_Exp FDIV Pow_Exp  */
#line 1008 "python.y"
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"//",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n//\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("//\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);
}
#line 2638 "y.tab.c"
    break;

  case 56: /* Mul_Exp: Mul_Exp MOD Pow_Exp  */
#line 1028 "python.y"
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"%",0));
  add_sibling($$.node,create_node(NULL,"Pow_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s = %s % %s",temp_var,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).code);


  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("%\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);
}
#line 2663 "y.tab.c"
    break;

  case 57: /* Add_Exp: Mul_Exp  */
#line 1050 "python.y"
{
  /*$$.node = create_node(NULL,"Mul_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 2675 "y.tab.c"
    break;

  case 58: /* Add_Exp: Add_Exp ADD Mul_Exp  */
#line 1058 "python.y"
{
  /*$$.node = create_node(NULL,"Add_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"+",0));
  add_sibling($$.node,create_node(NULL,"Mul_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy((yyval.ctype).lhs,temp_var);
  //sprintf($$.code,"hello%s = %s + %s",temp_var,$1.lhs,$3.lhs);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("+\t%s\t%s\t%s\n",$1.lhs,$3.lhs,temp_var);
  sprintf((yyval.ctype).code,"%s%s\n+\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //fprintf(fp_quad,"+ \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
#line 2704 "y.tab.c"
    break;

  case 59: /* Add_Exp: Add_Exp SUB Mul_Exp  */
#line 1083 "python.y"
{
  /*$$.node = create_node(NULL,"Add_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"-",0));
  add_sibling($$.node,create_node(NULL,"Mul_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n-\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  //printf("-\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //fprintf(fp_quad,"- \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
#line 2732 "y.tab.c"
    break;

  case 60: /* Bit_Exp: Add_Exp  */
#line 1108 "python.y"
{
  /*$$.node = create_node(NULL,"Add_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 2744 "y.tab.c"
    break;

  case 61: /* Bit_Exp: Bit_Exp XOR Add_Exp  */
#line 1116 "python.y"
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"^",0));
  add_sibling($$.node,create_node(NULL,"Add_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  //sprintf($$.code,"^\t%s\t%s\t%s\n",$1.lhs,$3.code,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  sprintf((yyval.ctype).code,"%s\n%s\n^\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //fprintf(fp_quad,"^ \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;


}
#line 2774 "y.tab.c"
    break;

  case 62: /* Bit_Exp: Bit_Exp BAND Add_Exp  */
#line 1142 "python.y"
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"&",0));
  add_sibling($$.node,create_node(NULL,"Add_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  //sprintf($$.code,"%s\n%s\n&\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  sprintf((yyval.ctype).code,"%s\n%s\n&\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //fprintf(fp_quad,"& \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
#line 2802 "y.tab.c"
    break;

  case 63: /* Bit_Exp: Bit_Exp BOR Add_Exp  */
#line 1166 "python.y"
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"|",0));
  add_sibling($$.node,create_node(NULL,"Add_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  sprintf((yyval.ctype).lhs,temp_var);
  //sprintf($$.code,"%s\n%s\n|\t%s\t%s\t%s\n",$1.code,$3.code,$1.lhs,$3.lhs,temp_var);

  //printf("\ncode is %s\n",$$.code);

  //printf("Quadruple is :\n");
  sprintf((yyval.ctype).code,"%s\n%s\n|\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);

  //fprintf(fp_quad,"| \t %s \t %s \t \t%s",$1.lhs,$3.code,temp_var); //op a1 a2 res
  
  exprno=1;
}
#line 2831 "y.tab.c"
    break;

  case 64: /* Rel_Exp: Bit_Exp  */
#line 1192 "python.y"
{
  /*$$.node = create_node(NULL,"Bit_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 2843 "y.tab.c"
    break;

  case 65: /* Rel_Exp: Rel_Exp G Bit_Exp  */
#line 1200 "python.y"
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,">",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is : \n%s = %s > %s\n",temp_var, $1.lhs, $3.lhs);
  //printf(">\t%s\t%s\t%s\n", $1.lhs, $3.lhs, temp_var);
  sprintf((yyval.ctype).code,">\t%s\t%s\t%s\n", (yyvsp[-2].ctype).lhs, (yyvsp[0].ctype).lhs, temp_var);
  strncpy((yyval.ctype).lhs, temp_var, m+1);
}
#line 2863 "y.tab.c"
    break;

  case 66: /* Rel_Exp: Rel_Exp GE Bit_Exp  */
#line 1216 "python.y"
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,">=",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is:\n %s = %s >= %s\n",temp_var, $1.code, $3.code);
  //printf(">=\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);

  sprintf((yyval.ctype).code,"%s\n%s\n>=\t%s\t%s\t%s\n", (yyvsp[-2].ctype).code, (yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs, temp_var);
  strncpy((yyval.ctype).lhs, temp_var, m+1);
}
#line 2885 "y.tab.c"
    break;

  case 67: /* Rel_Exp: Rel_Exp L Bit_Exp  */
#line 1234 "python.y"
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"<",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is:\n %s = %s < %s\n",temp_var, $1.code, $3.code);
  //printf("<\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n<\t%s\t%s\t%s\n", (yyvsp[-2].ctype).code, (yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs, temp_var);
  strncpy((yyval.ctype).lhs, temp_var, m+1);
}
#line 2905 "y.tab.c"
    break;

  case 68: /* Rel_Exp: Rel_Exp LE Bit_Exp  */
#line 1250 "python.y"
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"<=",0));
  add_sibling($$.node,create_node(NULL,"Bit_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is:\n %s = %s <= %s\n",temp_var, $1.code, $3.code);
  //printf("<=\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);
  sprintf((yyval.ctype).code,"<=\t%s\t%s\t%s\n", (yyvsp[-2].ctype).code, (yyvsp[0].ctype).code, temp_var);
  strncpy((yyval.ctype).lhs, temp_var, m+1);
}
#line 2925 "y.tab.c"
    break;

  case 69: /* Eq_Exp: Rel_Exp  */
#line 1267 "python.y"
{
  /*$$.node = create_node(NULL,"Rel_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
}
#line 2936 "y.tab.c"
    break;

  case 70: /* Eq_Exp: Eq_Exp EOP Rel_Exp  */
#line 1274 "python.y"
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"==",0));
  add_sibling($$.node,create_node(NULL,"Rel_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is : \n%s = %s == %s\n", temp_var, $1.code, $3.code);
  //printf("==\t%s\t%s\t%s\n", $1.code, $3.code, temp_var);

  //strncpy($$.code, temp_var, m+1);   //check out
  strcpy((yyval.ctype).lhs,temp_var);
  sprintf((yyval.ctype).code,"%s\n%s\n==\t%s\t%s\t%s\n", (yyvsp[-2].ctype).code, (yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs, temp_var);
}
#line 2958 "y.tab.c"
    break;

  case 71: /* Eq_Exp: Eq_Exp NEOP Rel_Exp  */
#line 1292 "python.y"
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"!=",0));
  add_sibling($$.node,create_node(NULL,"Rel_Exp",0));
  add_child(end_node($$.node),$3.node);*/


  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';
  ////printf("code is : \n%s = %s != %s\n", temp_var, $1.code, $3.code);
  sprintf("%s\n%s\n!=\t%s\t%s\t%s\n", (yyvsp[-2].ctype).code, (yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs, temp_var);

  strncpy((yyval.ctype).lhs, temp_var, m+1);   //check out
}
#line 2979 "y.tab.c"
    break;

  case 72: /* In_Exp: Eq_Exp  */
#line 1310 "python.y"
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 2991 "y.tab.c"
    break;

  case 73: /* In_Exp: Eq_Exp IN In_Exp  */
#line 1318 "python.y"
{
  /*$$.node = create_node(NULL,"Eq_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"in",0));
  add_sibling($$.node,create_node(NULL,"In_Exp",0));
  add_child(end_node($$.node),$3.node);*/
}
#line 3003 "y.tab.c"
    break;

  case 74: /* And_Exp: In_Exp  */
#line 1327 "python.y"
{
  /*$$.node = create_node(NULL,"In_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 3015 "y.tab.c"
    break;

  case 75: /* And_Exp: In_Exp LAND And_Exp  */
#line 1335 "python.y"
{
  /*$$.node = create_node(NULL,"In_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"and",0));
  add_sibling($$.node,create_node(NULL,"And_Exp",0));
  add_child(end_node($$.node),$3.node);*/
  
  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy((yyval.ctype).lhs,temp_var);

  sprintf((yyval.ctype).code,"%s%s\nand\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);


}
#line 3037 "y.tab.c"
    break;

  case 76: /* Or_Exp: And_Exp  */
#line 1354 "python.y"
{
  (yyval.ctype)=(yyvsp[0].ctype);  
  /*$$.node = create_node(NULL,"And_Exp",0); 
  add_child($$.node,$1.node);*/

  strcpy((yyval.ctype).code,(yyvsp[0].ctype).code);
  strcpy((yyval.ctype).lhs,(yyvsp[0].ctype).lhs);
}
#line 3050 "y.tab.c"
    break;

  case 77: /* Or_Exp: And_Exp LOR Or_Exp  */
#line 1363 "python.y"
{
  (yyval.ctype)=(yyvsp[-2].ctype);  
  /*$$.node = create_node(NULL,"And_Exp",0); 
  add_child($$.node,$1.node);
  add_sibling($$.node,create_node(NULL,"or",0));
  add_sibling($$.node,create_node(NULL,"Or_Exp",0));
  add_child(end_node($$.node),$3.node);*/

  sprintf(temp_var,"t%d",tempno++);
  m = strlen(temp_var);
  temp_var[m] = '\0';

  strcpy((yyval.ctype).lhs,temp_var);

  sprintf((yyval.ctype).code,"%s%s\nor\t%s\t%s\t%s\n",(yyvsp[-2].ctype).code,(yyvsp[0].ctype).code,(yyvsp[-2].ctype).lhs,(yyvsp[0].ctype).lhs,temp_var);



}
#line 3074 "y.tab.c"
    break;


#line 3078 "y.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1384 "python.y"
 
int yyerror(char *msg) 
{ 
  printf("Syntax Error\n"); 
  return 1;
} 
 
int main() 
{ 
  Quad *allQuads = (Quad*)malloc(sizeof(Quad));

  // head = tree_init();
  // head->node = create_node(NULL,"Start",0);
  yyparse(); 
  // printf("Symbol Table\n");
  // display_symbol();
  // printf("\n\nAbstract Syntax Tree\n\n");
  // printTree(head);
  
  return 0;
}
