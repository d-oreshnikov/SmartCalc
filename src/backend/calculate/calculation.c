#include "calculation.h"

// main function that calculate given expression
eflag calculate_equation(char *infix, double x, double *ans) {
  size_t inflen = 0;
  size_t posflen = 0;

  token *infix_tokens = tokenize(infix, &inflen);  // make infix tokens
  token *postfix_tokens = NULL;

  eflag flag = SUCCESS;

  if (infix_tokens) {
    postfix_tokens =
        postfix_func(infix_tokens, inflen, &posflen);  // make postfix tokens
    if (postfix_tokens) {
      flag = rcalc(postfix_tokens, posflen, ans,
                   x);  // calculate expression in postfix tokens
      free(postfix_tokens);
    } else {
      flag = INVALID_STACK;
    }
    free(infix_tokens);
  } else
    flag = INVALID_TOKEN;

  return flag;
}
