#!/bin/bash

function input {
    START=$(sudo date +'%s%N')
    export number_folders=$(sudo ls -laR $file | grep "^d" | wc -l)
    export number_files=$(sudo ls -laR $file | grep "^-" | wc -l)
    export cfg=$(sudo ls -laR $file | grep .conf | wc -l)
    export txt=$(sudo ls -laR $file | grep .txt | wc -l)
    export executable=$(sudo ls -laR $file | grep "^-........x" | wc -l)
    export log=$(sudo ls -laR $file | grep .log | wc -l)
    export archive=$(($(sudo ls -laR $file | grep .tar | wc -l) + \
    $(sudo ls -laR $file | grep .gz | wc -l) + \
    $(sudo ls -laR $file | grep .zip | wc -l) + \
    $(sudo ls -laR $file | grep .iso | wc -l) + \
    $(sudo ls -laR $file | grep .7z | wc -l) + \
    $(sudo ls -laR $file | grep .arj | wc -l) + \
    $(sudo ls -laR $file | grep .rar | wc -l)))
    export links=$(sudo ls -laR $file | grep "^l" | wc -l)
}

function top_five {
    i=1
    for ((var=1; var<6; var++, i++))
    do
        name=$(sudo du -b $file | sort -nr | head -5 | sed -n "$var"p | awk '{print $2}')
        size=$(sudo du -b $file | sort -nr | head -5 | sed -n "$var"p | awk '{print $1}')
        if ! [ -z "$name" ] && ! [ -z "$size" ] ; then
            echo "$i - $name, $(( $size / 1024 )) Kb"
        fi
    done
}

function top_ten {
    i=1
    for ((var=1; var<11; var++, i++))
    do
        name=$(sudo find $file -type f -printf '%s\t%p\n' | sort -nr | head -10 | sed -n "$var"p | awk '{print $2}')
        size=$(sudo find $file -type f -printf '%s\t%p\n' | sort -nr | head -10 | sed -n "$var"p | awk '{print $1}')
        if ! [ -z "$name" ] && ! [ -z "$size" ] ; then
            echo "$i - $name, $(( $size / 1024 )) Kb, ${name##*.}"
        fi
    done
}

function top_ten1 {
    i=1
    for ((var=1; var<11; var++, i++))
    do
        name=$(sudo find $file -executable -type f -printf '%s\t%p\n' | sort -nr | head -10 | sed -n "$var"p | awk '{print $2}')
        size=$(sudo find $file -executable -type f -printf '%s\t%p\n' | sort -nr | head -10 | sed -n "$var"p | awk '{print $1}')
        hash=$(sudo find $file -executable -type f -printf "%s\t%p\t" -exec bash -c 'md=$(md5sum "$0"); echo ${md:0:32};' {} \; | sort -nr | head -10 | sed -n "$var"p | awk '{print $3}')
        if ! [ -z "$name" ] && ! [ -z "$size" ] && ! [ -z "$hash" ] ; then
            echo "$i - $name, $(( $size / 1024 )) Kb, $hash"
        fi
    done
}

function output {
    echo "Total number of folders (including all nested ones) = ${number_folders}"
    echo "TOP 5 folders of maximum size arranged in descending order (path and size):  "
    top_five
    echo "etc up to 5"
    echo "Total number of files = ${number_files}"
    echo "Number of:"
    echo "Configuration files (with the .conf extension) = ${cfg}"
    echo "Text files = ${txt}"
    echo "Ececutable files = ${executable}"
    echo "Log files (with the extension .log) = ${log}"
    echo "Archive files = ${archive}"
    echo "Symbolic links = ${links}"
    echo "TOP 10 files of maximum size arranged in descending order (path, size and type): "
    top_ten
    echo "etc up to 10"
    echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file): "
    top_ten1
    echo "etc up to 10"
    END=$(sudo date +'%s%N')
    export DIFF=$((( $END - $START ) / 100000000 ))
    echo "Script execution time (in seconds) = $(( $DIFF / 10 )).$(( $DIFF % 10 ))"
}

