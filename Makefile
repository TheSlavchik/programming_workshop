clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [HASH TABLE]

hash_table_test.o: hash_table/hash_table_test.c
	gcc -g -c hash_table/hash_table_test.c -o hash_table_test.o

hash_table.o: hash_table/hash_table.c hash_table/hash_table.h
	gcc -g -c hash_table/hash_table.c -o hash_table.o

hash_table.a: hash_table.o
	ar rc hash_table.a hash_table.o

hash_table_test: hash_table_test.o hash_table.a pool_allocator.a
	gcc -g -static -o hash_table_test hash_table_test.o hash_table.a pool_allocator.a -lm

# [POOL ALLOCATOR]

pool_allocator_test.o: pool_allocator/pool_allocator_test.c
	gcc -g -c pool_allocator/pool_allocator_test.c -o pool_allocator_test.o

pool_allocator.o: pool_allocator/pool_allocator.c pool_allocator/pool_allocator.h
	gcc -g -c pool_allocator/pool_allocator.c -o pool_allocator.o 

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -static -o pool_allocator_test pool_allocator_test.o pool_allocator.a -lm

# [TEST]

test: pool_allocator_test hash_table_test
	./pool_allocator_test
	./hash_table_test
