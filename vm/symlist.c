#include <stdlib.h>
#include "pt.h"

struct symlist* new_symlist(struct symbol* sym, struct symlist* next) {
	struct symlist* sl = malloc(sizeof(struct symlist));
	check_mem(sl);

	sl->sym = sym;
	sl->next = next;
	return sl;
}


void free_symlist(struct symlist* sl) {
	struct symlist *nsl;
	while(sl) {
		nsl = sl->next;
		free(sl);
		sl = nsl;
	}
}
