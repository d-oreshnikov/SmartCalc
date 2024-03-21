
#include "help_func.h"

//make from infix notation to postfix notationS
token *postfix_func(token *infix, size_t infxlen, size_t *pidx);
//tokenize input equation
token *tokenize(const char* equation, size_t* num_tokens);

