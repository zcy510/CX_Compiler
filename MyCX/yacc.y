%{
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
%}

//辅助定义部分
%union{
char *id;
int num;
}

%token IFSYM ELSESYM WHILESYM INTSYM BOOLSYM READSYM WRITESYM TRUESYM FALSESYM CONSTSYM FUNCTIONSYM CALLSYM
%token NEQ BEQ GEQ LEQ LSS GTR ASS REM
%token PLUS MINUS TIMES SLASH LPAR RPAR LBRA RBRA SEMICOLON OR AND NOT COMMASYM


%token <id> ID
%token <num> NUM

%type <num> bid aid
%type <num> decls decl
%type <num> get_code_addr
%type <num> get_table_addr
%type <num> term factor expression idnum
%type <num> elsestmt

%nonassoc IFX
%nonassoc ELSESYM

%%
program: block;

block: LPAR{
	$<num>$=cx;
	gen(jmp,0,0);
} decls stmts RPAR
{
	gen(opr,0,0);
};

blockstmt: LPAR inc_level{
	leveltable[lev]=tx;
	gen(blo,0,0);
}
decls stmts{
	gen(fre,0,0);
} RPAR{
	tx=leveltable[lev];
}dec_level
;


decls: decls decl{
	$$=$1+$2;
}
|{$$=0;}
;

decl: INTSYM{
	strcpy(varType,"int");
} aid SEMICOLON{
	$$=1;
}
| BOOLSYM{
	strcpy(varType,"bool");
} bid SEMICOLON{
	$$=1;
}
;

aid: ID{
	strcpy(id,$1);
	if(!strcmp(varType,"int"))
		enter(inttype,variable);
	$$=position($1);
}

bid: ID{
	strcpy(id,$1);
	if(!strcmp(varType,"bool"))
		enter(booltype,variable);
	$$=position($1);
}


stmts: stmts stmt |;


stmt: assstmt
| readstmt
| writestmt
| ifstmt
| whilestmt
| blockstmt
| error{}
;

assstmt: aid ASS expression SEMICOLON{
	if($1==0){
		yyerror("Symbol does not exist!");
	}else if(table[$1].kind==variable && table[$1].type==inttype){
		gen(sto,lev,table[$1].adr);
	}else{
		yyerror("Symbol should be variable and type should be int!");
	}
}
| bid ASS truefalse SEMICOLON{
	if($1==0){
		yyerror("Symbol does not exist!");
	}else if(table[$1].kind==variable && table[$1].type==booltype){
		gen(sto,lev,table[$1].adr);
	}else{
		yyerror("Symbol should be variable and type should be bool!");
	}
}
;

readstmt: READSYM LBRA readvar RBRA SEMICOLON;


readvar: aid{
	if(table[$1].kind==variable && table[$1].type==inttype){
		gen(opr,0,17);
		gen(sto,lev,table[$1].adr);
	}else{
		yyerror("Only int avilable!");
	}
}
;

writestmt: WRITESYM LBRA writelist RBRA SEMICOLON;

writelist: expression{
	gen(opr,0,15);
	gen(opr,0,16);
}
| writelist COMMASYM expression{
	gen(opr,0,15);
	gen(opr,0,16);
}
;

ifstmt: IFSYM LBRA bexpr RBRA get_code_addr{
	gen(jpc,0,0);
} stmt elsestmt{
	code[$5].a=$8;
}
;

elsestmt: ELSESYM get_code_addr{
	gen(jmp,0,0);
}stmt{
	$$=$2+1;
	code[$2].a=cx;
}
| %prec IFX{
	$$=cx;
}
;

whilestmt: WHILESYM get_code_addr LBRA bexpr RBRA get_code_addr{
	gen(jpc,0,0);
}stmt{
	gen(jmp,0,$2);
	code[$6].a=cx;
}
;

bexpr: bexpr OR bterm{
	gen(opr,0,7);//或运算
}
| bterm
;

bterm: bterm AND bfactor{
	gen(opr,0,6);//与运算
}
| bfactor
;


bfactor: bid{
	if($1==0){
		yyerror("Symbol does not exist!");
	}else{
		gen(lod,lev,table[$1].adr);
	}
}
|truefalse
| NOT bfactor{
	gen(opr,0,8);//非运算
}
| LBRA bexpr RBRA
| rel
;

rel: idnum BEQ expression{
	gen(opr,0,9);
}
| idnum NEQ expression{
	gen(opr,0,10);
}
| idnum LSS expression{
	gen(opr,0,11);
}
| idnum GTR expression{
	gen(opr,0,12);
}
| idnum LEQ expression{
	gen(opr,0,13);
}
| idnum GEQ expression{
	gen(opr,0, 14)
}
;

idnum: aid{
	if($1==0){
		yyerror("Symbol does not exist!");
	}else{
                $$ = 0;
                gen(lod, lev, table[$1].adr);
        }
}
| NUM{
	$$=0;
	gen(lit,0,$1);
}
;

truefalse: TRUESYM{
	gen(lit,0,1);
}
| FALSESYM{
	gen(lit,0,0);
}
;

expression: PLUS term{
	$$=0;
}
| MINUS term{
	$$=0;
	gen(opr,0,1)//取反
}
| term{
	$$=$1;
}
| expression PLUS term{
	$$=0;
	gen(opr,0,2);
}
| expression MINUS term{
	$$=0;
	gen(opr,0,3);
}
;

term: factor{
	$$=$1;
}
| term TIMES factor{
	$$=0;
	gen(opr,0,4);
}
| term SLASH factor{
	$$=0;
	gen(opr,0,5);
}
| term REM factor{
	$$=0;
	gen(opr,0,18);
}
;

factor: idnum{
	$$=$1;
}
| LBRA expression RBRA{
	$$=0;
}
;


get_code_addr:
{
	$$ = cx;
}
;

get_table_addr:{
	$$=tx;
}
;

inc_level:{
	lev++;
	if(lev>levmax)
		yyerror("Level is too large!");
}
;

dec_level:{
	lev--;
}
;

%%
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