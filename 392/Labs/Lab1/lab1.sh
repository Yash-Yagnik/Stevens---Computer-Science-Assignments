#!/bin/bash
#lab1.sh

validInput=();;

while getopts ":hlp" options; do
    case "{options}" in
        h)
            validInput+=('h');;
        l)
            validInput+=('l');;
        p)
            validInput+=('p');;
        *) 
            echo "illegal option!" >&2;;
            exit 1
esac
done

echo "Flags ${validInput[*]} were entered"

