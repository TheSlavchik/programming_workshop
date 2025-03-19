clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

# [LINKED_LIST]

linked_list_test.o: list/linked_list_test.c
	gcc -g -c list/linked_list_test.c -o linked_list_test.o

linked_list.o: list/linked_list.c list/linked_list.h
	gcc -g -c list/linked_list.c -o linked_list.o 

linked_list.a: linked_list.o
	ar rc linked_list.a linked_list.o

list_test: linked_list_test.o linked_list.a
	gcc -g -static -o list_test linked_list_test.o linked_list.a -lm 

# [TEST]

test: list_test
	./list_test
