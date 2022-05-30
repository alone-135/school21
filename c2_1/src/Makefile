CC = gcc
OBJECTS=s21_string.o \
s21_sprintf.o
SOURSES=s21_string.c \
s21_sprintf.c
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: clean s21_string.a test gcov_report
s21_string.a: s21_string.o
	$(CC) -c $(SOURSES)
	ar rcs s21_string.a $(OBJECTS)
test: s21_string_test.c s21_string.a
	$(CC) $< s21_string.a -lcheck -o s21_string_test
gcov_report: s21_string.a
	@gcc $(GCOVFLAGS) s21_string_test.c -lcheck $(SOURSES) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.* 
check: s21_string.a
	@cppcheck *.h *.c
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@$(CC) s21_string_test.c s21_string.a -lcheck
	@CK_FORK=no leaks --atExit -- ./a.out 
	@rm CPPLINT.cfg
clean:
	@rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./sprintf_o ./sscanf_o ./string_o ./*.dSYM ./s21_string_test ./CPPLINT*
rebuild:
	$(MAKE) clean
	$(MAKE) all