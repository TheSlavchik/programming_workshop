clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror


pool.o: pool_allocator/pool_allocator.c
	gcc -g -c pool_allocator/pool_allocator.c -o pool.o

pool: pool.o
	gcc -g -o pool pool.o -lm 

test: pool
	./pool
		