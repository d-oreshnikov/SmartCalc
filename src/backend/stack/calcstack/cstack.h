#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include "../../types.h"

eflag calcstinit(calcstack* stk); //  calc stack init func
eflag calcnodeinit(calcnode* src, double value);  //calc  noda init with given token func
eflag calcspush(calcstack* head, double value); //push token to calc stack top
double calcspop(calcstack* stk); // pop token from calc stack and return its value
eflag calcsdestroy(calcstack* stk); // destroys calc stack object

#endif // SRC_STACK_STACK_H_