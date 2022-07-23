WWW = -Wall -Wextra -Werror -std=c11

all: test gcov_report

s21_matrix.o: s21_matrix.c
	gcc -c $(WWW) s21_matrix.c -o s21_matrix.o

s21_matrix.a: s21_matrix.o s21_matrix.h
	ar rcs s21_matrix.a  s21_matrix.o
	ranlib s21_matrix.a

test: s21_matrix.a
	gcc $(WWW) -lcheck tests.c s21_matrix.a -o test
	./test


gcov_report: gcov_report_build
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info

gcov_report_build:
	gcc $(CFLAGS) --coverage tests.c s21_matrix.c -o gcov_report -lcheck
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html

clean:
	rm -rf *.o s21_matrix.a *.out report gcov_report test *.gcno
