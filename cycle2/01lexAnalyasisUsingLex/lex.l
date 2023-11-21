%option noyywrap

%{
#include <stdio.h>
%}

%%

int |
float |
char |
for |
while |
if |
struct |
continue |
break |
void |
else |
double |
return { printf("%s\tKeyword\n", yytext); }


\"([a-zA-Z0-9]*)\"	{printf("%s\tString\n", yytext);}

[a-zA-Z][a-zA-Z0-9]*	{ printf("%s\tIdentifier\n", yytext); }

"++" |
"--" 	{printf("%s\tUnary Operator\n", yytext);}

"+"	|
"-" |
"*" |
"/" {printf("%s\tArithmetic Operator\n", yytext);}



">"	|
"<" |
"=" |
">=" |
"<=" |
"==" {printf("%s\tRelational Operator\n", yytext);}

";" |
"(" |
")" |
"{" |
"}" |
"." {printf("%s\tSpecial Character\n", yytext);}

[0-9]	{printf("%s\tDigit\n", yytext);}


[ \t\n]*

%%

int main() {
	FILE *myfile = fopen("input.asw", "r");
	yyin = myfile;

	printf("\n");
	yylex();
	printf("\n");

	return 0;
}
