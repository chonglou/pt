#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "pt.h"

struct ast* new_ast(int type, struct ast* left, struct ast* right) {
	return NULL;
}

struct ast* new_num(double val) {
	return NULL;
}

double eval(struct ast* a) {
	return 0.0;
}

void tree_free(struct ast* a) {

}

void yyerror(char*s, ...) {
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}
