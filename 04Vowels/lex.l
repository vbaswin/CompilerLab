%option noyywrap

%{
#include <stdio.h>
#include <string.h>
int vowels = 0, consonants = 0;
%}

%%

[\n]			{ return 0; }
[aeiouAEIOU]	{ ++vowels; }
[a-zA-Z]		{ ++consonants; }
.				{ }

%%

int main() {
	yylex();

	printf("Vowels: %d\nConsonants: %d\n", vowels, consonants);

	return 0;
}
