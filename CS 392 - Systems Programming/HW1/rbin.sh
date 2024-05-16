#!/bin/bash

# *******************************************************************************
#  Author  : Yash Yagnik
#  Date    : 2/5/2024
#  Description: CS392 - Homework 1
#  Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
# ******************************************************************************

# TODO: Fill the header above, and then complete rbin.sh below

readonly recycleDirectory="$HOME/.recycle" 
countFlags=0;

if [ ! -d "$recycleDirectory" ]; then
    mkdir "$recycleDirectory" 
fi
function usageMessage {
    cat << EOF
Usage: rbin.sh [-hlp] [list of files]
   -h: Display this help;
   -l: List files in the recycle bin;
   -p: Empty all files in the recycle bin;
   [list of files] with no other flags,
        these files will be moved to the
        recycle bin.
EOF
}

if [ "$#" = 1 ]; then
while getopts ":hlp" options; do
    case $options in
        h)
            usageMessage
            ((countFlags++))
            exit 0;;
        l)
            ls -lAF $recycleDirectory
            ((countFlags++))
            exit 0;;
        p)
            rm -rf ${recycleDirectory}/*
            rm -rf ${recycleDirectory}/.* 2>/dev/null
            ((countFlags++))
            exit 0;;

        *) 
            echo "Error: Unknown option '"$1"'." >&2
            usageMessage
            exit 1;;
esac
done
for pancakes in $@; do
        if [ -e $pancakes ]; then
            mv $pancakes $recycleDirectory
        else 
            echo "Warning: '$pancakes' not found." >&2
        fi
    done

elif [ "$#" -gt 1 ]; then
while getopts ":hlp" options; do
    case $options in
        h)
            ((countFlags++));;
        
        l)
            ((countFlags++));;
        p)
            ((countFlags++));;
        *) 
            echo "Error: Unknown option '-${OPTARG}'." >&2
            usageMessage
            exit 1;;
esac
done
if [ $countFlags -gt 0 ]; then
    echo "Error: Too many options enabled." >&2
    usageMessage
    exit 1
else
    for pancakes in $@; do
        if [ -e $pancakes ]; then
            mv $pancakes $recycleDirectory
        else 
            echo "Warning: '$pancakes' not found." >&2
        fi
    done
fi

else
usageMessage
exit 0
fi

