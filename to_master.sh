#!/usr/bin/env bash

./clean.sh

rm -rf benchmarks_build benchmarks_files
rm -rf cortadella deliverables experiments readings
rm benchmark_reader.py header_template.h main*

rm -f to_master.sh
