#!/bin/bash

function arg {
    if [[ ${args} -ne 0 ]] ; then
        echo "error"
        exit 1
    fi
}
