#include "stack.h"

// stack init
eflag stinit(stack *stk) {
  eflag flag = SUCCESS;

  if (!stk)
    flag = NULL_PTR;
  else {
    stk->head = NULL;
    stk->size = 0;
  }
  return flag;
}

eflag spush(stack *stk, token *tk) {
  eflag flag = SUCCESS;

  if (!stk)
    flag = NULL_PTR;
  else {
    node *nnode = (node *)calloc(1, sizeof(node));
    eflag node_flag = nodeinit(nnode, tk);
    if (node_flag)
      flag = node_flag;
    else {
      nnode->next = stk->head;
      stk->head = nnode;
      stk->size++;
    }
  }

  return flag;
}

// node init
eflag nodeinit(node *src, token *tk) {
  eflag flag = SUCCESS;
  if (!src)
    flag = FAILED_ALLOC;
  else {
    src->data = tk;
    src->next = NULL;
  }
  return flag;
}

// pop value from stack and return it back
token *spop(stack *stk) {
  if (!stk) return NULL;

  token *res = stk->head->data;

  node *temp_head = stk->head;
  stk->head = stk->head->next;
  free(temp_head);
  stk->size--;
  return res;
}

// destroys stack
eflag sdestroy(stack *stk) {
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