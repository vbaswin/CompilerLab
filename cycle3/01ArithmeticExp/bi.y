%{
#include <stdio.h>

int yylex(void);
void yyerror(char* s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%

E: 	T { printf("\nValid Arithmetic Expression!!\n"); return 0; }

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

void yyerror(char* s) {
	printf("\nExpression is invalid!!\n");
}
