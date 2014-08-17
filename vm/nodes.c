#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pt.h"

static unsigned symhash(char* sym) {
	unsigned int hash = 0;
	unsigned c;

	while(c = *sym++) {
		hash = hash*9 ^ c;
	}

	return hash;
}


struct symbol* lookup(char* sym) {
	struct symbol* sp = &symtab[symhash(sym) % NHASH];
	int scount = NHASH;

	while(--scount >=0 ) {
		if(sp->name && !strcmp(sp->name, sym)) {
			return sp;
		}
		if(!sp->name) {
			sp->name = strdup(sym);
			sp->val = 0;
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

	return (struct ast*)a;
}

struct ast* new_cmp(int type, struct ast* l, struct ast* r) {
	struct ast* a = malloc(sizeof(struct ast));
	check_mem(a);

	a->t = '0'+type;
	a->l = l;
	a->r = r;
	return a;
}

struct ast* new_func(int type, struct ast* l) {
	struct func* a = malloc(sizeof(struct func));
	check_mem(a);

	a->nt = 'F';
	a->l = l;
	a->ft = type;
 
	return (struct ast*)a;
}

struct ast* new_call(struct symbol* s, struct ast* l) {
	struct call* a = malloc(sizeof(struct call));
	check_mem(a);

	a->t = 'C';
	a->l = l;
	a->s = s;

	return (struct ast*)a;
}

struct ast* new_asgn(struct symbol* s, struct ast* v) {
	struct symasgn* a = malloc(sizeof(struct symasgn));
	check_mem(a);

	a->t = '=';
	a->s = s;
	a->v = v;
	return (struct ast*)a;
}

struct ast* new_flow(int type, struct ast* cond, struct ast* tl, struct ast* el) {
	struct flow* a = malloc(sizeof(struct flow));
	check_mem(a);

	a->t = type;
	a->cond = cond;
	a->tl = tl;
	a->el = el;
	return (struct ast*)a;
}

struct ast* new_ref(struct symbol* s) {
	struct symref* a = malloc(sizeof(struct symref));
	check_mem(a);

	a->t = 'N';
	a->s = s;
	return (struct ast*)a;
}


void free_tree(struct ast* a) {
	switch(a->t) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case 'L':
			free_tree(a->r);
		case '|':
		case 'M':
		case 'C':
		case 'F':
			free_tree(a->l);
		case 'K':
		case 'N':
			break;
		case '=':
			free(((struct symasgn*)a)->v);
			break;
		case 'I':
		case 'W':
			free(((struct flow*)a)->cond);
			if(((struct flow*)a)->tl) {
				free(((struct flow*)a)->tl);
			}
			if(((struct flow*)a)->el) {
				free(((struct flow*)a)->el);
			}
			break;
		default:
			printf("internal error: free bade node %c\n", a->t);

	}
	free(a);
}


void do_def(struct symbol* name, struct symlist* syms, struct ast* func) {
	if(name->syms) {
		free_symlist(name->syms);
	}
	if(name->func) {
		free_tree(name->func);
	}
	name->syms = syms;
	name->func = func;
}

