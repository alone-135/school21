CC=gcc
CFLAGS=# -Wall -Wextra -Werror -pedantic -std=c11
FLAGS_TEST_LIBS = -lcheck -lm -lpthread
#
SRC=s21_calc.c s21_bonus_calc.c


HEADER=s21_calc.h
NAME=s21_calc.a
OBJ=$(patsubst %.c, %.o, $(SRC))
OS = $(shell uname)

.PHONY: all build static install uninstall rebuild dist test gcov_report clean m

all: build static tests

build:
	$(CC) $(CFLAGS) -c $(SRC)

static:
	ar rc s21_calc.a $(OBJ)
	ranlib s21_calc.a

tests: static
	$(CC) $(CFLAGS) -lcheck  s21_test.c s21_calc.a -o test
	./test

gcov_report: all
	$(CC) $(CFLAGS) --coverage s21_test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html


install:
	make clean
	mkdir build
	cd Qt && qmake && make && make clean && rm Makefile && cd ../ && mv Qt/Qt.app build

uninstall:
	rm -rf build*

dvi:
	open readme.html

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	mv ./build/Qt.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf $(EXECUTABLE)
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf CPPLINT.cfg
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf Archive_calc_v1.0 
	@rm -rf *tgz
	@rm -rf build
	@rm -rf gcov_test

rebuild: clean all

check:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c *.c
	python3 ../materials/linters/cpplint.py --extensions=c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	leaks --atExit -- test

m: build static
	@ $(CC) s21_bonus_calc.c -g $(NAME)
	@./a.out
