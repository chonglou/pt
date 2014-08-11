#include "utils.hh"

void pt::cout(int radix, int val) {
	if(val < 0) {
		std::cout << "-";
		val = -val;
	}
	if(val > radix) {
		pt::cout(radix, val/radix);
		val %= radix;
	}
	std::cout << val;
}

int pt::atoi(int radix, char *s) {
	int v = 0;
	while(*s) {
		v = v*radix + *s++ - '0';
	}
	return v;
}

