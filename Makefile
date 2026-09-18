.PHONY: all

all: compile

dev:
	@gcc src/main.c src/lib/qodon.c src/lib/shell.c -o src/qdn

prod:
	@gcc src/main.c -Wall -Wextra -O3 src/lib/qodon.c src/lib/shell.c -o bin/qdn