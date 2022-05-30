FLAGS := -Wall -Werror -Wextra

all: build clean

build: exe

clean:
	@rm -rf *.o  *.out

open: build
	@./exe

exe: main.o
	@gcc main.o -o exe

main.o: main.c 
	@gcc $(FLAGS) -c main.c -o main.o

