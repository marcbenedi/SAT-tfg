#!/usr/bin/env bash

#Google test
rm -rf googletest
unzip googletest.zip
cd googletest/googletest/make
make
mv gtest_main.a libgtest_main.a
cd ..
cd ..
cd ..

#CUDD
rm -rf cudd-3.0.0
unzip cudd-3.0.0.zip
cd cudd-3.0.0
./configure --enable-obj
make
make check
cd ..

#PBlib
rm -rf pblib
unzip pblib.zip
cd pblib
cmake .
make setup
cd ..


#Requirements
#picosat
#cmake

rm -rf test_build source_build
mkdir test_build source_build

make tfg
make tests
