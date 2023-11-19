%option noyywrap

%{
#include <stdio.h>
#include <string.h>
%}

%%

"abc" { printf("ABC"); }

%%

int main() {
	yylex();

	return 0;
}
