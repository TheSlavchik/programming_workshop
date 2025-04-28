clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [STACK]

stack_test.o: stack/stack_test.c
	gcc -g -c stack/stack_test.c -o stack_test.o

stack.o: stack/stack.c stack/stack.h
	gcc -g -c stack/stack.c -o stack.o 

stack.a: stack.o
	ar rc stack.a stack.o

stack_test: stack_test.o stack.a
	gcc -g -static -o stack_test stack_test.o stack.a -lm

# [TESTS]

test: stack_test
	./stack_test
