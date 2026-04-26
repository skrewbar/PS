#!/bin/bash

problem=molecules

g++-15 -O2 -std=c++20 -o $problem grader.cpp $problem.cpp
