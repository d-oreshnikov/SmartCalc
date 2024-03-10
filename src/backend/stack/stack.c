#include "stack.h"

eflag _sinit(stack *stk) {
    /*
    Description:
        Initializes stack_t object

    Args:
        (stack*) stk : Pointer to stack object

    Returns:
        If stack initialized successfully flag
    */

    if (!stk) return NULL_PTR;

    stk->head = NULL;
    stk->size = 0;

    return SUCCESS;
}

eflag cnode(node *src, token *tk) {
    /*
    Description:
        Initializes node_t object with the respect to dtype

    Args:
        (node*) src       : Pointer to node to be initialized
        (token) tk        : Pointer to the token data value

    Returns:
        If node initialized correctly flag
    */

    if (!src) return FAILED_ALLOC;

    src->data = tk;
    src->next = NULL;

    return SUCCESS;
}

eflag _spush(stack *stk, token *tk) {
    /*
    Description:
        Pushes new token onto the stack

    Args:
        (stack*) head  : Pointer to the stack object
        (token) tk     : Pointer to the token data value

    Returns:
        If data pushed successfully flag
    */

    if (!stk) return NULL_PTR;

    node *nnode = (node *)calloc(1, sizeof(node));
    eflag flag = cnode(nnode, tk);
    if (flag) return flag;

    nnode->next = stk->head;
    stk->head = nnode;
    stk->size++;

    return SUCCESS;
}

token *_spop(stack *stk) {
    /*
    Description:
        Pops value from stack and returns its value

    Args:
        (stack*) stk : Pointer to the stack object

    Returns:
        Popped data
    */

    if (!stk) return NULL;

    token *res = stk->head->data;

    node *thead = stk->head;
    stk->head = stk->head->next;
    free(thead);
    stk->size--;

    return res;
}

eflag _sdestroy(stack *stk) {
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

    node *curr = stk->head;
    node *next = NULL;

    do {
        next = curr->next;
        free(curr);
        curr = next;
        next = NULL;
    } while (curr);

    stk = NULL;

    return SUCCESS;
}
