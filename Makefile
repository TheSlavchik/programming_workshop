clear:
	rm -rf *.o *.a *_test *.gch 

fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft --dry-run --Werror `find -regex ".+\.[ch]"`

test: l_alloc_test
	./l_alloc_test

l_allocator.a: l_allocator.o
	ar rc l_allocator.a l_allocator.o

l_test.o: l_main.c
	gcc -g -c l_main.c -o l_test.o

l_alloc_test: l_test.o l_allocator.a
	gcc -g -static -o l_alloc_test l_test.o l_allocator.a -lm