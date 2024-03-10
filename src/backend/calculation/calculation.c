#include "calculation.h"

eflag calculate_equation(char *infix, double x, double *ans) {
    /*
    Description:
        Calculates given expression with Reverse Polish Notation (RPN)

    Args:
        (char*) infix : Infix entry of the expression
        (double) x     : Dependent input variable
        (double*) ans  : Pointer to the answer value

    Returns:
        If input equation calculated successfully flag
    */

    size_t ilength = 0;
    size_t plength = 0;
    token *infix_tokens = tokenize(infix, &ilength);
    token *postfix_tokens = NULL;

    eflag flag = SUCCESS;

    if (infix_tokens) {
        postfix_tokens = gpostfix(infix_tokens, ilength, &plength);
        if (postfix_tokens) {
            flag = rcalc(postfix_tokens, plength, ans, x);
            free(postfix_tokens);
        } else
            flag = INVALID_STACK;
        free(infix_tokens);
    } else
        flag = INVALID_TOKEN;

    return flag;
}
