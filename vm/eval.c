#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pt.h"

static double call_user(struct call* f) {
	struct symbol* fn = f->s; //函数名
	struct symlist *sl; //虚拟参数
	struct ast* args = f->l; //实际参数
	double *oldval, *newval; //参数值
	double v;
	int nargs;
	int i;

	if(!fn->func) {
		yyerror("call to undefined function", fn->name);
		return 0;
	}

	sl = fn->syms;
	for(nargs=0; sl; sl = sl->next) {
		nargs++;
	}

	oldval = (double *)malloc(nargs * sizeof(double));
	check_mem(oldval);
	newval = (double *)malloc(nargs * sizeof(double));
	check_mem(newval);

	for(i=0; i<nargs; i++) {
		if(!args) {
			yyerror("too few args in call to %s", fn->name);
			free(oldval);
			free(newval);
			return 0.0;
		}
		if(args->t == 'L') {
			newval[i] = eval(args->l);
			args = args->r;
		}
		else {
			newval[i] = eval(args);
			args = NULL;
		}
	}

	sl = fn->syms;
	for(i=0; i<nargs; i++) {
		struct symbol*s = sl->sym;
		oldval[i] = s->val;
		s->val = newval[i];
		sl = sl->next;
	}

	free(newval);
	v = eval(fn->func);

	sl=fn->syms;
	for(i=0; i<nargs; i++) {
		struct symbol* s = sl->sym;
		s->val = oldval[i];
		sl = sl->next;
	}
	free(oldval);
	return v;
}

double eval(struct ast* a) {
	double v;
	if(!a) {
		yyerror("internal error, null eval");
		return 0.0;
	}
	switch(a->t) {
		case 'K':
			v = ((struct numval*)a)->v;
			break;
		case 'N':
			v = ((struct symref*)a)->s->val;
			break;
		case '=':
			v = ((struct symasgn*)a)->s->val;
			break;
		case '+':
			v = eval(a->l) + eval(a->r);
			break;
		case '-':
			v = eval(a->l) - eval(a->r);
			break;
		case '*':
			v = eval(a->l) * eval(a->r);
			break;
		case '/':
			v = eval(a->l) / eval(a->r);
			break;
		case '|':
			v = fabs(eval(a->l));
			break;
		case 'M':
			v = -eval(a->l);
			break;
		//比较
		case '1':
			v = (eval(a->l)) > (eval(a->r)) ? 1 : 0;
			break;
		case '2':
			v = (eval(a->l)) < (eval(a->r)) ? 1 : 0;
			break;
		case '3':
			v = (eval(a->l)) != (eval(a->r)) ? 1 : 0;
			break;
		case '4':
			v = (eval(a->l)) == (eval(a->r)) ? 1 : 0;
			break;
		case '5':
			v = (eval(a->l)) >= (eval(a->r)) ? 1 : 0;
			break;
		case '6':
			v = (eval(a->l)) <= (eval(a->r)) ? 1 : 0;
			break;
		//条件
		case 'I':
			if(eval(((struct flow*)a)->cond) == 0) {
				if(((struct flow*)a)->el) {
					v = eval(((struct flow*)a)->el);
				}
				else {
					v = 0.0;
				}
			}
			else {
				if(((struct flow*)a)->tl) {
					v = eval(((struct flow*)a)->tl);
				}
				else {
					v = 0.0;
				}
			}
			break;
		//循环
		case 'W':
			v = 0.0;
			if(((struct flow*)a)->tl) {
				while(eval(((struct flow*)a)->cond) !=0) {
					v = eval(((struct flow*)a)->tl);
				}
			}
			break;
		case 'L':
			eval(a->l);
			v = eval(a->r);
			break;
		case 'F':
			call_buildin((struct func*)a);
			break;
		case 'C':
			call_user((struct call*)a);
			break;
		default:
			printf("internal error: bad node %c\n", a->t);


	}
	return v;
}
