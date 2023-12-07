%{
#include <stdio.h>
int yylex(void);
void yyerror(char* s);

extern FILE *yyin;
%}

%token NUMBER NL

%left '+' '-'
%left '*' '/'

%%

E: T NL	{printf("\nOutput: %d\n", $$); return 0;}

T:	T '+' T 	{$$ = $1 + $3}
	| T '-' T	{$$ = $1 - $3}
	| T '*' T	{$$ = $1 * $3}
	| T '/' T	{$$ = $1 / $3}
	| '(' T ')'	{$$ = $2}
	| NUMBER 	{$$ = $1}

%%

int main() {
	printf("Enter expression: ");
	/* FILE *fp = fopen("input.txt","r"); */
	/* yyin = fp; */
	/* yylex(); */
	yyparse();
	/* fclose(fp); */
}
void yyerror(char* s) {
	printf("\nExpression is invalid!!\n");
}

