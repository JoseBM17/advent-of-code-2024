# Advent of Code 2024

Advent of Code is an annual series of programming challenges that take place during the month of December. 
Each day, a new problem is released, challenging participants to solve it using the programming language of their choice. 
This repository contains my solutions for the Advent of Code 2024, implemented in **C**.


## Prerequisites

To execute this project, you will need:
- A **C compiler** like `gcc`.
- `make` installed on your system.

## How to Compile

To compile the entire project, simply run:
```bash
make
```

This will generate the executables for each day inside the build/ directory, preserving the structure of the src/ folder.

For example:

    src/day_01/day_01.c will produce build/day_01/day_01.

## How to Execute
Run a Specific Day

To execute the solution for a specific day, use the following command:
```
make run DAY=day_01
```
Replace day_01 with the desired day's directory.
Run All Days

To execute all the solutions consecutively:
```
    make run-all
```
### Clean the Project

To remove all compiled files and clean the build/ directory:

make clean
