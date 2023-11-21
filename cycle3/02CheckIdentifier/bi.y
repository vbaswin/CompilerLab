%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *s);
%}

%token DIGIT LETTER NL

%%

E: 	T NL { printf("\nValid Identifier!!\n"); exit(0); }

T: LETTER S

S: LETTER S |
	DIGIT S |
	;

%%

int main() {
	printf("Enter the identifier: ");
	yyparse();

	return 0;
}

int yyerror(char *s) {
	printf("\nInvalid Identifier!!\n");
	exit(0);
}
