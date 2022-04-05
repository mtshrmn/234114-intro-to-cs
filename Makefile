CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -W -O -g -std=c99
ifeq (build,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

test:
	@./test.sh

# example usage `make build hw1q1`
build:
	$(CC) $(CFLAGS) src/$(RUN_ARGS).c -o bin/$(RUN_ARGS)
