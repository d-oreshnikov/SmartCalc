#include "parser.h"
#include "../stack/stack.h"

token *gpostfix(token *infix, size_t ilength, size_t *plength) {
    /*
    Description:
        Converts infix notation (1 + 2) into postfix notation (1 2 +)

    Args:
        (token*) infix    : Infix (source) notation in array of tokens
    representation (size_t) ilength  : Length of the infix notation (size_t*)
    plenght : Pointer to the length of the postfix notation

    Returns:
        Postfix notation in array of tokens representation
    */

    stack stk = {0};
    if (_sinit(&stk)) return NULL;
    token *postfix = (token *)calloc(2 * ilength, sizeof(token));
    *plength = 0;
    size_t idx = 0;
    token *tmp = NULL;

    while (idx < ilength) {
        if (infix[idx].is_num) {
            postfix[*plength].num_var = infix[idx].num_var;
            postfix[*plength].operation = DUMMY_CHAR;
            postfix[*plength].is_num = true;

            (*plength)++;
            idx++;
        } else if (infix[idx].operation == 'x') {
            postfix[*plength].operation = infix[idx].operation;
            postfix[*plength].num_var = 0.0;
            postfix[*plength].is_num = false;

            (*plength)++;
            idx++;
        } else {
            if (infix[idx].operation == '(') {
                eflag flag = _spush(&stk, &infix[idx]);
                if (flag) return NULL;
                idx++;
            } else if (infix[idx].operation == ')') {
                tmp = _spop(&stk);
                while (tmp->operation != '(') {
                    postfix[*plength].operation = tmp->operation;
                    postfix[*plength].num_var = DUMMY_DOUBLE;
                    postfix[*plength].is_num = false;

                    (*plength)++;
                    tmp = _spop(&stk);
                }
                idx++;
            } else {
                if (stk.head && opriority(stk.head->data, &infix[idx]) >= 0) {
                    tmp = _spop(&stk);
                    postfix[*plength].operation = tmp->operation;
                    postfix[*plength].num_var = DUMMY_DOUBLE;
                    postfix[*plength].is_num = false;

                    (*plength)++;
                } else {
                    _spush(&stk, &infix[idx]);
                    idx++;
                }
            }
        }
    }

    while (stk.size) {
        tmp = _spop(&stk);
        postfix[*plength].operation = tmp->operation;
        postfix[*plength].num_var = DUMMY_DOUBLE;
        postfix[*plength].is_num = false;

        (*plength)++;
    }

    _sdestroy(&stk);

    return postfix;
}

token *tokenize(const char *equation, size_t *num_tokens) {
    /*
    Description:
        Tokenizes input equation (creates array of tokens)

    Args:
        (const char*) equation : Source equation (user input)
        (int*) num_tokens           : Pointer to tokens length

    Returns:
        List of tokens representing source equation (sin(x) -> s(x))
    */

    token *tokens = (token *)calloc(strlen(equation) * 2, sizeof(token));
    if (!tokens) return NULL;

    double number = 0.0;
    int cnt_brackets = 0;
    size_t shift = 0;
    size_t idx = 0;
    bool flag = true;
    *num_tokens = 0;

    while (flag && equation[idx]) {
        number = 0.0;
        shift = 0;

        switch (equation[idx]) {
            case ' ':
                idx++;
                break;

            case '+':
            case '*':
            case '/':
            case '^':
                oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
                break;

            case '-': {
                if (*num_tokens == 0 || (*num_tokens && tokens[*num_tokens - 1].operation == '(') ||
                    (idx && equation[idx - 1] == ' ' && equation[idx + 1] != ' ')) {
                    tokens[*num_tokens].is_num = true;
                    tokens[*num_tokens].num_var = 0.0;
                    tokens[*num_tokens].operation = DUMMY_CHAR;
                    (*num_tokens)++;
                }
                oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
                break;
            }

            case '(':
                oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
                cnt_brackets++;
                break;

            case ')':
                oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
                cnt_brackets--;
                break;

            case 'a': {
                if (is_function(equation + idx, "asin", &shift)) {
                    oshift(&(tokens[*num_tokens]), ASIN, num_tokens, &idx, shift);
                } else if (is_function(equation + idx, "acos", &shift)) {
                    oshift(&(tokens[*num_tokens]), ACOS, num_tokens, &idx, shift);
                } else if (is_function(equation + idx, "atan", &shift)) {
                    oshift(&(tokens[*num_tokens]), ATAN, num_tokens, &idx, shift);
                } else
                    flag = false;
                break;
            }

            case 's': {
                if (is_function(equation + idx, "sin", &shift)) {
                    oshift(&(tokens[*num_tokens]), SIN, num_tokens, &idx, shift);
                } else if (is_function(equation + idx, "sqrt", &shift)) {
                    oshift(&(tokens[*num_tokens]), SQRT, num_tokens, &idx, shift);
                } else
                    flag = false;
                break;
            }

            case 'l': {
                if (is_function(equation + idx, "log", &shift)) {
                    oshift(&(tokens[*num_tokens]), LOG, num_tokens, &idx, shift);
                } else if (is_function(equation + idx, "ln", &shift)) {
                    oshift(&(tokens[*num_tokens]), LN, num_tokens, &idx, shift);
                } else
                    flag = false;
                break;
            }

            case 'c': {
                if (is_function(equation + idx, "cos", &shift)) {
                    oshift(&(tokens[*num_tokens]), COS, num_tokens, &idx, shift);
                } else
                    flag = false;
                break;
            }

            case 't': {
                if (is_function(equation + idx, "tan", &shift)) {
                    oshift(&(tokens[*num_tokens]), TAN, num_tokens, &idx, shift);
                } else
                    flag = false;
                break;
            }

            case 'm': {
                if (is_function(equation + idx, "mod", &shift)) {
                    oshift(&(tokens[*num_tokens]), MOD, num_tokens, &idx, shift);
                } else
                    flag = false;
                break;
            }

            case 'x': {
                if (*num_tokens && tokens[(*num_tokens) - 1].is_num) {
                    tokens[*num_tokens].is_num = false;
                    tokens[*num_tokens].num_var = DUMMY_DOUBLE;
                    tokens[*num_tokens].operation = '*';

                    (*num_tokens)++;
                }
                oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
                break;
            }

            default: {
                if (equation[idx] >= '0' && equation[idx] <= '9') {
                    if (!stod(equation, &number, &idx))
                        flag = false;
                    else {
                        tokens[*num_tokens].is_num = true;
                        tokens[*num_tokens].num_var = number;
                        tokens[*num_tokens].operation = DUMMY_CHAR;
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
