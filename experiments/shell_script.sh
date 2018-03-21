#!/bin/bash
for value in $(seq 0 10000)
do
    export D=$value
    ./main >> results.csv
done
