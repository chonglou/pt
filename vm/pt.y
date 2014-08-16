%{
#include <stdio.h>
#include <stdlib.h>
#include "pt.h"
%}

%union {
struct ast* a;
double v;
struct symbol* s;
struct symlist *sl;
int fn;
}

%token <v> NUMBER
%token <s> NAME
%token <fn> FUNC
%token EOL

%token IF THEN ELSE WHILE DO DEF

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start pt_list

%%
stmt: IF exp THEN list { $$ = new_flow('I', $2, $4, NULL); }
	| IF exp THEN list ELSE list { $$ = new_flow('I', $2, $4, $6); }
	| WHILE exp DO list { $$ = new_flow('W', $2, $4, NULL); }
	| exp
;

list: { $$ = NULL; }
	| stmt ';' list { if($3 == NULL)
											$$ = $1;
										else
											$$ = new_ast('L', $1, $3);
		}
;

exp: exp CMP exp { $$ = new_cmp($2, $1, $3); }
	| exp '+' exp { $$ = new_ast('+', $1, $3); }
	| exp '-' exp { $$ = new_ast('-', $1, $3); }
	| exp '*' exp { $$ = new_ast('*', $1, $3); }
	| exp '/' exp { $$ = new_ast('/', $1, $3); }
	| '|' exp { $$ = new_ast('|', $2, NULL); }
	| '(' exp ')' { $$ = $2; }
	| '-' exp %prec UMINUS { $$ = new_ast('M', $2, NULL); }
	| NUMBER { $$ = new_num($1); }
	| NAME { $$ = new_ref($1); }
	| NAME '=' exp { $$ = new_asgn($1, $3); }
	| FUNC '(' explist ')' { $$ = new_func($1, $3); }
	| NAME '(' explist ')' { $$ = new_call($1, $3); } 
;

explist: exp
	| exp ',' explist { $$ = new_ast('L', $1, $3); }
;

symlist: NAME { $$ = new_symlist($1, NULL); }
	| NAME ',' symlist { $$ = new_symlist($1, $3); }
;



pt_list:
	| pt_list stmt EOL {
			printf("= %4.4g\n", eval($2));
			free_tree($2);
		}
	| pt_list DEF NAME '(' symlist ')' '=' list EOL {
			do_def($3, $5, $8);
			printf("Defined %s\n>", $3->name);
		}
	| pt_list error EOL { yyerrok; printf("> "); }
	;

%%

