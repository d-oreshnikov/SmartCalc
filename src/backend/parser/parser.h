#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include "putils.h"

/**
 * @brief          Converts infix notation (1 + 2) into postfix notation (1 2 +)
 * 
 * @param infix    Infix (source) notation in array of tokens representation
 * @param ilength  Length of the infix notation
 * @param plength  Pointer to the length of the postfix notation
 * @return         Postfix notation in array of tokens representation
 */
token* gpostfix(token* infix, size_t ilength, size_t* plength);

/**
 * @brief           Tokenizes input equation (creates array of tokens)
 * 
 * @param equation  Source equation (user input)
 * @param length    Pointer to equation length
 * @return          List of tokens representing source equation ( sin(x) -> {'s', '(', 'x', ')'} )
 */
token* tokenize(const char* equation, size_t* length);

#endif  // SRC_PARSER_PARSER_H_