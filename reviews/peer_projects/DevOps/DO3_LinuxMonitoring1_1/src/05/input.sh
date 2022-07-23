#!/bin/bash
function arg {
    if [[ ${args} -eq 1 ]] ; then
        last=$(echo "${one}" | tail -c 2)
        if [[ ${last} == "/" ]] ; then
            if [[ -d ${one} ]] ; then
                export file=${one}
            else
                echo "error"
                exit 1
            fi
        else
            echo "error"
            exit 1
        fi
    else
        echo "error"
        exit 1
    fi
}
