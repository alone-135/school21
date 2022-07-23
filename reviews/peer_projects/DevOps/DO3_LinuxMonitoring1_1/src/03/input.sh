#!/bin/bash

function arg {
    if [[ ${args} -ne 4 ]] ; then
        echo "error"
        exit 1
    fi
}

function check_six_arg {
    if [[ $1 -gt 6 ]] || [[ $1 -lt  1 ]] ; then
        echo "error"
        exit 1
    fi
}

function check_similar_arg {
        if [[ ${1} = ${2} ]] || [[ ${3} = ${4} ]] ; then
            while [[ ${1} = ${2} ]] || [[ ${3} = ${4} ]]
            do
                echo "Arguments 1 and 2 or 3 and 4 are similar. Please run the script again."
		exit 1
            done
        fi
}
