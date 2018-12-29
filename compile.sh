#!/bin/sh
# Author: AlexPowers
# Fri Dec 28 22:09:25 CST 2018
g++ --std=c++11 inconsistent.cpp -o incon.exe
g++ --std=c++11 consistent_slow.cpp -o con_slow.exe
g++ --std=c++11 consistent_fast.cpp -o con_fast.exe
