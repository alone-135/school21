FLAGS := -Wall -Werror -Wextra

all: clean build

build: s21_math

clean:
	@rm -rf *.o *.a 

s21_math: s21_math.h
	@gcc $(FLAGS) main.c -o exe

lint: all