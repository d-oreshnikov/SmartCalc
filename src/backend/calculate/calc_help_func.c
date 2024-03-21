#include "calc_help_func.h"

// runs calculation of given postfix notation equation
eflag rcalc(token *postfix_tokens, size_t posflen, double *ans, double x) {
  calcstack stk = {0};
  calcstinit(&stk);

  eflag flag = SUCCESS;

  for (size_t i = 0; i < posflen && flag == SUCCESS; i++) {
    if (postfix_tokens[i].is_num) {
      // if we have double push it on stack
      calcspush(&stk, postfix_tokens[i].num);
    } else {
      // if we have function do it
      fcalc(&stk, postfix_tokens[i].operation, &flag);
      // if we have operation do it
      acalc(&stk, postfix_tokens[i].operation, x, &flag);
    }
  }

  if (stk.size != 1)
    flag = FAILED_CALC;
  else {
    // takes our result
    *ans = calcspop(&stk);
    if (fabs(*ans) < EPS) *ans = 0;
  }
  calcsdestroy(&stk);

  return flag;
}

// runs calculation in aritmetic operation
void acalc(calcstack *stk, char oper, double x, eflag *flag) {
  switch (oper) {
    case 'x':
      calcspush(stk, x);
      break;

    case '+':
      pop_arith_operation(stk, oper, flag);
      break;

    case '-':
      pop_arith_operation(stk, oper, flag);
      break;

    case '*':
      pop_arith_operation(stk, oper, flag);
      break;

    case '/':
      pop_arith_operation(stk, oper, flag);
      break;

    case 'm':
      pop_arith_operation(stk, oper, flag);
      break;

    case '^':
      pop_arith_operation(stk, oper, flag);
      break;
  }
}

// make operation and pushes result on stack
void pop_arith_operation(calcstack *stk, char oper, eflag *flag) {
  double top = 0.0;

  switch (oper) {
    case '+':
      if (goodstack(stk))
        calcspush(stk, calcspop(stk) + calcspop(stk));
      else
        *flag = INVALID_STACK;
      break;

    case '*':
      if (goodstack(stk))
        calcspush(stk, calcspop(stk) * calcspop(stk));
      else
        *flag = INVALID_STACK;
      break;

    case '-':
      if (goodstack(stk)) {
        top = calcspop(stk);
        calcspush(stk, calcspop(stk) - top);
      } else
        *flag = INVALID_STACK;
      break;

    case '/':
      if (goodstack(stk)) {
        top = calcspop(stk);
        if (fabs(top) >= EPS)
          calcspush(stk, calcspop(stk) / top);
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;

    case 'm':
      if (goodstack(stk)) {
        top = calcspop(stk);
        if (fabs(top) >= EPS)
          calcspush(stk, fmod(calcspop(stk), top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;

    case '^':
      if (goodstack(stk)) {
        top = calcspop(stk);
        calcspush(stk, powl(calcspop(stk), top));
      }
      break;
  }
}

// cheks if we have two double values in stack
bool goodstack(calcstack *stk) { return stk->head && stk->head->next; }

// runs calculation in arithmetic functions
void fcalc(calcstack *stk, char func, eflag *flag) {
  switch (func) {
    case SIN:
      pop_func_operation(stk, func, flag);
      break;

    case COS:
      pop_func_operation(stk, func, flag);
      break;

    case TAN:
      pop_func_operation(stk, func, flag);
      break;

    case ASIN:
      pop_func_operation(stk, func, flag);
      break;

    case ACOS:
      pop_func_operation(stk, func, flag);
      break;

    case ATAN:
      pop_func_operation(stk, func, flag);
      break;

    case SQRT:
      pop_func_operation(stk, func, flag);
      break;

    case LOG:
      pop_func_operation(stk, func, flag);
      break;

    case LN:
      pop_func_operation(stk, func, flag);
      break;
  }
}

// make operation and pushes result on stack
void pop_func_operation(calcstack *stk, char func, eflag *flag) {
  double top = 0.0;

  switch (func) {
    case SIN: {
      if (stk->head)
        calcspush(stk, sin(calcspop(stk)));
      else
        *flag = INVALID_TOKEN;
      break;
    }
    case COS: {
      if (stk->head)
        calcspush(stk, cos(calcspop(stk)));
      else
        *flag = INVALID_TOKEN;
      break;
    }
    case TAN: {
      if (stk->head)
        calcspush(stk, tan(calcspop(stk)));
      else
        *flag = INVALID_TOKEN;
      break;
    }
    case ASIN: {
      if (stk->head)
        calcspush(stk, asin(calcspop(stk)));
      else
        *flag = INVALID_TOKEN;
      break;
    }
    case ACOS: {
      if (stk->head)
        calcspush(stk, acos(calcspop(stk)));
      else
        *flag = INVALID_TOKEN;
      break;
    }
    case ATAN: {
      if (stk->head)
        calcspush(stk, atan(calcspop(stk)));
      else
        *flag = INVALID_TOKEN;
      break;
    }
    case SQRT: {
      if (stk->head) {
        top = calcspop(stk);
        if (top >= 0)
          calcspush(stk, sqrt(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_TOKEN;
      break;
    }
    case LOG: {
      if (stk->head) {
        top = calcspop(stk);
        if (top > EPS)
          calcspush(stk, log10(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_TOKEN;
      break;
    }

    case LN: {
      if (stk->head) {
        top = calcspop(stk);
        if (top > EPS)
          calcspush(stk, log(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_TOKEN;
      break;
    }
  }
}
