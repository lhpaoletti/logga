INCLUDE_DIR ?= include
WARN_OPTS   := -Wall -Wextra -pedantic

logga.o: logga.c $(INCLUDE_DIR)/logga.h
	clang -c -O3 -I$(INCLUDE_DIR) $(WARN_OPTS) -o $@ $<

test: test.o logga.o
	clang $(WARN_OPTS) -o $@ $^

test.o: test.c $(INCLUDE_DIR)/logga.h
	clang -c -I$(INCLUDE_DIR) $(WARN_OPTS) -o $@ $<

.PHONY: clean
clean:
	rm *.o
