NAME = S21_decimal_Project
CC = gcc -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURSES = s21_comparison.c s21_conversion.c s21_math_operations.c s21_rounding.c support.c
OBJECT = s21_comparison.o s21_conversion.o s21_math_operations.o s21_rounding.o support.o
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 TEST_FLAGS =-lcheck
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 TEST_FLAGS =-lcheck -lsubunit -lm -lrt -pthread
endif

all: clean s21_decimal.a

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

s21_decimal.a: s21_comparison.o s21_conversion.o s21_math_operations.o s21_rounding.o
	$(CC) -c $(SOURSES)
	@ar rcs s21_decimal.a $(OBJECT)

test: testest.c s21_decimal.a
	$(CC) $< s21_decimal.a $(TEST_FLAGS) -o test
	@./test

check: s21_decimal.a
	@cppcheck *.h *.c
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../materials/linters/cpplint.py --extension=c *.c
	@rm CPPLINT.cfg
	@$(CC) testest.c s21_decimal.a $(TEST_FLAGS)
	@CK_FORK=no leaks --atExit -- ./a.out

gcov_report: s21_decimal.a
	@gcc $(GCOVFLAGS) testest.c $(TEST_FLAGS) -lcheck $(SOURSES) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*  

clean:
	@rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./decimal_o ./*.dSYM ./test ./CPPLINT*

rebuild:
	$(MAKE) clean
	$(MAKE) all
