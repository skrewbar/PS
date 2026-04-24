#!/bin/bash

TASK=combo

g++-15 -std=gnu++20 -Wall -O2 -o ${TASK} grader.cpp ${TASK}.cpp
