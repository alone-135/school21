#!/bin/bash
cp ~/alone/github/configs/linters/CPPLINT.cfg ./
echo " "
echo " "
echo ==================================================
echo ------------------! TEST START !-------------------
echo ==================================================
echo " "
python3 ~/alone/github/configs/linters/cpplint.py --extensions=c *.c *.h
echo " "
echo " "
echo ==================== CPP_LINT ====================
echo " "
echo " "
cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
echo ==================== CPP_CHECK ====================
echo " "
echo " "
echo ==================================================
echo -------------------! TEST END !------------------- 
echo ==================================================
echo " "
echo " "
rm CPPLINT.cfg