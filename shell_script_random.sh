#!/bin/bash
for doc in $(seq 0 10)
do
    for value in $(seq 0 10)
    do
        export D=$value
        ./main >> resultsRandom/${doc}.csv
    done
done
