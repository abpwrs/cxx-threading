#!/bin/sh
# Author: AlexPowers
# Fri Dec 28 22:10:57 CST 2018
./recompile.sh
echo "\nInconsistent increment: "
./inconsistent.exe
./inconsistent.exe
./inconsistent.exe
echo "\n\nConsistent slow: "
time ./consistent_slow.exe
echo "\n\nConsistent fast: "
time ./consistent_fast.exe
