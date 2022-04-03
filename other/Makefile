CC=gcc 
CFLAGS=-c -Wall -Werror -Wextra
BUILD_DIR=../build/

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests cleantemp

clean:
	rm -rf $(BUILD_DIR)*

cleantemp:
	rm -rf $(BUILD_DIR)*.o

rebuild: clean all

# s21_string.o
s21_string.o: s21_string.c
	$(CC) $(CFLAGS) s21_string.c -o $(BUILD_DIR)s21_string.o

# STRLEN
strlen_tests: strlen_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strlen_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_1

strlen_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRLEN s21_string_test.c -o $(BUILD_DIR)strlen_tests_main.o


# STRCMP
strcmp_tests: strcmp_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strcmp_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_2

strcmp_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRCMP s21_string_test.c -o $(BUILD_DIR)strcmp_tests_main.o


# STRCPY
strcpy_tests: strcpy_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strcpy_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_3

strcpy_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRCPY s21_string_test.c -o $(BUILD_DIR)strcpy_tests_main.o


# STRCAT
strcat_tests: strcat_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strcat_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_4

strcat_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRCAT s21_string_test.c -o $(BUILD_DIR)strcat_tests_main.o


# STRCHR
strchr_tests: strchr_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strchr_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_5

strchr_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRCHR s21_string_test.c -o $(BUILD_DIR)strchr_tests_main.o


# STRSTR
strstr_tests: strstr_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strstr_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_6

strstr_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRSTR s21_string_test.c -o $(BUILD_DIR)strstr_tests_main.o


# STRTOK
strtok_tests: strtok_tests_main.o s21_string.o
	$(CC) $(BUILD_DIR)strtok_tests_main.o $(BUILD_DIR)s21_string.o -o $(BUILD_DIR)Quest_7

strtok_tests_main.o: s21_string_test.c
	$(CC) $(CFLAGS) -DSTRTOK s21_string_test.c -o $(BUILD_DIR)strtok_tests_main.o

