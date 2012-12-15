FLAGS = -g -Wall
CFLAGS += $(FLAGS)
LDFLAGS += $(FLAGS)

.PHONY: all
all: hash_test hashtable_test

hash_test: hash_test.o hash.o

hashtable_test: hashtable_test.o hashtable.o hash.o

.PHONY: clean
clean:
	@rm -rf hash_test hashtable_test *.o
