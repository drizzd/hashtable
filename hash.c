#include "hash.h"

unsigned hash(const char *s)
{
	unsigned x = 0;

	while (*s != '\0') {
		x = 31 * x + *s;
		s++;
	}

	return x;
}
