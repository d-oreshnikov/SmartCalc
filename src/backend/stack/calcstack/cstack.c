#include "cstack.h"

// calc stack init
eflag calcstinit(calcstack *stk) {
  eflag flag = SUCCESS;

  if (!stk)
    flag = NULL_PTR;
  else {
    stk->head = NULL;
    stk->size = 0;
  }
  return flag;
}

// calc node init
eflag calcnodeinit(calcnode *src, double value) {
  eflag flag = SUCCESS;
  if (!src)
    flag = FAILED_ALLOC;
  else {
    src->data = value;
    src->next = NULL;
  }
  return flag;
}

// push new noda to calc stack
eflag calcspush(calcstack *stk, double value) {
  eflag flag = SUCCESS;

  if (!stk)
    flag = NULL_PTR;
  else {
    calcnode *calnode = (calcnode *)calloc(1, sizeof(calcnode));
    eflag node_flag = calcnodeinit(calnode, value);
    if (node_flag)
      flag = node_flag;
    else {
      calnode->next = stk->head;
      stk->head = calnode;
      stk->size++;
    }
  }
  return flag;
}

// pop value from calc stack and return it back
double calcspop(calcstack *stk) {
  double res = stk->head->data;

  calcnode *temp_head = stk->head;
  stk->head = stk->head->next;
  free(temp_head);
  stk->size--;

  return res;
}

// destroys calc stack
eflag calcsdestroy(calcstack *stk) {
  if (!stk) return NULL_PTR;
  if (!stk->head) return NULL_PTR;

  calcnode *curr = stk->head;
  calcnode *next = NULL;
  do {
    next = curr->next;
    free(curr);
    curr = next;
    next = NULL;
  } while (curr);

  stk = NULL;
  return SUCCESS;
}