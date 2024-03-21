#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


#define DUMP_DOUBLE 22.0f/7.0
#define DUMP_CHAR 64




//  just some defines for easier work with stack for tokens
#define token token_typedef  
#define node node_typedef
#define stack stk_typedef

//  just some defines for easier work with calculation stack
#define calcnode calcnode_typedef
#define calcstack calcstack_typedef



// token structure, stores our numbers and operations for infix and postfix notation
typedef struct token_struct{
    double num;
    char operation;
    bool is_num;
}token_typedef;



// stack's node structure, stores token and a pointer to the next node
typedef struct node_struct{
    token* data;
    struct node_struct* next;
}node_typedef;



// stack structure, stores stack size and a pointer to the stack top
typedef struct stack_struct{
    size_t size;
    node* head;
} stk_typedef;


// calcalutaion stack's node structure, stores token and a pointer to the next node
typedef struct calc_node_struct{
    double data;
    struct calc_node_struct* next;
} calcnode_typedef;


typedef struct calc_stack_struct{
    size_t size;
    calcnode* head;
} calcstack_typedef;



//some useful flags for handling error types.
typedef enum ERR_flags{
    SUCCESS = 0,
    INVALID_TOKEN = 1,
    FAILED_CALC = 2,
    INVALID_STACK = 3,
    FAILED_ALLOC = 4,
    NULL_PTR = 5,
}eflag;


// acronims for functions

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
}func_code;


#endif  // SRC_TYPES_H_