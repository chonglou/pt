#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "pt.h"

static unsigned symhash(char* sym) {
	unsigned int hash = 0;
	unsigned c;

	while(c = *sym++) {
		hash = hash*9 ^ c;
	}

	return hash;
}

inline void check_mem(void* p) {
	if(!p) {
		yyerror("out of space!");
		exit(0);
	}
}

struct symbol* lookup(char* key) {
	struct symbol* sp = &symtab[symhash(sym) % NHASH];
	int scount = NHASH;

	while(--scount >=0 ) {
		if(sp->name && !strcmp(sp->name, sym)) {
			return sp;
		}
		if(!sp->name) {
			sp->name = strdup(sym);
			sp->value = 0;
			sp->func = NULL;
			sp->syms = NULL;
			return sp;
		}

		if(++sp >= symtab+NHASH) {
			sp = symtab;
		}
	}

	yyerror("symbol table overflow!\n");
	abort();
}

struct ast* new_ast(int type, struct ast* l, struct ast* r) {
	struct ast* a = malloc(sizeof(struct ast));
	check_mem(a);

	a->t = type;
	a->l = l;
	a->r = r;

	return a;
}

struct ast* new_num(double v) {
	struct numval* a = malloc(sizeof(struct numval));
	check_mem(a);
	a->t = 'K';
	a->v = v;

	return NULL;
}

struct ast* new_cmp(int type, struct ast* l, struct ast* r) {
	return NULL;
}

struct ast* new_func(int type, struct ast* l) {
	return NULL;
}

struct ast* new_call(struct symbol* s, struct ast* l) {
	return NULL;
}

struct ast* new_asgn(struct symbol* s, struct ast* v) {
	return NULL;
}

struct ast* new_flow(int type, struct ast* cond, struct ast* tl, struct ast* el) {
	return NULL;
}

struct ast* new_ref(struct symbol* s) {
	return NULL;
}


struct ast* new_symlist(struct symbol* sym, struct symlist* next) {
	return NULL;
}

double eval(struct ast* a) {
	return 0.0;
}

void tree_free(struct ast* a) {

}

void free_symlist(struct symlist* sl) {
}

void do_def(struct symbol* name, struct symlist* syms, struct ast* func) {
}

void yyerror(char*s, ...) {
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}
