#!/bin/sh
# Author: AlexPowers
# Fri Dec 28 22:10:57 CST 2018
./compile.sh
echo "\nInconsistent increment: "
./incon.exe
./incon.exe
./incon.exe
echo "\n\nConsistent slow: "
time ./con_slow.exe
echo "\n\nConsistent fast: "
time ./con_fast.exe
