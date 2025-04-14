clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [INTEGRAL]

pool_allocator_test.o: pool_allocator/pool_allocator_test.c
	gcc -g -c pool_allocator/pool_allocator_test.c -o pool_allocator_test.o

pool_allocator.o: pool_allocator/pool_allocator.c pool_allocator/pool_allocator.h
	gcc -g -c pool_allocator/pool_allocator.c -o pool_allocator.o 

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -static -o pool_allocator_test pool_allocator_test.o pool_allocator.a -lm

# [TEST]

test: pool_allocator_test
	./pool_allocator_test
