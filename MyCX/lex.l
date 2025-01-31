%{
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "yacc.tab.h"
int line=1;
void yyerror(char *);
int yywrap(void);
int yygetchar(void);
void comment();

%}
%x COMMENT

%%
"/*"                {BEGIN(COMMENT); continue;}/*开始注释*/
<COMMENT>[^*/\n]*   {continue;}/*普通的注释内容*/
<COMMENT>\n         {line++;continue;}/*换行*/
<COMMENT>[*/]       {continue;}/* 单独出现的*或/ */
<COMMENT>"*/"       {BEGIN(INITIAL); continue;}/*结束注释*/

[ \t]   {;}//忽略空格和制表符
[\n]    {line++;}
"int"   {return INTSYM;}
"bool"  {return BOOLSYM;}
"if"    {return IFSYM;}
"else"  {return ELSESYM;}
"while" {return WHILESYM;}
"write" {return WRITESYM;}
"read"  {return READSYM;}
"true"  {return TRUESYM;}
"false" {return FALSESYM;}
"const"    {return CONSTSYM;}
"call"  {return CALLSYM;}
"function"  {return FUNCTIONSYM;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return SLASH;}
"<" {return LSS;}
">" {return GTR;}
"<="    {return LEQ;}
">="    {return GEQ;}
"=="    {return BEQ;}
"!="    {return NEQ;}
"=" {return ASS;}
"||"    {return OR;}
"&&"    {return AND;}
"!" {return NOT;}
";" {return SEMICOLON;}
"(" {return LBRA;}
")" {return RBRA;}
"{" {return LPAR;}
"}" {return RPAR;}
"," {return COMMASYM;}
"%" {return REM;}

[A-Za-z]([A-Za-z]|[0-9])*   {yylval.id=(char *)malloc(strlen(yytext)+1);
                             strcpy(yylval.id,yytext);
                             return ID;
                             }//识别标识符

[-]?[0-9]+		{yylval.num=atoi(yytext);return NUM;}//识别数字

.	{printf("?\n");yyerror("Unknown character!");}//处理未知字符
%%

void redirectInput(FILE *input)
{
	yyin=input;
}

int yywrap(void)
{
	return 1;
}

void comment() {
    char c, c1;
loop:
    while ((c = input()) != '*' && c != 0) {
        if (c == '\n') {line++;}
	}
    if ((c1 = input()) != '/' && c != 0) {
        unput(c1);
        goto loop;
    }
}