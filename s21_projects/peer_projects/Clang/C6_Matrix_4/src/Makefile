CC := gcc
GFLAGS :=-fprofile-arcs -ftest-coverage
CFLAGS := -Wall -Wextra -Werror
TST_LIBS := -lcheck -lm -lpthread
OS := $(shell uname -s)
ifeq ($(OS), Darwin)
    CFLAGS += -D OS_MAC
else
    CFLAGS += -D OS_LINUX
    TST_LIBS += -lcheck_pic -lrt -lsubunit
endif

all : s21_matrix.a 

project: s21_matrix.a test gcov_report check

s21_matrix.a :
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.c.o
	ar r s21_matrix.a *.o
	ranlib s21_matrix.a

clean :
	rm *.o *.a *.gcno *.gcda *.info test testcoverage 
	rm -rf report
	rm CPPLINT.cfg
	

test : test.c test.o
	$(CC) $(CFLAGS) test.c s21_matrix.a $(TST_LIBS) -o test
	$(CC) $(GFLAGS) test.c s21_matrix.c $(TST_LIBS) -o testcoverage
	./testcoverage
gcov_report : 
	./testcoverage
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@echo
	@echo ===CPPCHECK===
	@echo
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo
	@echo ===STYLE TEST===
	@echo
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@echo
	@echo ===LEAKS TEST===
	@echo
	CK_FORK=no leaks -atExit -- ./testcoverage

rebuild :
	clean
	make