%{
#include <stdio.h>

int yylex(void);
int yyerror(char* s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%

E: 	T { printf("\nOutput: %d\n", $$); return 0; }

T: 
	T '+' T { $$ = $1 + $3; }
	| T '-' T { $$ = $1 - $3; }
	| T '*' T { $$ = $1 * $3; }
	| T '/' T { $$ = $1 / $3; }
	| '(' T ')' { $$ = $2; }
	| NUMBER { $$ = $1; }

%%

int main() {
	printf("Enter the expression: ");
	yyparse();
}

int yyerror(char* s) {
	printf("\nExpression is invalid!!\n");
}
