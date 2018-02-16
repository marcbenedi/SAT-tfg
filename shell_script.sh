#!/bin/bash
for value in $(seq 0 10000)
do
    export D=$value
    echo $value
    touch main.cpp
    make main
    ./main >> results.out
done
