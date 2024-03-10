# SmartCallc

Calculator on C/C++

## Contents

0. [Information](#information)
1. [Arithmetic operators](#arithmetic-operators)
2. [Functions](#functions)

## Information

In this project I implemented an extended version of the usual calculator, which can be found in the standard applications of each operating system in the C programming language using structured programming. In addition to basic arithmetic operations such as add/subtract and multiply/divide, supplemented the calculator with the ability to calculate arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.).

Besides calculating expressions, it supports the use of the _x_ variable and the graphing of the corresponding function.

- The program was developed in C language of C11 standard using gcc compiler, using additional QT libraries and modules
- The program code located in the src folder
- The program built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests, gcov_report.
- The program was developed according to the principles of structured programming
- The program code written in Google style
- Full coverage of modules related to calculating expressions with unit-tests using the Check library
- GUI implementation, based on any GUI library with API for C89/C99/C11 (Qt)
- Both integers and real numbers with a dot can be input into the program. You can optionally provide the input of numbers in exponential notation
- The calculation done after you complete entering the calculating expression and press the `=` symbol.
- Calculating arbitrary bracketed arithmetic expressions in infix notation
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable _x_ as a number
- Plotting a graph of a function given by an expression in infix notation with the variable _x_ (with coordinate axes, mark of the used scale and an adaptive grid)
- Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000
- To plot a graph of a function it is necessary to additionally specify the displayed domain and codomain
- Verifiable accuracy of the fractional part is at least to 7 decimal places
- Users must be able to enter up to 255 characters
- Bracketed arithmetic expressions in infix notation must support the following arithmetic operations and mathematical functions:
    
## Arithmetic operators

| Operator name | Infix notation <br /> (Classic) | Prefix notation <br /> (Polish notation) |  Postfix notation <br /> (Reverse Polish notation) |
| --------- | ------ | ------ | ------ |
| Brackets | (a + b) | (+ a b) | a b + |
| Addition | a + b | + a b | a b + |
| Subtraction | a - b | - a b | a b - |
| Multiplication | a * b | * a b | a b * |
| Division | a / b | / a b | a b \ |
| Power | a ^ b | ^ a b | a b ^ |
| Modulus | a mod b | mod a b | a b mod |
| Unary plus | +a | +a | a+ |
| Unary minus | -a | -a | a- |


## Functions
  
| Function description | Function |
| ------ | ------ |
| Computes cosine | cos(x) |
| Computes sine | sin(x) |
| Computes tangent | tan(x) |
| Computes arc cosine | acos(x) |
| Computes arc sine | asin(x) |
| Computes arc tangent | atan(x) |
| Computes square root | sqrt(x) |
| Computes natural logarithm | ln(x) |
| Computes common logarithm | log(x) |