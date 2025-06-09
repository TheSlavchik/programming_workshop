clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [POOL ALLOCATOR]

pool_allocator_test.o: pool_allocator/pool_allocator_test.c
	gcc -g -I. -c pool_allocator/pool_allocator_test.c -o pool_allocator_test.o

pool_allocator.o: pool_allocator/pool_allocator.c pool_allocator/pool_allocator.h
	gcc -g -I. -c pool_allocator/pool_allocator.c -o pool_allocator.o 

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -o pool_allocator_test pool_allocator_test.o pool_allocator.a -lm

#[GARBAGE COLLECTOR]

garbage_collector_test.o: garbage_collector/garbage_collector_test.c garbage_collector/garbage_collector.h
	gcc -g -I. -c garbage_collector/garbage_collector_test.c -o garbage_collector_test.o

garbage_collector.o: garbage_collector/garbage_collector.c garbage_collector/garbage_collector.h pool_allocator/pool_allocator.h
	gcc -g -I. -c garbage_collector/garbage_collector.c -o garbage_collector.o 

garbage_collector.a: garbage_collector.o
	ar rc garbage_collector.a garbage_collector.o

garbage_collector_test: garbage_collector_test.o garbage_collector.a pool_allocator.a
	gcc -g -o garbage_collector_test garbage_collector_test.o garbage_collector.a pool_allocator.a -lm

# [TEST]

test: pool_allocator_test garbage_collector_test
	./pool_allocator_test
	./garbage_collector_test
	valgrind --leak-check=full --track-origins=yes ./pool_allocator_test
	valgrind --leak-check=full --track-origins=yes ./garbage_collector_test
