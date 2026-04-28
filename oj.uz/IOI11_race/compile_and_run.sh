#!/bin/bash

problem=race

g++-15 -O2 -std=c++20 -o $problem.out grader.cpp $problem.cpp
./$problem.out
