#!/bin/bash

if [ -n "$1" ]
then
    echo ==================== ! TEST ! ====================
    echo " "
    python3 ../materials/linters/cpplint.py --extensions=c $1
    echo ==================== CPP_LINT ====================
    echo " "
    echo " "
    cppcheck --enable=all --suppress=missingIncludeSystem $1
    echo ==================== CPP_CHECK ====================
    echo " "
    echo " "
    gcc -Wall -Werror -Wextra $1
    echo gcc -Wall -Werror -Wextra $1
    echo ==================== GCC ====================
    echo " "
else 
    echo error
fi