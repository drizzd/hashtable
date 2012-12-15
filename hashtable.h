struct item {
	void *value;
	char key[];
};

#define HASHTABLE_SIZE 5

extern struct item *hashtable[HASHTABLE_SIZE];

int hashtable_set(const char *key, void *value);
