FLAGS := -Wall -Werror -Wextra

all: build open

build: clean exe

clean:
	rm -rf *.o exe

open: build
	./exe

exe: main.o
	gcc main.o -o exe

main.o: main.c 
	gcc $(FLAGS) -c main.c -o main.o

