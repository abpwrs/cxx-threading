#!/bin/sh
# Author: AlexPowers
# Fri Dec 28 22:09:25 CST 2018
for cpp_file in ./*.cpp; do
    filename=$(basename -- "${cpp_file}")
    filename="${filename%.*}"
    g++ --std=c++11 ${cpp_file} -o "${filename}.exe"
done
