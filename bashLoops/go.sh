#!/bin/bash

if [ $# -eq 0 ]
then
    array=(1 2 3)
else
    array=()
    for arg in "$@"
    do
        if [ -d "$arg" ]
        then
            array+=($arg)
        fi
    done
fi

echo "array = ${array[@]}"

for i in "${array[@]}"
do
    echo $i
done

