FLAGS := -Wall -Werror -Wextra

all: build

build: s21_cat

clean:
	@rm -rf *.o  s21_cat s21_cat.dSYM/

s21_cat: s21_cat.c
	@gcc $(FLAGS) s21_cat.c -o s21_cat
