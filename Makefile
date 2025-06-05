clear:
	rm -rf *.o *.a *_test *.gch 

fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft --dry-run --Werror `find -regex ".+\.[ch]"`

linear_allocator_test.o: linear_allocator/linear_allocator_test.c
	gcc -g -c linear_allocator_test/linear_allocator_test.c -o linear_allocator_test.o

linear_allocator.o: linear_allocator/linear_allocator.c linear_allocator/linear_allocator.h
	gcc -g -c linear_allocator/linear_allocator.c -o linear_allocator.o 

linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -g -static -o linear_allocator_test linear_allocator_test.o linear_allocator.a -lm

test: linear_allocator_test
	./linear_allocator_test