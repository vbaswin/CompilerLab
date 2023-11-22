%option noyywrap

%{
#include <stdio.h>
%}


%%

[a-zA-Z]+[0-9a-zA-Z]* {printf("identifier");}
[0-9]+	{printf("digits");}


%%

int main() {
	FILE *fp = fopen("input.txt", "r");

	// yyin =fp;
	yylex();

	fclose(fp);
}
