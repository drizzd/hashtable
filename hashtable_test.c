#include "hash.h"
#include "hashtable.h"
#include <assert.h>
#include <string.h>

int hashtable_test_key_at_pos(const char *key, int pos)
{
	return hashtable[pos] && !strcmp(hashtable[pos]->key, key);
}

static int inc_key(char *key, int n)
{
	int i;

	for (i = n-1; i >= 0; i--) {
		key[i]++;
		if (key[i] <= 'z')
			return 0;
		key[i] = 'a';
	}

	return 1;
}

static int find_next_collision(int h, char *key, int n)
{
	while (!inc_key(key, n))
		if (hash(key) % HASHTABLE_SIZE == h)
			return 0;

	return 1;
}

void init_key(char *key, int n)
{
	int i;
	for (i = 0; i < n; i++)
		key[i] = 'a';
}

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

int main()
{
	char key[9];
	int i;
	int pos = 0;

	init_key(key, ARRAY_SIZE(key));
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		void *unchanged = NULL + 1234;
		void *actual = unchanged;
		void *value = NULL + i;
		assert(!find_next_collision(pos, key, strlen(key)));
		assert(hashtable_get(key, &actual) == 1);
		assert(actual == unchanged);
		assert(!hashtable_set(key, value));
		assert(hashtable_test_key_at_pos(key, pos + i % HASHTABLE_SIZE));
	}

	assert(!find_next_collision(pos, key, strlen(key)));
	/* table is full */
	assert(hashtable_set(key, NULL) == 1);

	init_key(key, ARRAY_SIZE(key));
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		void *expect = NULL + i;
		void *actual;
		assert(!find_next_collision(pos, key, strlen(key)));
		assert(!hashtable_get(key, &actual));
		assert(actual == expect);
	}

	return 0;
}
