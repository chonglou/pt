%language "C++"
%defines
%locations

%define api.namespace {pt}
%define parser_class_name {vm_parser}

%{
#include <iostream>
#include "ctx.hh"
#include "utils.hh"
%}

%parse-param { pt::vm_ctx &ctx }
%lex-param { pt::vm_ctx &ctx }

%union {
	int ival;
};


%token <ival> NUMBER
%token ADD SUB MUL DIV ABS
%token OP CP
%token EOL

%type <ival> exp factor term

%{
extern int yylex(pt::vm_parser::semantic_type *yylval, pt::vm_parser::location_type* yylloc, pt::vm_ctx &ctx);
%}

%initial-action {
	@$.begin.filename = @$.end.filename = new std::string("stdin");
}

%%

vmlist:
	| vmlist exp EOL { std::cout << "="; pt::cout(ctx.getradix(), $2); std::cout << "\n> "; }
	| vmlist EOL { std::cout << "> "; }
;

exp: factor
	| exp ADD factor { $$ = $1 + $3; }
	| exp SUB factor { $$ = $1 - $3; }
	| exp ABS factor { $$ = $1 | $3; }
;

factor: term
	| factor MUL term { $$ = $1 * $3; }
	| factor DIV term { if($3 == 0) {
												error(@3, "zero divide");
												YYABORT;
											}
											$$ = $1 / $3; }
;

term: NUMBER
	| ABS term { $$ = $2 >=0 ? $2 : -$2; }
	| OP exp CP { $$ = $2; }
;
%%

int main() {
	pt::vm_ctx ctx(8);
	std::cout << "> ";
	pt::vm_parser parser(ctx);
	int v = parser.parse();
	return v;
}

namespace pt {
	void vm_parser::error(location const &loc, const std::string &s) {
		std::cerr << "error at " << loc << ": " << std::endl;
	}
}
