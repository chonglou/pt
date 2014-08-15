%option noyywrap nodefault yylineno

%{
#include "pt.h"
#include "pt.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"(" |
")" { return yytext[0]; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.val = atof(yytext); return NUMBER; }

\n {return EOL; }

"//".*
[ \t] {}

. { yyerror("Mystery character %c\n", *yytext); }

%%
