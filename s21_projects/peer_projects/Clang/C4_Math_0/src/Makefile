CC := gcc
CFLAGS := -std=c11 -ggdb -Wall -Werror -Wextra
TST_LIBS := -lcheck -lm -lpthread
TDIR = tests
EXEDIR = testrun/

all: clean gcov_report

clean: 
	@rm -rf *.a *.o *.gcda *.gcno test gcov_test *.info *.dSYM report alone *cfg

test:  test.o s21_math.a
	@clear
	@$(CC) $(CFLAGS) test.o s21_math.a $(TST_LIBS) -o test
	@./test

test.o: test.c
	@$(CC) $(CFLAGS) -c test.c -o test.o

s21_math.o: s21_math.c
	@$(CC) $(CFLAGS) -c s21_math.c -o s21_math.o

s21_math.a: s21_math.o
	@ar rc s21_math.a s21_math.o
	@ranlib s21_math.a

gcov_test: test.c s21_math.a
	@$(CC) $(CFLAGS) --coverage test.c s21_math.c s21_math.a $(TST_LIBS) -o gcov_test

gcov_test.gcda: gcov_test
	@chmod +x *
	@./gcov_test

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_report: clean gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

report_open: gcov_report
	@open report/index.html

cpplint:
	@cp ../materials/linters/CPPLINT.cfg ./
	@python3 ../materials/linters/cpplint.py *.c *.h
	@rm CPPLINT.cfg

cppcheck:
	@cppcheck *.c *.h

check: cpplint cppcheck

alone: clean s21_math.a alone.o
	@$(CC) $(CFLAGS) alone.o s21_math.a -o alone
	@./alone

alone.o: alone.c
	@$(CC) $(CFLAGS) -c alone.c -o alone.o