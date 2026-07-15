.PHONY: all

all: main

main: main.c
	gcc -std=c11 -Wall -Wextra -Wpedantic -O3 main.c -o main

run: main
	./main

test: main
	cat test-cases/1.in | ./main > 1.out
	cat test-cases/2.in | ./main > 2.out
	cat test-cases/3.in | ./main > 3.out

	diff 1.out test-cases/1.out
	diff 2.out test-cases/2.out

clean:
	rm -rf main 1.out 2.out 3.out

