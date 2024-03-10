#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include "../types.h"

/**
 * @brief       Initializes stk_t object
 * 
 * @param stk   Pointer to stack object
 * @return      If stack initialized successfully flag
 */
eflag _sinit(stack* stk);

/**
 * @brief           Initializes node_t object with given token values
 *  
 * @param src       Pointer to node to be initialized
 * @param tk        Pointer to the token data value
 * @return          If node initialized correctly flag
 */
eflag cnode(node* src, token* tk);

/**
 * @brief       Pushes new token onto the stack
 * 
 * @param head  Pointer to the stack object
 * @param tk    Pointer to the token data value
 * @return      If node initialized correctly flag
 */
eflag _spush(stack* head, token* tk);

/**
 * @brief      Pops value from stack and returns its value
 * 
 * @param stk  Pointer to the stack object
 * @return     Popped data
 */
token* _spop(stack* stk);

/**
 * @brief      Destroys stack object
 * 
 * @param stk  Pointer to the stack to destroy
 * @return     If stack destoyed successfully flag
 */
eflag _sdestroy(stack* stk);

#endif  // SRC_STACK_STACK_H_
