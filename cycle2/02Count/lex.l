%option noyywrap

%{
#include <stdio.h>
#include <string.h>
int chr = 0, words = 0, lines = 0;
char *temp;
int isBlank = 1, noWords = 1;
%}

%%

[a-zA-Z0-9{}()=<>.] {++chr; isBlank = 0; noWords = 0;} 
[ \t]*		{ if (!noWords) ++words; noWords = 1;}
[\n]	{++lines; if(!isBlank && !noWords) ++words; isBlank = 1; noWords=1;}

%%

int main() {
	FILE *myfile = fopen("input.asw", "r");
	yyin = myfile;

	yylex();

	printf("\nCharacters: %d\nWords: %d\nLines: %d\n", chr, words, lines);

	fclose(myfile);

	return 0;
}
