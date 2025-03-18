clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [EQUATION]

test1.o: equation/test1.c
	gcc -g -c equation/test1.c -o test1.o

equation.o: equation/equation.c equation/equation.h
	gcc -g -c equation/equation.c -o equation.o 

equation.a: equation.o
	ar rc equation.a equation.o

equation_test: test1.o equation.a
	gcc -g -static -o equation_test test1.o equation.a -lm

# [TEST]

test: equation_test
	./equation_test
		