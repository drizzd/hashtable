#include "hash.h"
#include "hashtable.h"
#include <assert.h>
#include <string.h>

static int hashtable_test_key_at_pos(const char *key, int pos)
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

int main()
{
	char key[] = "aaaaaaaa";
	int i;
	int pos = 0;

	for (i = 0; i < HASHTABLE_SIZE; i++) {
		assert(!find_next_collision(pos, key, strlen(key)));
		assert(!hashtable_set(key, NULL + i));
		assert(hashtable_test_key_at_pos(key, pos + i % HASHTABLE_SIZE));
	}

	assert(!find_next_collision(pos, key, strlen(key)));
	/* table is full */
	assert(hashtable_set(key, NULL) == 1);

	return 0;
}
