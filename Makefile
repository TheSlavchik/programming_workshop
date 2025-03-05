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

# [INTEGRAL]

test2.o: integral/test2.c
	gcc -g -c integral/test2.c -o test2.o

integral.o: integral/integral.c integral/integral.h
	gcc -g -c integral/integral.c -o integral.o 

integral.a: integral.o
	ar rc integral.a integral.o

integral_test: test2.o integral.a
	gcc -g -static -o integral_test test2.o integral.a -lm

# [TESTS]

test: equation_test integral_test
	./equation_test
	./integral_test
# @if [ -z "$(wildcard *_test)" ]; then \
	# 	echo "No '_test' found."; \
	# else \
	# 	for binary in $(wildcard *_test); do ./$$binary; done; fi
