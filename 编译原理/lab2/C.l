%{
#include <stdio.h>
%}

%option yylineno
%x COMMENT

ID   [A-Za-z_][A-Za-z0-9_]*  
INT [1-9][0-9]*|[0]
FLOAT [0-9]*[.][0-9]+([eE][-+]?([1-9][0-9*]|[0]))?
CHAR ['][^\n][']
STRING ["][^\n]*["]
ERRORID [0-9][A-Za-z0-9]*

%%
{INT} {printf("(%s, INT)\n", yytext);}
{FLOAT}  {printf("(%s, FLOAT)\n", yytext);}
{CHAR}   {printf("(%s, CHAR)\n", yytext);}
{STRING} {printf("(%s, STRING)\n",yytext);}//string

"int"    {printf("(%s, TYPEINT)\n", yytext);}
"float"  {printf("(%s, TYPEFLOAT)\n", yytext);}
"char"   {printf("(%s, TYPECHAR)\n", yytext);}
"string" {printf("(%sm TYPESTRING)\n",yytext);}//string
"return" {printf("(%s, RETURN)\n", yytext);}

"if"     {printf("(%s, IF)\n", yytext);}
"else"   {printf("(%s, ELSE)\n", yytext);}
"while"  {printf("(%s, WHILE)\n", yytext);}
"break"	 {printf("(%s, BREAK)\n", yytext);} // break
"continue" {printf("(%s, CONTINUE)\n", yytext);} //continue
"for"	 {printf("(%s, FOR)\n", yytext);}//for
"switch" {printf("(%s, SWITCH)\n", yytext);}//switch
"case"	 {printf("(%s, CASE)\n", yytext);}//case
"struct" {printf("(%s, STRUCT)\n", yytext);}//struct
"default" {printf("(%s, DEFAULT)\n", yytext);}//DEFAULT

{ID}     {printf("(%s, IDENTIFIER)\n", yytext);}
{ERRORID}	 {printf("(%s, ERROR 禁止数字为开头的标识符)\n",yytext);}//错误标识符
":"		 {printf("(%s,COLON)\n",yytext);}
";"		 {printf("(%s, SEMI)\n", yytext);}
","		 {printf("(%s, COMMA)\n", yytext);}
">"|"<"|">="|"<="|"=="|"!=" {printf("(%s, RELOP)\n", yytext);}
"="		 {printf("(%s, ASSIGN)\n", yytext);}
"+"		 {printf("(%s, PLUS)\n", yytext);}
"-"		 {printf("(%s, MINUS)\n", yytext);}
"*"		 {printf("(%s, STAR)\n", yytext);}
"/"		 {printf("(%s, DIV)\n", yytext);}
"."      {printf("(%s, DOT)\n", yytext);}
"%"      {printf("(%s, MOD)\n", yytext);}
"&&"     {printf("(%s, AND)\n", yytext);}
"||"     {printf("(%s, OR)\n", yytext);}
"!"		 {printf("(%s, NOT)\n", yytext);}
"++"     {printf("(%s, PLUSPLUS)\n", yytext);}//自增
"--"     {printf("(%s, MINUSMINUS)\n", yytext);}//自减
"+="     {printf("(%s, PLUSASSIGN)\n", yytext);}
"-="     {printf("(%s, MINUSASSIGN)\n", yytext);}
"*="     {printf("(%s, STARASSIGN)\n", yytext);}
"/="     {printf("(%s, DIVASSIGN)\n)", yytext);}
"%="     {printf("(%s, MODASSIGN)\n", yytext);}
"("		 {printf("(%s, LP)\n", yytext);}
")"		 {printf("(%s, RP)\n", yytext);}
"{"		 {printf("(%s, LC)\n", yytext);}
"}"		 {printf("(%s, RC)\n", yytext);}
"["      {printf("(%s, LB)\n", yytext);}
"]"      {printf("(%s, RB)\n", yytext);}
" "      {}
"#"      {printf("(%s, DEF)\n", yytext);}
\/\/[^\n]*  {printf("(%s, LINECOMMENT)\n", yytext);}//匹配注释
 /* 注释 */
"/*"		{BEGIN(COMMENT);}
<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>	{printf("%s: %d: Unterminated comment\n", yytext, yylineno);}
%%

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}