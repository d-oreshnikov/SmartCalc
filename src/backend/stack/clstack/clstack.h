#ifndef SRC_STACK_CLSTACK_CLSTACK_H_
#define SRC_STACK_CLSTACK_CLSTACK_H_

#include "../../types.h"

/**
 * @brief       Initializes cstk_t object
 * 
 * @param stk   Pointer to stack object
 * @return      If stack initialized successfully flag
 */
eflag _csinit(clstack* stk);

/**
 * @brief           Initializes node_t object with given data value
 *  
 * @param src       Pointer to node to be initialized
 * @param val       Value to create node with
 * @return          If node initialized correctly flag
 */
eflag ccnode(clnode* src, double val);

/**
 * @brief       Pushes new value onto the stack
 * 
 * @param head  Pointer to the stack object
 * @param val   Value to push onto the stack
 * @return      If node initialized correctly flag
 */
eflag _cspush(clstack* head, double val);

/**
 * @brief      Pops value from stack and returns its value
 * 
 * @param stk  Pointer to the stack object
 * @return     Popped data
 */
double _cspop(clstack* stk);

/**
 * @brief      Destroys stack object
 * 
 * @param stk  Pointer to the stack to destroy
 * @return     If stack destoyed successfully flag
 */
eflag _csdestroy(clstack* stk);

#endif  // SRC_STACK_CLSTACK_CLSTACK_H_