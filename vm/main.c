#include <stdio.h>
#include "pt.h"

int main() {
	printf("> ");
	return yyparse();
}
