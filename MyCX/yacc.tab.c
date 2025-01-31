
/*  A Bison parser, made from yacc.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	IFSYM	257
#define	ELSESYM	258
#define	WHILESYM	259
#define	INTSYM	260
#define	BOOLSYM	261
#define	READSYM	262
#define	WRITESYM	263
#define	TRUESYM	264
#define	FALSESYM	265
#define	CONSTSYM	266
#define	FUNCTIONSYM	267
#define	CALLSYM	268
#define	NEQ	269
#define	BEQ	270
#define	GEQ	271
#define	LEQ	272
#define	LSS	273
#define	GTR	274
#define	ASS	275
#define	REM	276
#define	PLUS	277
#define	MINUS	278
#define	TIMES	279
#define	SLASH	280
#define	LPAR	281
#define	RPAR	282
#define	LBRA	283
#define	RBRA	284
#define	SEMICOLON	285
#define	OR	286
#define	AND	287
#define	NOT	288
#define	COMMASYM	289
#define	ID	290
#define	NUM	291
#define	IFX	292

#line 1 "yacc.y"

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>

#define bool int
#define true 1
#define false 0
#define txmax 100     /* 符号表容量 */
#define al 10         /* 标识符的最大长度 */
#define amax 2048     /* 地址上界*/
#define levmax 3      /* 最大允许过程嵌套声明层数*/
#define cxmax 200     /* 最多的虚拟机代码数 */
#define stacksize 500 /* 运行时数据栈元素最多为500个 */

/* 符号表中的类型 */
enum object {
    variable,
};

enum vartype{
	inttype,
	booltype,
};


/* 符号表结构 */
typedef struct
{
	char name[al];      /* 名字 */
	enum object kind;   /* 类型：var */
	int value;	/* 仅限const使用 */
	int level;          /* 所处层，仅const不使用 */
	int adr;            /* 地址，仅const不使用 */
	int size;
	enum vartype type;	/* 变量类型 */
}tablestruct;

tablestruct table[txmax]; /* 符号表 */

/* 虚拟机代码指令 */
enum fct {
    lit,     opr,     lod,
    sto,    ini,
    jmp,     jpc,
    cal,     blo,    fre
};

/* 虚拟机代码结构 */
struct instruction
{
	enum fct f;   /* 虚拟机代码指令 */
	int l;        /* 引用层与声明层的层次差 */
	int a;        /* 根据f的不同而不同, lodarr中表示基址 */
};

struct instruction code[cxmax]; /* 存放虚拟机代码的数组 */

int tx;         /* 符号表当前尾指针 */
int adrx;//当前分配到的地址指针（地址从1开始）
int cx;         /* 虚拟机代码指针, 取值范围[0, cxmax-1] */
int leveltable[5]; // 嵌套索引表
int lev;
char id[al];
int number;//当前数字
//下面两项必输出到文件，无需问用户与否
//bool listswitch;   /* 显示虚拟机代码与否 */
//bool tableswitch;  /* 显示符号表与否 */

FILE* fin;      /* 输入源文件 */
FILE* ftable;	  /* 输出符号表 */
FILE* fcode;    /* 输出虚拟机代码 */
FILE* foutput;  /* 输出出错示意（如有错） */
FILE* fresult;  /* 输出执行结果 */
FILE* fstack;   /* 输出每一步栈的结果 */
//char fname[al];
int err;	/* 错误个数 */
extern int line;
char varType[10]; //判断当前id是整形还是布尔类型还是字符类型

int yylex(void);
void yyerror(char *s);
int redirectInput(FILE* fin);

void init();
void enter(enum vartype t, enum object k);
int position(char *s);
void setdx(int n);
void gen(enum fct x,int y, int z);
void listall();
void displaytable();
void interpret();
int base(int l, int *s, int b);

#line 99 "yacc.y"
typedef union{
char *id;
int num;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		131
#define	YYFLAG		-32768
#define	YYNTBASE	39

#define YYTRANSLATE(x) ((unsigned)(x) <= 292 ? yytranslate[x] : 77)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     9,    10,    11,    12,    22,    25,    26,
    27,    32,    33,    38,    40,    42,    45,    46,    48,    50,
    52,    54,    56,    58,    60,    65,    70,    76,    78,    84,
    86,    90,    91,   100,   101,   106,   107,   108,   117,   121,
   123,   127,   129,   131,   133,   136,   140,   142,   146,   150,
   154,   158,   162,   166,   168,   170,   172,   174,   177,   180,
   182,   186,   190,   192,   196,   200,   204,   206,   210,   211,
   212,   213
};

static const short yyrhs[] = {    40,
     0,     0,    27,    41,    46,    52,    28,     0,     0,     0,
     0,    27,    75,    43,    46,    52,    44,    28,    45,    76,
     0,    46,    47,     0,     0,     0,     6,    48,    50,    31,
     0,     0,     7,    49,    51,    31,     0,    36,     0,    36,
     0,    52,    53,     0,     0,    54,     0,    55,     0,    57,
     0,    59,     0,    63,     0,    42,     0,     1,     0,    50,
    21,    71,    31,     0,    51,    21,    70,    31,     0,     8,
    29,    56,    30,    31,     0,    50,     0,     9,    29,    58,
    30,    31,     0,    71,     0,    58,    35,    71,     0,     0,
     3,    29,    65,    30,    74,    60,    53,    61,     0,     0,
     4,    74,    62,    53,     0,     0,     0,     5,    74,    29,
    65,    30,    74,    64,    53,     0,    65,    32,    66,     0,
    66,     0,    66,    33,    67,     0,    67,     0,    51,     0,
    70,     0,    34,    67,     0,    29,    65,    30,     0,    68,
     0,    69,    16,    71,     0,    69,    15,    71,     0,    69,
    19,    71,     0,    69,    20,    71,     0,    69,    18,    71,
     0,    69,    17,    71,     0,    50,     0,    37,     0,    10,
     0,    11,     0,    23,    72,     0,    24,    72,     0,    72,
     0,    71,    23,    72,     0,    71,    24,    72,     0,    73,
     0,    72,    25,    73,     0,    72,    26,    73,     0,    72,
    22,    73,     0,    69,     0,    29,    71,    30,     0,     0,
     0,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   123,   125,   128,   133,   137,   139,   142,   145,   148,   151,
   153,   156,   158,   163,   170,   178,   178,   181,   182,   183,
   184,   185,   186,   187,   190,   199,   210,   213,   223,   225,
   229,   235,   237,   242,   244,   248,   253,   255,   261,   264,
   267,   270,   274,   281,   282,   285,   286,   289,   292,   295,
   298,   301,   304,   309,   317,   323,   326,   331,   334,   338,
   341,   345,   351,   354,   358,   362,   368,   371,   377,   383,
   388,   395
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","IFSYM",
"ELSESYM","WHILESYM","INTSYM","BOOLSYM","READSYM","WRITESYM","TRUESYM","FALSESYM",
"CONSTSYM","FUNCTIONSYM","CALLSYM","NEQ","BEQ","GEQ","LEQ","LSS","GTR","ASS",
"REM","PLUS","MINUS","TIMES","SLASH","LPAR","RPAR","LBRA","RBRA","SEMICOLON",
"OR","AND","NOT","COMMASYM","ID","NUM","IFX","program","block","@1","blockstmt",
"@2","@3","@4","decls","decl","@5","@6","aid","bid","stmts","stmt","assstmt",
"readstmt","readvar","writestmt","writelist","ifstmt","@7","elsestmt","@8","whilestmt",
"@9","bexpr","bterm","bfactor","rel","idnum","truefalse","expression","term",
"factor","get_code_addr","inc_level","dec_level", NULL
};
#endif

static const short yyr1[] = {     0,
    39,    41,    40,    43,    44,    45,    42,    46,    46,    48,
    47,    49,    47,    50,    51,    52,    52,    53,    53,    53,
    53,    53,    53,    53,    54,    54,    55,    56,    57,    58,
    58,    60,    59,    62,    61,    61,    64,    63,    65,    65,
    66,    66,    67,    67,    67,    67,    67,    68,    68,    68,
    68,    68,    68,    69,    69,    70,    70,    71,    71,    71,
    71,    71,    72,    72,    72,    72,    73,    73,    74,    -1,
    75,    76
};

static const short yyr2[] = {     0,
     1,     0,     5,     0,     0,     0,     9,     2,     0,     0,
     4,     0,     4,     1,     1,     2,     0,     1,     1,     1,
     1,     1,     1,     1,     4,     4,     5,     1,     5,     1,
     3,     0,     8,     0,     4,     0,     0,     8,     3,     1,
     3,     1,     1,     1,     2,     3,     1,     3,     3,     3,
     3,     3,     3,     1,     1,     1,     1,     2,     2,     1,
     3,     3,     1,     3,     3,     3,     1,     3,     0,     0,
     0,     0
};

static const short yydefact[] = {     0,
     2,     1,     9,    17,    10,    12,     8,     0,     0,     0,
    24,     0,    69,     0,     0,    71,     3,    14,    23,     0,
     0,    16,    18,    19,    20,    21,    22,    14,     0,    15,
     0,     0,     0,     0,     0,     4,     0,     0,    11,    13,
    56,    57,     0,     0,    55,    54,    43,     0,    40,    42,
    47,     0,    44,     0,    28,     0,     0,     0,     0,     0,
    67,    30,    60,    63,     9,     0,     0,     0,    45,    69,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
    17,    25,    26,    46,    32,    39,    41,    49,    48,    53,
    52,    50,    51,    69,    27,    68,    29,    31,    61,    62,
    66,    64,    65,     0,     0,    37,     0,    36,     0,     6,
    69,    33,    38,    72,    34,     7,     0,    35,     0,     0,
     0
};

static const short yydefgoto[] = {   129,
     2,     3,    19,    65,   117,   124,     4,     7,     9,    10,
    46,    47,     8,    22,    23,    24,    56,    25,    60,    26,
   115,   122,   127,    27,   119,    48,    49,    50,    51,    61,
    53,    62,    63,    64,    33,    36,   126
};

static const short yypact[] = {   -14,
-32768,-32768,-32768,    49,-32768,-32768,-32768,    30,   -13,    -4,
-32768,    43,-32768,    54,    61,-32768,-32768,    52,-32768,    38,
    57,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    62,-32768,
    86,    60,    95,   -13,   -12,-32768,   -12,    94,-32768,-32768,
-32768,-32768,    60,    60,-32768,-32768,-32768,   -23,    92,-32768,
-32768,    83,-32768,    60,-32768,    96,    40,    40,   -12,   -20,
-32768,    99,    66,-32768,-32768,     5,    97,    80,-32768,-32768,
    60,    60,   -12,   -12,   -12,   -12,   -12,   -12,    88,    98,
    66,    66,    51,   100,   -12,    40,    40,    40,    40,    40,
    49,-32768,-32768,-32768,-32768,    92,-32768,    99,    99,    99,
    99,    99,    99,-32768,-32768,-32768,-32768,    99,    66,    66,
-32768,-32768,-32768,    59,    13,-32768,   102,   123,    13,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    13,-32768,   132,   133,
-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    69,-32768,-32768,-32768,
    -8,    -6,    44,   -54,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,     9,    65,   -38,-32768,   -24,
   101,   -32,    -7,    26,   -67,-32768,-32768
};


#define	YYLAST		139


static const short yytable[] = {    20,
    29,    21,    95,    31,    66,    69,    70,    52,    71,    84,
    57,    58,     1,    11,    85,    12,    59,    13,    52,    52,
    14,    15,    28,    28,    45,    55,    83,    86,    87,    52,
    11,    30,    12,    97,    13,    92,   116,    14,    15,    16,
    98,    99,   100,   101,   102,   103,    52,    52,    18,    81,
    82,    68,   108,   125,     5,     6,    16,    17,    37,    11,
   118,    12,    79,    13,   123,    18,    14,    15,    59,    41,
    42,    32,   128,    86,    87,    28,    45,    38,   109,   110,
   106,   -15,    34,   -15,   -15,    16,    -5,    88,    43,    35,
    89,    90,    39,    44,    18,    18,    45,    73,    74,    75,
    76,    77,    78,    41,    42,    20,    20,    21,    21,    94,
    20,    71,    21,   111,   112,   113,    40,   104,    20,    71,
    21,    86,    87,    54,    72,    80,   121,    93,   105,   120,
   107,   130,   131,    91,   114,    96,     0,     0,    67
};

static const short yycheck[] = {     8,
     9,     8,    70,    10,    37,    44,    30,    32,    32,    30,
    23,    24,    27,     1,    35,     3,    29,     5,    43,    44,
     8,     9,    36,    36,    37,    34,    59,    23,    24,    54,
     1,    36,     3,    72,     5,    31,   104,     8,     9,    27,
    73,    74,    75,    76,    77,    78,    71,    72,    36,    57,
    58,    43,    85,   121,     6,     7,    27,    28,    21,     1,
   115,     3,    54,     5,   119,    36,     8,     9,    29,    10,
    11,    29,   127,    23,    24,    36,    37,    21,    86,    87,
    30,    30,    29,    32,    33,    27,    28,    22,    29,    29,
    25,    26,    31,    34,    36,    36,    37,    15,    16,    17,
    18,    19,    20,    10,    11,   114,   115,   114,   115,    30,
   119,    32,   119,    88,    89,    90,    31,    30,   127,    32,
   127,    23,    24,    29,    33,    30,     4,    31,    31,    28,
    31,     0,     0,    65,    91,    71,    -1,    -1,    38
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 125 "yacc.y"
{
	yyval.num=cx;
	gen(jmp,0,0);
;
    break;}
case 3:
#line 129 "yacc.y"
{
	gen(opr,0,0);
;
    break;}
case 4:
#line 133 "yacc.y"
{
	leveltable[lev]=tx;
	gen(blo,0,0);
;
    break;}
case 5:
#line 137 "yacc.y"
{
	gen(fre,0,0);
;
    break;}
case 6:
#line 139 "yacc.y"
{
	tx=leveltable[lev];
;
    break;}
case 8:
#line 145 "yacc.y"
{
	yyval.num=yyvsp[-1].num+yyvsp[0].num;
;
    break;}
case 9:
#line 148 "yacc.y"
{yyval.num=0;;
    break;}
case 10:
#line 151 "yacc.y"
{
	strcpy(varType,"int");
;
    break;}
case 11:
#line 153 "yacc.y"
{
	yyval.num=1;
;
    break;}
case 12:
#line 156 "yacc.y"
{
	strcpy(varType,"bool");
;
    break;}
case 13:
#line 158 "yacc.y"
{
	yyval.num=1;
;
    break;}
case 14:
#line 163 "yacc.y"
{
	strcpy(id,yyvsp[0].id);
	if(!strcmp(varType,"int"))
		enter(inttype,variable);
	yyval.num=position(yyvsp[0].id);
;
    break;}
case 15:
#line 170 "yacc.y"
{
	strcpy(id,yyvsp[0].id);
	if(!strcmp(varType,"bool"))
		enter(booltype,variable);
	yyval.num=position(yyvsp[0].id);
;
    break;}
case 24:
#line 187 "yacc.y"
{;
    break;}
case 25:
#line 190 "yacc.y"
{
	if(yyvsp[-3].num==0){
		yyerror("Symbol does not exist!");
	}else if(table[yyvsp[-3].num].kind==variable && table[yyvsp[-3].num].type==inttype){
		gen(sto,lev,table[yyvsp[-3].num].adr);
	}else{
		yyerror("Symbol should be variable and type should be int!");
	}
;
    break;}
case 26:
#line 199 "yacc.y"
{
	if(yyvsp[-3].num==0){
		yyerror("Symbol does not exist!");
	}else if(table[yyvsp[-3].num].kind==variable && table[yyvsp[-3].num].type==booltype){
		gen(sto,lev,table[yyvsp[-3].num].adr);
	}else{
		yyerror("Symbol should be variable and type should be bool!");
	}
;
    break;}
case 28:
#line 213 "yacc.y"
{
	if(table[yyvsp[0].num].kind==variable && table[yyvsp[0].num].type==inttype){
		gen(opr,0,17);
		gen(sto,lev-table[yyvsp[0].num].level,table[yyvsp[0].num].adr);
	}else{
		yyerror("Only int avilable!");
	}
;
    break;}
case 30:
#line 225 "yacc.y"
{
	gen(opr,0,15);
	gen(opr,0,16);
;
    break;}
case 31:
#line 229 "yacc.y"
{
	gen(opr,0,15);
	gen(opr,0,16);
;
    break;}
case 32:
#line 235 "yacc.y"
{
	gen(jpc,0,0);
;
    break;}
case 33:
#line 237 "yacc.y"
{
	code[yyvsp[-3].num].a=yyvsp[0].num;
;
    break;}
case 34:
#line 242 "yacc.y"
{
	gen(jmp,0,0);
;
    break;}
case 35:
#line 244 "yacc.y"
{
	yyval.num=yyvsp[-2].num+1;
	code[yyvsp[-2].num].a=cx;
;
    break;}
case 36:
#line 248 "yacc.y"
{
	yyval.num=cx;
;
    break;}
case 37:
#line 253 "yacc.y"
{
	gen(jpc,0,0);
;
    break;}
case 38:
#line 255 "yacc.y"
{
	gen(jmp,0,yyvsp[-6].num);
	code[yyvsp[-2].num].a=cx;
;
    break;}
case 39:
#line 261 "yacc.y"
{
	gen(opr,0,7);//或运算
;
    break;}
case 41:
#line 267 "yacc.y"
{
	gen(opr,0,6);//与运算
;
    break;}
case 43:
#line 274 "yacc.y"
{
	if(yyvsp[0].num==0){
		yyerror("Symbol does not exist!");
	}else{
		gen(lod,lev,table[yyvsp[0].num].adr);
	}
;
    break;}
case 45:
#line 282 "yacc.y"
{
	gen(opr,0,8);//非运算
;
    break;}
case 48:
#line 289 "yacc.y"
{
	gen(opr,0,9);
;
    break;}
case 49:
#line 292 "yacc.y"
{
	gen(opr,0,10);
;
    break;}
case 50:
#line 295 "yacc.y"
{
	gen(opr,0,11);
;
    break;}
case 51:
#line 298 "yacc.y"
{
	gen(opr,0,12);
;
    break;}
case 52:
#line 301 "yacc.y"
{
	gen(opr,0,13);
;
    break;}
case 53:
#line 304 "yacc.y"
{
	gen(opr,0, 14)
;
    break;}
case 54:
#line 309 "yacc.y"
{
	if(yyvsp[0].num==0){
		yyerror("Symbol does not exist!");
	}else{
                yyval.num = 0;
                gen(lod, lev, table[yyvsp[0].num].adr);
        }
;
    break;}
case 55:
#line 317 "yacc.y"
{
	yyval.num=0;
	gen(lit,0,yyvsp[0].num);
;
    break;}
case 56:
#line 323 "yacc.y"
{
	gen(lit,0,1);
;
    break;}
case 57:
#line 326 "yacc.y"
{
	gen(lit,0,0);
;
    break;}
case 58:
#line 331 "yacc.y"
{
	yyval.num=0;
;
    break;}
case 59:
#line 334 "yacc.y"
{
	yyval.num=0;
	gen(opr,0,1)//取反
;
    break;}
case 60:
#line 338 "yacc.y"
{
	yyval.num=yyvsp[0].num;
;
    break;}
case 61:
#line 341 "yacc.y"
{
	yyval.num=0;
	gen(opr,0,2);
;
    break;}
case 62:
#line 345 "yacc.y"
{
	yyval.num=0;
	gen(opr,0,3);
;
    break;}
case 63:
#line 351 "yacc.y"
{
	yyval.num=yyvsp[0].num;
;
    break;}
case 64:
#line 354 "yacc.y"
{
	yyval.num=0;
	gen(opr,0,4);
;
    break;}
case 65:
#line 358 "yacc.y"
{
	yyval.num=0;
	gen(opr,0,5);
;
    break;}
case 66:
#line 362 "yacc.y"
{
	yyval.num=0;
	gen(opr,0,18);
;
    break;}
case 67:
#line 368 "yacc.y"
{
	yyval.num=yyvsp[0].num;
;
    break;}
case 68:
#line 371 "yacc.y"
{
	yyval.num=0;
;
    break;}
case 69:
#line 378 "yacc.y"
{
	yyval.num = cx;
;
    break;}
case 70:
#line 383 "yacc.y"
{
	yyval.num=tx;
;
    break;}
case 71:
#line 388 "yacc.y"
{
	lev++;
	if(lev>levmax)
		yyerror("Level is too large!");
;
    break;}
case 72:
#line 395 "yacc.y"
{
	lev--;
;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 400 "yacc.y"

//程序部分
void yyerror(char *s)
{
	err=err+1;
	fprintf(foutput, "[line %d] error: %s\n", line, s);
}

//初始化
void init()
{
	tx=0;
	adrx=1;
	cx=0;
	lev=0;
	leveltable[0]=0;
	number=0;
	err=0;
}

//符号入表
void enter(enum vartype t, enum object k)
{
	tx = tx + 1;
    	strcpy(table[tx].name, id);
    	table[tx].kind = k;
    	switch(k) {
    	case variable:
        	table[tx].level = lev;
        	table[tx].type = t;
        	break;
    	}
}

int position(char *s)
{
	int i;
	strcpy(table[0].name,s);
	i=tx;
	while(strcmp(table[i].name,s)!=0)
		i--;
	return i;
}

void setdx(int n){
	int i;
	for(i=1;i<=n;i++){
		table[tx-i+1].adr=n-i+3;
	}
}

void gen(enum fct x,int y, int z)
{
	if(cx>=cxmax)
	{
		printf("Program is too long!\n");
		exit(1);
	}
	if(z>=amax)
	{
		printf("Displacement address is too big!\n");
		exit(1);
	}
	code[cx].f=x;
	code[cx].l=y;
	code[cx].a=z;
	cx++;
}

void listall()
{
	int i;
	char name[][4]=
	{
		{"lit"},{"opr"},{"lod"},{"sto"},{"ini"},{"jmp"},{"jpc"},{"cal"},{"blo"},{"fre"}
	};
	for (i = 0; i < cx; i++)
	{
		fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
	}
	fprintf(fcode,"\n");
}

void displaytable()
{
	int i;
	for (i = 1; i <= tx; i++)
		{
			switch (table[i].kind)
			{
				case variable:
					fprintf(ftable, "%d\tname=%s\tlev=%d\taddr=%d\ttype=%d\n", i,table[i].name,table[i].level,table[i].adr,table[i].type);
					break;
			}
		}
		fprintf(ftable, "\n");
}

void printstack(int t, int p, int *s) {
    	int i;
        fprintf(fstack, "pcode %2d: |", p);
        for (i = 1; i <= t; i++)
            fprintf(fstack, " %2d |", s[i]);
        fprintf(fstack, "%s", "\n");
}

void interpret(){
	int p=0;//指令指针
	int b=1;//指令基址
	int t=0;//栈顶指针

	struct instruction i;//存放当前指令
	int s[stacksize];

	printf("Start CX\n");
	fprintf(fresult,"Start CX\n");
	s[0]=0;
	s[1]=0;
	s[2]=0;
	s[3]=0;
	do{
		i=code[p];
		printf("%d\n",p);
		p++;
		switch(i.f){
			case lit:
				t=t+1;
				s[t]=i.a;
				//printf("lit\n");
				//printstack(t, p, s);
				break;
			case opr:
				switch(i.a){
					case 0:
						t=b-1;
						p=s[t+3];
						b=s[t+2];
						break;
					case 1:
						s[t]=-s[t];
						break;
					case 2:
						t=t-1;
						s[t]=s[t]+s[t+1];
						break;
					case 3:
						t=t-1;
						s[t]=s[t]-s[t+1];
						break;
					case 4:
						t=t-1;
						s[t]=s[t]*s[t+1];
						break;
					case 5:
						t=t-1;
						s[t]=s[t]/s[t+1];
						break;
					case 6:
						t=t-1;
						s[t]=s[t]&&s[t+1];
						break;
					case 7:
						t=t-1;
						s[t]=s[t]||s[t+1];
						break;
					case 8:
						t=t-1;
						s[t]=!s[t];
						break;
					case 9:
						t=t-1;
						s[t]=(s[t]==s[t+1]);
						break;
					case 10:
						t=t-1;
						s[t]=(s[t]!=s[t+1]);
						break;
					case 11:
						t=t-1;
						s[t]=(s[t]<s[t+1]);
						break;
					case 12:
						t=t-1;
						s[t]=(s[t]>s[t+1]);
						break;
					case 13:
						t=t-1;
						s[t]=(s[t]<=s[t+1]);
						break;
					case 14:
						t=t-1;
						s[t]=(s[t]>=s[t+1]);
						break;
					case 15:
						fprintf(fresult,"%d",s[t]);
						t=t-1;
						break;
					case 16:
						fprintf(fresult,"\n");
                                                break;
                                        case 17:
                                        	t=t+1;
                                        	printf("Please input: ");
                                        	fprintf(fresult,"input a number: ");
                                        	scanf("%d",&(s[t]));
                                        	getchar();
                                        	fprintf(fresult,"%d\n",s[t]);
                                        	break;
                                        case 18:
                                        	t=t-1;
                                        	s[t]=s[t]%s[t+1];
                                        	break;
				}
				//printstack(t, p, s);
				break;
			case lod:
				t=t+1;
				s[t]=s[i.a];
				//printstack(t, p, s);
				break;
			case sto:
				s[i.a]=s[t];
				t=t-1;
				//printf("sto\n");
				//printstack(t, p, s);
				break;
			case ini:
				t=t+i.a;
				//printstack(t, p, s);
				break;
			case jmp:
				p=i.a;
				//printstack(t, p, s);
				break;
			case jpc:
				if(s[t]==0)
					p=i.a;
				t=t-1;
				//printstack(t, p, s);
				break;
			case blo: //不改变p
                                s[t + 1] = base(i.l, s, b);
                                s[t + 2] = b;
                                b = t + 1;
                                printstack(t, p, s);
                                break;
                        case fre: //不改变p
                                t = b - 1;
                                b = s[t + 2];
                                printstack(t, p, s);
                                break;
                        case cal:
                                s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
                                s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
                                s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
                                b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
                                p = i.a;  /* 跳转 */
                                printstack(t, p, s);
                                break;
		}
	}while(p!=0);
	fprintf(fresult,"End CX\n");
}

int base(int l, int *s, int b) {
    int b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l = l - 1;
    }
    return b1;
}


int main(void)
{
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Can't open the input file!\n");
		exit(1);
	}
	if ((foutput = fopen("foutput.txt", "w")) == NULL)
  {
		printf("Can't open the output file!\n");
		exit(1);
	}
	if ((ftable = fopen("ftable.txt", "w")) == NULL)
	{
		printf("Can't open ftable.txt file!\n");
		exit(1);
	}

	redirectInput(fin);
	init();
  	yyparse();
	if(err == 0)
	{
		fprintf(foutput, "\n===Parsing success!===\n");
		//displaytable();
		if ((fcode = fopen("fcode.txt", "w")) == NULL)
		{
			printf("Can't open fcode.txt file!\n");
			exit(1);
		}
		if ((fresult = fopen("fresult.txt", "w")) == NULL) {
                        printf("Can't open fresult.txt file!\n");
                        exit(1);
                }
                if ((fstack = fopen("fstack.txt", "w")) == NULL) {
                        printf("Can't open fresult.txt file!\n");
                        exit(1);
                }

		listall();  /* 输出所有代码 */
		fclose(fcode);

		interpret();  /* 调用解释执行程序 */
                fclose(fresult);
                fclose(fstack);
	}
  else
	{
		printf("%d errors in CX program.Please corract the errors!\n",err);
		fprintf(foutput,"%d errors in CX program.Please corract the errors!\n",err);

	}

	fclose(ftable);
    fclose(foutput);
	fclose(fin);
	return 0;
}