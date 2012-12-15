FLAGS = -g -Wall
CFLAGS += $(FLAGS)
LDFLAGS += $(FLAGS)

hash_test: hash_test.o hash.o

.PHONY: clean
clean:
	@rm -rf hash_test *.o
