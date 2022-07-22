#!/bin/bash

. ./input.sh
. ./scr03.sh
. ./colors.sh

export args=${#}

arg
check_six_arg ${1}
check_six_arg ${2}
check_six_arg ${3}
check_six_arg ${4}
check_similar_arg ${1} ${2} ${3} ${4}
color ${1} ${2} ${3} ${4}
input
output
