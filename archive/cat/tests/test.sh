#!/bin/bash

make clean
make

echo
echo ">>>>> TEST #1 | file: test1.txt <<<<<<"
echo 

#   just read
./s21_cat tests/test1.txt > res1
cat tests/test1.txt > res2
cmp -s res1 res2 && echo "       just read file - SUCCES"
rm res1 res2

#   b flag
./s21_cat -b tests/test1.txt > res1
cat -b tests/test1.txt > res2
cmp -s res1 res2 && echo "           b flag     - SUCCES"
rm res1 res2

#   e flag
./s21_cat -e tests/test1.txt > res1
cat -e tests/test1.txt > res2
cmp -s res1 res2 && echo "           e flag     - SUCCES"
rm res1 res2

#   s flag
./s21_cat -s tests/test1.txt > res1
cat -s tests/test1.txt > res2
cmp -s res1 res2 && echo "           s flag     - SUCCES"
rm res1 res2

#   t flag
./s21_cat -t tests/test1.txt > res1
cat -t tests/test1.txt > res2
cmp -s res1 res2 && echo "           t flag     - SUCCES"
rm res1 res2

#   n flag
./s21_cat -n tests/test1.txt > res1
cat -n tests/test1.txt > res2
cmp -s res1 res2 && echo "           n flag     - SUCCES"
rm res1 res2

echo 

echo
echo ">>>>> TEST #2 | file: test2.txt <<<<<<"
echo 

#   just read
./s21_cat tests/test2.txt > res1
cat tests/test2.txt > res2
cmp -s res1 res2 && echo "       just read file - SUCCES"
rm res1 res2

#   b flag
./s21_cat -b tests/test2.txt > res1
cat -b tests/test2.txt > res2
cmp -s res1 res2 && echo "           b flag     - SUCCES"
rm res1 res2

#   e flag
./s21_cat -e tests/test2.txt > res1
cat -e tests/test2.txt > res2
cmp -s res1 res2 && echo "           e flag     - SUCCES"
rm res1 res2

#   s flag
./s21_cat -s tests/test2.txt > res1
cat -s tests/test2.txt > res2
cmp -s res1 res2 && echo "           s flag     - SUCCES"
rm res1 res2

#   t flag
./s21_cat -t tests/test2.txt > res1
cat -t tests/test2.txt > res2
cmp -s res1 res2 && echo "           t flag     - SUCCES"
rm res1 res2

#   n flag
./s21_cat -n tests/test2.txt > res1
cat -n tests/test2.txt > res2
cmp -s res1 res2 && echo "           n flag     - SUCCES"
rm res1 res2

echo 

echo
echo ">>>>> TEST #3 | file: test3.txt <<<<<<"
echo 

#   just read
./s21_cat tests/test3.txt > res1
cat tests/test3.txt > res2
cmp -s res1 res2 && echo "       just read file - SUCCES"
rm res1 res2

#   b flag
./s21_cat -b tests/test3.txt > res1
cat -b tests/test3.txt > res2
cmp -s res1 res2 && echo "           b flag     - SUCCES"
rm res1 res2

#   e flag
./s21_cat -e tests/test3.txt > res1
cat -e tests/test3.txt > res2
cmp -s res1 res2 && echo "           e flag     - SUCCES"
rm res1 res2

#   s flag
./s21_cat -s tests/test3.txt > res1
cat -s tests/test3.txt > res2
cmp -s res1 res2 && echo "           s flag     - SUCCES"
rm res1 res2

#   t flag
./s21_cat -t tests/test3.txt > res1
cat -t tests/test3.txt > res2
cmp -s res1 res2 && echo "           t flag     - SUCCES"
rm res1 res2

#   n flag
./s21_cat -n tests/test3.txt > res1
cat -n tests/test3.txt > res2
cmp -s res1 res2 && echo "           n flag     - SUCCES"
rm res1 res2

echo 
