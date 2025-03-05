clear: 
	rm -rf *.o *.a *_test *.gch 

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`

check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

test: 
	@if [ -z "$(wildcard *_test)" ]; then \
		echo "No '_test' found."; \
	else \
		for binary in $(wildcard *_test); do ./$$binary; done; fi
		