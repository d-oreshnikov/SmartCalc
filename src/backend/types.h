#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include <string.h>
#include <stdlib.h>

/**
 * @brief Dummy numeric value to fill token with operator data.
 * 
 */
#define DUMMY_DOUBLE 22.0f/7.0

/**
 * @brief Dummy character value to fill token with numerical data.
 * 
 */
#define DUMMY_CHAR 64

/**
 * @brief Convinient wrapper type for token_t object.
 * 
 */
#define token token_t

/**
 * @brief Convinient wrapper type for node_t object.
 * 
 */
#define node node_t

/**
 * @brief Convinient wrapper type for stk_t object.
 * 
 */
#define stack stk_t

/**
 * @brief Convinient wrapper type for cnode_t (calculation node) object.
 * 
 */
#define clnode cnode_t

/**
 * @brief Convinient wrapper type for cstk_t (calculation stack) object.
 * 
 */
#define clstack cstk_t

/**
 * @brief Token structure for processing infix and postfix notation
 * in better way than just a char variable. Is stores numerical value, 
 * operator value and is_num boolean flag. If token representing, for example,
 * numerical value - is stores: 1. actual numerical value; 2. dummy operator
 * value; 3. true is_num flag and vice versa. 
 * 
 */
typedef struct token_s {
    double num_var;
    char operation;
    bool is_num;
} token_t;

/**
 * @brief Stack node structure. It stores token and a pointer to the next
 * node.
 * 
 */
typedef struct node_s {
    token* data;
    struct node_s* next;
} node_t;

/**
 * @brief Stack structure that stores stack size and pointer to the head (top)
 * node.
 * 
 */
typedef struct stk_s {
    size_t size;
    node* head;
} stk_t;

/**
 * @brief Calculation node structure. It stores double value
 * and pointer to the next calculation node.
 * 
 */
typedef struct cnode_s {
    double data;
    struct cnode_s* next;
} cnode_t;

/**
 * @brief Calculation stack structure. Since pushing onto the stack assumes
 * new token creation it is more convinient to define separate stack that stores
 * only numeric values to perform calculation using that stack. It stores stack size and the pointer to
 * head (top) node.
 * 
 */
typedef struct cstk_s {
    size_t size;
    clnode* head;
} cstk_t;

/**
 * @brief Enum for coding math operators (mod, sqrt) and functions
 * (sin, cos, etc.).
 * 
 */
typedef enum FUNC_CODE {
    SIN = 's',
    COS = 'c',
    TAN = 't',
    ASIN = 'S',
    ACOS = 'C',
    ATAN = 'T',
    SQRT = 'q',
    LOG = 'l',
    LN = 'L',
    MOD = 'm',
} func_code;

/**
 * @brief Enum for handling different errors types. One can be raised
 * while parsing input or generating Reverse Polish Notation while another
 * can be raise while calculation
 * 
 */
typedef enum ERR_FLAG {
    SUCCESS = 0,
    INVALID_TOKEN = 1,
    FAILED_CALC = 2,
    INVALID_STACK = 3,
    FAILED_ALLOC = 4,
    NULL_PTR = 5,
    INIT_ERROR = 6,
} eflag;

#endif  // SRC_TYPES_H_
