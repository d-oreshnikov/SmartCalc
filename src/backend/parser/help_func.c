#include "help_func.h"

// help func for compare_operat_prior

int prior(token *tk) {
  int res = 0;

  switch (tk->operation) {
    case '(':
    case ')':
      break;
    case '+':
    case '-':
      res = 2;
      break;
    case '*':
    case '/':
    case MOD:
      res = 3;
      break;
    case '^':
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case SQRT:
    case LOG:
    case LN:
      res = 4;
      break;
  }

  return res;
}

// comparing to operations priority
int compare_operat_prior(token *ltk, token *rtk) {
  return prior(ltk) - prior(rtk);
}

// write given token to a token struct and shifts equation by given index
void operantshift(token *curr_token, char operation, size_t *num_tokens,
                  size_t *curr_quat_idx, size_t shift) {
  curr_token->num = DUMP_DOUBLE;
  curr_token->operation = operation;
  curr_token->is_num = false;
  (*curr_quat_idx) += shift;
  (*num_tokens)++;
}

// checks if given char is func
bool is_function(const char *src, const char *func_name, size_t *shift) {
  size_t length = 0;
  bool flag = true;

  while (flag && func_name[length]) {
    if (src[length] == '\0')
      flag = false;
    else if (src[length] != func_name[length])
      flag = false;
    length++;
  }

  if (flag && src[length] != '(' && strcmp(func_name, "mod")) flag = false;
  *shift = length;

  return flag;
}

// string do decimal, convert token if it's number to double

bool stod(const char *snum, double *num, size_t *curr_eq_idx) {
  while ('0' <= snum[*curr_eq_idx] && snum[*curr_eq_idx] <= '9') {
    *num = *num * 10 + (snum[*curr_eq_idx] - '0');
    (*curr_eq_idx)++;
  }

  int mant_size = 0;
  double mantissa = 0.0;

  if (snum[*curr_eq_idx] == '.') {
    (*curr_eq_idx)++;
    if (snum[*curr_eq_idx] == ' ')
      return true;
    else if (snum[*curr_eq_idx] < '0' || snum[*curr_eq_idx] > '9')
      return false;

    while ('0' <= snum[*curr_eq_idx] && snum[*curr_eq_idx] <= '9') {
      mantissa = mantissa * 10 + (snum[*curr_eq_idx] - '0');
      (*curr_eq_idx)++;
      mant_size++;
    }
  }

  for (; mant_size > 0; mant_size--) mantissa /= 10;

  *num += mantissa;

  return true;
}