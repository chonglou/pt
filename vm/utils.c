#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "pt.h"

inline void check_mem(void* p) {
	if(!p) {
		yyerror("out of space!");
		exit(0);
	}
}

inline void yyerror(char*s, ...) {
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}
