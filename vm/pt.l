%option noyywrap

%{

#include <cstdlib>
#include "ctx.hh"
#include "pt.tab.hh"

#define YY_DECL int yylex(pt::vm_parser::semantic_type *yylval, pt::vm_parser::location_type *yylloc, pt::vm_ctx &ctx)
#define YY_USER_ACTION yylloc->columns(yyleng);

typedef pt::vm_parser::token token;
extern int myatoi(int radix, char *s);

%}

%%
%{
	yylloc->step();
%}

"+" { return token::ADD; }
"-" { return token::SUB; }
"*" { return token::MUL; }
"/" { return token::DIV; }
"|" { return token::ABS; }
"(" { return token::OP; }
")" { return token::CP; }
[0-9]+ { yylval->ival = myatoi(ctx.getradix(), yytext); return token::NUMBER; }

\n { yylloc->lines(1); return token::EOL; }

"//".* |
[ \t] { yylloc->step(); }

. { printf("Mystery character %c\n", *yytext); }

%%


