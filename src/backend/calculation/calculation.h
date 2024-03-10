#ifndef SRC_CALCULATION_CALCULATION_H_
#define SRC_CALCULATION_CALCULATION_H_

#include "cutils.h"

/**
 * @brief        Calculates given expression with Reverse Polish Notation (RPN) 
 * 
 * @param infix  Infix entry of the expression
 * @param x      Dependent input variable
 * @param ans    Pointer to the answer value
 * @return       If input equation calculated successfully flag
 */
eflag calculate_equation(char* infix, double x, double* ans);

#endif  // SRC_CALCULATION_CALCULATION_H_