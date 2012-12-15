#include "hash.h"
#include <stdio.h>

void pretty(const char *s)
{
	printf("%08x %s\n", hash(s), s);
}

int main()
{
	pretty("This is a very long string "
		"which should be able to fill 32 bits");
	pretty("hello");
	pretty("bob");
	pretty("hello bob");

	pretty("");
	pretty(" ");

	pretty("a");
	pretty("b");
	pretty("c");
	pretty("    a");
	pretty("   a");
	pretty("  a");
	pretty(" a");
	pretty("a");
	pretty("a ");
	pretty("a  ");
	pretty("a   ");
	pretty("a    ");

	return 0;
}
