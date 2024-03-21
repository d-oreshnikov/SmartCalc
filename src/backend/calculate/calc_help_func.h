#ifndef SRC_CALCULATE_CALC_HELP_FUNC_H_
#define SRC_CALCULATE_CALC_HELP_FUNC_H_

#define EPS 1E-6
#define PI 3.14159265358979323846

#include <math.h>
#include <tgmath.h>
#include "../types.h"
#include "../parser/parser.h"
#include "../stack/calcstack/cstack.h"

// help functions
// main func to run calculation
eflag rcalc(token *postfix_tokens, size_t posflen, double *ans, double x);
// runs calculation in arithmetic functions
void fcalc(calcstack *stk, char func, eflag *flag);
// make function and pushes result on stack
void pop_func_operation(calcstack *stk, char func, eflag *flag);
// runs calculation in arithmetic operation
void acalc(calcstack *stk, char oper, double x, eflag *flag);
// make operation and pushes result on stack
void pop_arith_operation(calcstack *stk, char oper, eflag *flag);
// cheks if we have two double values in stack
bool goodstack(calcstack *stk);

#endif // SRC_CALCULATE_CALC_HELP_FUNC.H