#include "clstack.h"

eflag _csinit(clstack *stk) {
    /*
    Description:
        Initializes cstk_t object

    Args:
        (clstack*) stk : Pointer to stack object

    Returns:
        If stack initialized successfully flag
    */

    if (!stk) return NULL_PTR;

    stk->head = NULL;
    stk->size = 0;

    return SUCCESS;
}

eflag ccnode(clnode *src, double val) {
    /*
    Description:
        Initializes node_t object with given data value

    Args:
        (node*) src       : Pointer to node to be initialized
        (double) val      : Value to create node with

    Returns:
        If node initialized correctly flag
    */

    if (!src) return FAILED_ALLOC;

    src->data = val;
    src->next = NULL;

    return SUCCESS;
}

eflag _cspush(clstack *stk, double val) {
    /*
    Description:
        Pushes new value onto the stack

    Args:
        (stack*) head  : Pointer to the stack object
        (double) val    : Value to push onto the stack

    Returns:
        If data pushed successfully flag
    */

    if (!stk) return NULL_PTR;

    clnode *nnode = (clnode *)calloc(1, sizeof(clnode));
    eflag flag = ccnode(nnode, val);
    if (flag) return flag;

    nnode->next = stk->head;
    stk->head = nnode;
    stk->size++;

    return SUCCESS;
}

double _cspop(clstack *stk) {
    /*
    Description:
        Pops value from stack and returns its value

    Args:
        (stack*) stk : Pointer to the stack object

    Returns:
        Popped data
    */

    double res = stk->head->data;

    clnode *thead = stk->head;
    stk->head = stk->head->next;
    free(thead);
    stk->size--;

    return res;
}

eflag _csdestroy(clstack *stk) {
    /*
    Description:
        Destroys stack object

    Args:
        (stack*) stk : Pointer to the stack to destroy

    Returns:
        If stack destroyed successfully flag
    */

    if (!stk) return NULL_PTR;
    if (!stk->head) return NULL_PTR;

    clnode *curr = stk->head;
    clnode *next = NULL;

    do {
        next = curr->next;
        free(curr);
        curr = next;
        next = NULL;
    } while (curr);

    stk = NULL;

    return SUCCESS;
}