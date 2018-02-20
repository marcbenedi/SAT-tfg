#!/bin/bash
for doc in $(seq 0 10000)
do
    for value in $(seq 0 1000)
    do
        export D=$value
        ./main >> resultsRandom/${doc}.csv & (sleep 60; kill $!) &
        echo pene
    done
done
