#ifndef SRC_CALCULATION_CUTILS_H_
#define SRC_CALCULATION_CUTILS_H_

#define EPS 1E-6
#define PI 3.14159265358979323846

#include <math.h>
#include <tgmath.h>
#include "../types.h"
#include "../parser/parser.h"
#include "../stack/clstack/clstack.h"

/**
 * @brief                 Runs calculation on given postfix notation equation
 * 
 * @param postfix_tokens  Reverse Polish Notation (RPN) in array of tokens representation
 * @param plength         Length of the postfix entry expression
 * @param x               Dependent input variable
 * @param ans             Pointer to the answer value
 * @return                If equation calculated successfully flag
 */
eflag rcalc(token* postfix_tokens, size_t plength, double* ans, double x);

/**
 * @brief           Runs calculation on arithmetic operations ('+', '-', 'mod', etc.)
 * 
 * @param stk       Pointer to stack object
 * @param operation  Operator to calculate
 * @param x         Dependent input variable
 * @param flag      Pointer to calculation flag
 * @return          None (sets arithmetic operation performed successfully flag)
 */
void acalc(clstack* stk, char operation, double x, eflag* flag);

/**
 * @brief           Runs calculation on arithmetic operations (sin(x), cos, etc.)
 * 
 * @param stk       Pointer to stack object
 * @param operation  Function to calculate
 * @param flag      Pointer to calculation flag
 * @return          None (sets arithmetic operation performed successfully flag)
 */
void fcalc(clstack* stk, char operation, eflag* flag);

/**
 * @brief            Performs given operation and pushes result onto the stack
 * 
 * @param stk        Pointer to the stack object
 * @param flag       Pointer to the calculation flag 
 * @param operation  Operation to perform
 * @return           None (only runs calculation and pushes result onto the stack)
 */
void poperation(clstack* stk, eflag* flag, char operation);

/**
 * @brief      Checks if there are at least two double values in the stack
 * 
 * @param stk  Pointer to the stack object
 * @return     If currect stack state is suitable for calculations
 */
bool vstack(clstack* stk);

#endif  // SRC_CALCULATION_CUTILS_H_