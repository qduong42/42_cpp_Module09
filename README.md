# Cpp Module 09 - @42Wolfsburg

## About
CPP Module 09 teaches us to use STL Containers in CPP. In each exercise, we need to evaluate, choose and use different containers most suited for the task.

### Ex00
In this excercise we need to create a BitcoinExchange and convert input values in dollars to bitcoin prices. Here I opted to use std::map. We create a BitcoinExchange class to store our bitcoin exchange data from the given data.csv file. The data.csv file is parsed to store the information in the map. The find member function implemented finds the data parsed from the input file. The main.cpp parses, validates the input file.

### Ex01
In this excercise we need to parse as well as compute a simple single digit RPN(reverse polish notation) expression (handling tokens + - * / only) to the correct result. For this excercise, a stack was decided as a First in Last out method. As operations between the two most recent numbers need to be done, as soon as an operator is encountered. An Example:

RPN 1 5 7 0 + - * evaluates to
1st Operation = 1 5 7 + 0 - *
RPN 1 5 7 - *
2nd Operation = 1 5 - 7 *
RPN 1 -2 *
3rd Operation = 1 * -2
Result = - 2

Invalid RPN Expressions throw errors in the form of thrown and caught exceptions, for example:
"1 +" (1 operator but only 1 number => Not Enough numbers for operation)
"1 3 + 5" (1 operator but 3 numbers to compute => still too many numbers in stack)

## Ex02
In this excercise, we implement Merge-Insertion Sort in CPP. We need to compare the operation time of two different containers. I compared the vector and the deque. I practiced my knowledge with templates and wrote template functions that can be applied to both containers.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- c++ (clang++) v.12.0.0
- compile with -std=c++98 flag.

Those versions are the ones used during development.

### Building the program

1. Download/Clone this repo

        git clone https://github.com/qduong42/42_cpp_Module09
2. `cd` into the exercise directories and run `make`
  for (int i = 00; i <= 02; i++)
{
        cd 42_cpp_Module09/exi
        make
}

### Running the program

After running make, you can run the program following the instructions printed in the terminal by the Makefile.

## Main Project Instructions

- Piscine style C++ Excercises to introduce us to C++ Beginner Concepts.

### Mandatory

- Only code in a C++ way. C functions should be avoided as much as possible.
- NO CODING NORMS!
- No memory leaks
- Must have a Makefile to build the program
- Files to turn in partially given.

### Bonuses
    
## Notes


Enjoy!

