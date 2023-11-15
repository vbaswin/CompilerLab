%option noyywrap

%{
#include "bi.tab.h"
extern int yylval;
extern int yyerror();
%}

%%

[0-9]		{ return DIGIT; }
[a-zA-Z]	{ return LETTER; }
[\n]		{ return NL; }
[ \t]		{ return yytext[0]; }
.			{ return yytext[0]; }

%%
