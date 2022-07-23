#!/bin/bash

function color {
    export default_color
    if [[ -f ./cfg.conf ]] ; then
        default_color=0
    else
        default_color=1
    fi

    if [[ ${default_color} = 0 ]] ; then
        arg_1=$(sed -n '1'p cfg.conf | cut -d "=" -f 2)
        arg_2=$(sed -n '2'p cfg.conf | cut -d "=" -f 2)
        arg_3=$(sed -n '3'p cfg.conf | cut -d "=" -f 2)
        arg_4=$(sed -n '4'p cfg.conf | cut -d "=" -f 2)
    fi

    if [[ ${arg_1} = '' ]] || [[ ${arg_2} = '' ]] || [[ ${arg_3} = '' ]] || [[ ${arg_4} = '' ]] ; then
        default_color=1
    elif [[ ${arg_1} == ${arg_2} ]] || [[ ${arg_3} == ${arg_4} ]] ; then
        echo "Arguments 1 and 2 or 3 and 4 are similar. Please write other arguments."
        exit 1
    elif [[ ${arg_1} -gt 6 ]] || [[ ${arg_1} -lt  1 ]] ; then
        echo "error"
        exit 1
    elif [[ ${arg_2} -gt 6 ]] || [[ ${arg_2} -lt  1 ]] ; then
        echo "error"
        exit 1
    elif [[ ${arg_3} -gt 6 ]] || [[ ${arg_3} -lt  1 ]] ; then
        echo "error"
        exit 1
    elif [[ ${arg_4} -gt 6 ]] || [[ ${arg_4} -lt  1 ]] ; then
        echo "error"
        exit 1
    fi

    if [[ ${default_color} = 0 ]] ; then
        if [[ $arg_1 == 1 ]] ; then
            bg_color=47
            bg_color_name=' (white)'
        elif [[ $arg_1 == 2 ]] ; then
            bg_color=41
            bg_color_name=' (red)'
        elif [[ $arg_1 == 3 ]] ; then
            bg_color=42
            bg_color_name=' (green)'
        elif [[ $arg_1 == 4 ]] ; then
            bg_color=44
            bg_color_name=' (blue)'
        elif [[ $arg_1 == 5 ]] ; then
            bg_color=45
            bg_color_name=' (purple)'
        elif [[ $arg_1 == 6 ]] ; then
            bg_color=40
            bg_color_name=' (black)'
        fi

        if [[ $arg_2 == 1 ]] ; then
            txt_color=37
            txt_color_name=' (white)'
        elif [[ $arg_2 == 2 ]] ; then
            txt_color=31
            txt_color_name=' (red)'
        elif [[ $arg_2 == 3 ]] ; then
            txt_color=32
            txt_color_name=' (green)'
        elif [[ $arg_2 == 4 ]] ; then
            txt_color=34
            txt_color_name=' (blue)'
        elif [[ $arg_2 == 5 ]] ; then
            txt_color=35
            txt_color_name=' (purple)'
        elif [[ $arg_2 == 6 ]] ; then
            txt_color=30
            txt_color_name=' (black)'
        fi

        if [[ $arg_3 == 1 ]] ; then
            bg_color1=47
            bg_color1_name=' (white)'
        elif [[ $arg_3 == 2 ]] ; then
            bg_color1=41
            bg_color1_name=' (red)'
        elif [[ $arg_3 == 3 ]] ; then
            bg_color1=42
            bg_color1_name=' (green)'
        elif [[ $arg_3 == 4 ]] ; then
            bg_color1=44
            bg_color1_name=' (blue)'
        elif [[ $arg_3 == 5 ]] ; then
            bg_color1=45
            bg_color1_name=' (purple)'
        elif [[ $arg_3 == 6 ]] ; then
            bg_color1=40
            bg_color1_name=' (black)'
        fi

        if [[ $arg_4 == 1 ]] ; then
            txt_color1=37
            txt_color1_name=' (white)'
        elif [[ $arg_4 == 2 ]] ; then
            txt_color1=31
            txt_color1_name=' (red)'
        elif [[ $arg_4 == 3 ]] ; then
            txt_color1=32
            txt_color1_name=' (green)'
        elif [[ $arg_4 == 4 ]] ; then
            txt_color1=34
            txt_color1_name=' (blue)'
        elif [[ $arg_4 == 5 ]] ; then
            txt_color1=35
            txt_color1_name=' (purple)'
        elif [[ $arg_4 == 6 ]] ; then
            txt_color1=30
            txt_color1_name=' (black)'
        fi
    else
        bg_color=40
        bg_color_name=' (black)'
        txt_color=37
        txt_color_name=' (white)'
        bg_color1=41
        bg_color1_name=' (red)'
        txt_color1=34
        txt_color1_name=' (blue)'
    fi

    export color_input="\0033["${txt_color}";"${bg_color}"m"
    export color_output="\0033["${txt_color1}";"${bg_color1}"m"
    export clear="\0033[0m"
}
