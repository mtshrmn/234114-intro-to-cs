CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -W -O -g -std=c99
ifeq (build,$(firstword $(MAKECMDGOALS)))
  BUILD_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(BUILD_ARGS):;@:)
endif

ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

ifeq (archive,$(firstword $(MAKECMDGOALS)))
  ARCHIVE_ARGS:= $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(ARCHIVE_ARGS):;@:)
endif


test:
	@./test.sh

# example usage `make build hw1q1`
build:
	$(CC) $(CFLAGS) src/$(BUILD_ARGS).c -o bin/$(BUILD_ARGS)

run:
	@./bin/$(RUN_ARGS)

archive:
	zip -j archives/$(ARCHIVE_ARGS) src/$(ARCHIVE_ARGS)q*.c students.txt
