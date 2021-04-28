/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 193 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
