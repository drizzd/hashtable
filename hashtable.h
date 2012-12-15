struct item {
	void *value;
	char key[];
};

#define HASHTABLE_SIZE 5

extern struct item *hashtable[HASHTABLE_SIZE];
int hashtable_test_key_at_pos(const char *key, int pos);

int hashtable_set(const char *key, void *value);
int hashtable_get(const char *key, void **value);
