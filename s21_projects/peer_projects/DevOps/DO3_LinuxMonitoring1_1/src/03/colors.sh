#!/bin/bash

function color {
    if [[ $1 == 1 ]] ; then
        bg_color=47
    elif [[ $1 == 2 ]] ; then
        bg_color=41
    elif [[ $1 == 3 ]] ; then
        bg_color=42
    elif [[ $1 == 4 ]] ; then
        bg_color=44
    elif [[ $1 == 5 ]] ; then
        bg_color=45
    elif [[ $1 == 6 ]]; then
        bg_color=40
    fi

    if [[ $2 == 1 ]] ; then
        txt_color=37
    elif [[ $2 == 2 ]] ; then
        txt_color=31
    elif [[ $2 == 3 ]] ; then
        txt_color=32
    elif [[ $2 == 4 ]] ; then
        txt_color=34
    elif [[ $2 == 5 ]] ; then
        txt_color=35
    elif [[ $2 == 6 ]] ; then
        txt_color=30
    fi

    if [[ $3 == 1 ]] ; then
        bg_color1=47
    elif [[ $3 == 2 ]] ; then
        bg_color1=41
    elif [[ $3 == 3 ]] ; then
        bg_color1=42
    elif [[ $3 == 4 ]] ; then
        bg_color1=44
    elif [[ $3 == 5 ]] ; then
        bg_color1=45
    elif [[ $3 == 6 ]] ; then
        bg_color1=40
    fi

    if [[ $4 == 1 ]] ; then
        txt_color1=37
    elif [[ $4 == 2 ]] ; then
        txt_color1=31
    elif [[ $4 == 3 ]] ; then
        txt_color1=32
    elif [[ $4 == 4 ]] ; then
        txt_color1=34
    elif [[ $4 == 5 ]] ; then
        txt_color1=35
    elif [[ $4 == 6 ]] ; then
        txt_color1=30
    fi

    export color_input="\0033["${txt_color}";"${bg_color}"m"
    export color_output="\0033["${txt_color1}";"${bg_color1}"m"
    export clear="\0033[0m"
}
