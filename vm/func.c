#include <stdio.h>
#include <math.h>
#include "pt.h"

inline double call_buildin(struct func* f) {
	int ft = f->ft;
	double v = eval(f->l);

	switch(ft) {
		case B_sqrt:
			return sqrt(v);
		case B_exp:
			return exp(v);
		case B_log:
			return log(v);
		case B_print:
			printf("= %4.4g\n", v);
			return v;
		default:
			yyerror("Unknown built-in function %d", ft);
			return 0.0;
	}
	return 0.0;
}
