#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include "../types.h"

eflag stinit(stack* stk); // stack init func
eflag nodeinit(node* src, token* tk);  // noda init with given token func
eflag spush(stack* head, token* tk); //push token to stack top
token* spop(stack* stk); // pop token from stack and return its value
eflag sdestroy(stack* stk); // destroys stack object

#endif // SRC_STACK_STACK_H_