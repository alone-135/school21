FLAGS := -Wall -Werror -Wextra

all: build clean

build: s21_cat

clean:
	@rm -rf *.o  *.out exe

open: build
	@./exe

exe: main.o
	@gcc main.o -o exe

main.o: main.c 
	@gcc $(FLAGS) -c main.c -o main.o

s21_cat: main.o
	@gcc main.o lib.c -o s21_cat

lint:
	@cp ../configs/linters/CPPLINT.cfg ./
	@python3 ../configs/linters/cpplint.py --extensions=c *.c *.h 
	@rm CPPLINT.cfg
