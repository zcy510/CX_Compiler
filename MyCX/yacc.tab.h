typedef union{
char *id;
int num;
} YYSTYPE;
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


extern YYSTYPE yylval;
