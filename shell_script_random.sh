#!/bin/bash
for value in $(seq 0 10)
do
    # export D=$value
    ./main >> resultsRandom2/${value}.csv; sleep 2
done
