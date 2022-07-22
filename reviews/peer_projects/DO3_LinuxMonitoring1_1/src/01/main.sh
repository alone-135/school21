#!/bin/bash
if [[ $1 =~ [0-9] ]] ; then
	echo "error"
elif [ $# == 1 ] ; then
	echo "$1"
else
	echo "error"
fi
