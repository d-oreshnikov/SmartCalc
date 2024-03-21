#include "parser.h"

#include "../stack/stack.h"

// make from infix notation to postfix
token *postfix_func(token *infix, size_t infxlen, size_t *pidx) {
  stack stk = {0};

  if (stinit(&stk)) return NULL;

  token *postfix = (token *)calloc(2 * infxlen, sizeof(token));
  *pidx = 0;
  size_t idx = 0;
  token *tmp = NULL;

  while (idx < infxlen) {
    if (infix[idx].is_num) {
      postfix[*pidx].num = infix[idx].num;
      postfix[*pidx].operation = DUMP_CHAR;
      postfix[*pidx].is_num = true;

      (*pidx)++;
      idx++;
    } else if (infix[idx].operation == 'x') {
      postfix[*pidx].operation = infix[idx].operation;
      postfix[*pidx].num = 0.0;
      postfix[*pidx].is_num = false;

      (*pidx)++;
      idx++;
    } else {
      if (infix[idx].operation == '(') {
        eflag flag = spush(&stk, &infix[idx]);
        if (flag) return NULL;
        idx++;
      } else if (infix[idx].operation == ')') {
        tmp = spop(&stk);
        while (tmp->operation != '(') {
          postfix[*pidx].operation = tmp->operation;
          postfix[*pidx].num = DUMP_DOUBLE;
          postfix[*pidx].is_num = false;

          (*pidx)++;
          tmp = spop(&stk);
        }
        idx++;
      } else {
        if (stk.head &&
            compare_operat_prior(stk.head->data, &infix[idx]) >= 0) {
          tmp = spop(&stk);
          postfix[*pidx].operation = tmp->operation;
          postfix[*pidx].num = DUMP_DOUBLE;
          postfix[*pidx].is_num = false;

          (*pidx)++;
        } else {
          spush(&stk, &infix[idx]);
          idx++;
        }
      }
    }
  }

  while (stk.size) {
    tmp = spop(&stk);
    postfix[*pidx].operation = tmp->operation;
    postfix[*pidx].num = DUMP_DOUBLE;
    postfix[*pidx].is_num = false;

    (*pidx)++;
  }

  sdestroy(&stk);

  return postfix;
}

//  tokenize input equtation, makes an array of tokens
token *tokenize(const char *equtation, size_t *num_tokens) {
  token *tokens = (token *)calloc(strlen(equtation) * 2, sizeof(token));
  if (!tokens) return NULL;

  double number = 0.0;   // num
  int cnt_brackets = 0;  // count of brackets
  size_t shift = 0;      // shift of going on string
  size_t idx = 0;        // index of string
  bool flag = true;      // flag
  *num_tokens = 0;       //

  while (flag && equtation[idx]) {
    number = 0.0;
    shift = 0;

    switch (equtation[idx]) {
      case ' ':
        idx++;
        break;
        // sample operants

      case '+':
      case '*':
      case '/':
      case '^':
        operantshift(&(tokens[*num_tokens]), equtation[idx], num_tokens, &idx,
                     1);
        break;

        // oprant mines

      case '-': {
        if (*num_tokens == 0 ||
            (*num_tokens && tokens[*num_tokens - 1].operation == '(') ||
            (idx && equtation[idx - 1] == ' ' && equtation[idx + 1] != ' ')) {
          tokens[*num_tokens].is_num = true;
          tokens[*num_tokens].num = 0.0;
          tokens[*num_tokens].operation = DUMP_CHAR;
          (*num_tokens)++;
        }
        operantshift(&(tokens[*num_tokens]), equtation[idx], num_tokens, &idx,
                     1);
        break;
      }

        // working eith breakets

      case '(': {
        operantshift(&(tokens[*num_tokens]), equtation[idx], num_tokens, &idx,
                     1);
        cnt_brackets++;
        break;
      }

      case ')': {
        operantshift(&(tokens[*num_tokens]), equtation[idx], num_tokens, &idx,
                     1);
        cnt_brackets--;
        break;
      }

        // working with math func

      case 'a': {
        if (is_function(equtation + idx, "asin", &shift)) {
          operantshift(&(tokens[*num_tokens]), ASIN, num_tokens, &idx, shift);
        } else if (is_function(equtation + idx, "acos", &shift)) {
          operantshift(&(tokens[*num_tokens]), ACOS, num_tokens, &idx, shift);
        } else if (is_function(equtation + idx, "atan", &shift)) {
          operantshift(&(tokens[*num_tokens]), ATAN, num_tokens, &idx, shift);
        } else {
          flag = false;
        }
        break;
      }

      case 's': {
        if (is_function(equtation + idx, "sin", &shift)) {
          operantshift(&(tokens[*num_tokens]), SIN, num_tokens, &idx, shift);
        } else if (is_function(equtation + idx, "sqrt", &shift)) {
          operantshift(&(tokens[*num_tokens]), SQRT, num_tokens, &idx, shift);
        } else {
          flag = false;
        }
        break;
      }

      case 'l': {
        if (is_function(equtation + idx, "log", &shift)) {
          operantshift(&(tokens[*num_tokens]), LOG, num_tokens, &idx, shift);
        } else if (is_function(equtation + idx, "ln", &shift)) {
          operantshift(&(tokens[*num_tokens]), LN, num_tokens, &idx, shift);
        } else {
          flag = false;
        }
        break;
      }

      case 'c': {
        if (is_function(equtation + idx, "cos", &shift)) {
          operantshift(&(tokens[*num_tokens]), COS, num_tokens, &idx, shift);
        } else {
          flag = false;
        }
        break;
      }

      case 't': {
        if (is_function(equtation + idx, "tan", &shift)) {
          operantshift(&(tokens[*num_tokens]), TAN, num_tokens, &idx, shift);
        } else {
          flag = false;
        }
        break;
      }
      case 'm': {
        if (is_function(equtation + idx, "mod", &shift)) {
          operantshift(&(tokens[*num_tokens]), MOD, num_tokens, &idx, shift);
        } else {
          flag = false;
        }
        break;
      }
      case 'x': {
        if (*num_tokens && tokens[(*num_tokens) - 1].is_num) {
          tokens[*num_tokens].is_num = false;
          tokens[*num_tokens].num = DUMP_DOUBLE;
          tokens[*num_tokens].operation = '*';
          (*num_tokens)++;
        }
        operantshift(&(tokens[*num_tokens]), equtation[idx], num_tokens, &idx,
                     1);
        break;
      }

      default: {
        if ('0' <= equtation[idx] && equtation[idx] <= '9') {
          if (!stod(equtation, &number, &idx)) {
            flag = false;
          } else {
            tokens[*num_tokens].is_num = true;
            tokens[*num_tokens].num = number;
            tokens[*num_tokens].operation = DUMP_CHAR;
            (*num_tokens)++;
          }
        } else {
          flag = false;
        }
        break;
      }
    }
  }

  if (cnt_brackets || !flag) {
    if (tokens) free(tokens);
    tokens = NULL;
  }

  return tokens;
}
