%{
#include <stdio.h>
#include <stdlib.h>
#include "pt.h"
%}

%union {
struct ast* tree;
double val;
}

%token <val> NUMBER
%token EOL

%type <tree> exp factor term

%%
pt_list:
	| pt_list exp EOL {
		printf("= %4.4g\n", eval($2));
		tree_free($2);
		printf("> ");
	}
	| pt_list EOL { printf("> "); }
	;

exp: factor
	| exp '+' factor {$$ = new_ast('+', $1, $3); }
	| exp '-' factor {$$ = new_ast('-', $1, $3); }
	;

factor: term
	| factor '*' term {$$ = new_ast('*', $1, $3); }
	| factor '/' term {$$ = new_ast('*', $1, $3); }
	;

term: NUMBER { $$ = new_num($1); }
	| '|' term { $$ = new_ast('|', $2, NULL); }
	| '(' exp ')' { $$ = $2; }
	| '-' term { $$ = new_ast('M', $2, NULL); }
	;
%%

