clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [INTEGRAL]

test2.o: integral/test2.c
	gcc -g -c integral/test2.c -o test2.o

integral.o: integral/integral.c integral/integral.h
	gcc -g -c integral/integral.c -o integral.o 

integral.a: integral.o
	ar rc integral.a integral.o

integral_test: test2.o integral.a
	gcc -g -static -o integral_test test2.o integral.a -lm

# [TEST]

test: integral_test
	./integral_test
