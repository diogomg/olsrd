#ifndef _HEAP_H
#define _HEAP_H

#include "olsr_types.h"

struct heap_node{
    olsr_linkcost key;
    int vertex;
    struct heap_node *parent, *left, *right;
};

struct heap{
    unsigned int count;
    struct heap_node *root_node, *last_node;
};

void heap_init(struct heap *root);

unsigned int heap_perfect_log2 (unsigned int number);

struct heap_node* heap_find_parent_insert_node(struct heap *root);

void heap_decrease_key(struct heap *root, struct heap_node *node);

void heap_insert(struct heap *root, struct heap_node *node);

void heap_swap_left(struct heap *root, struct heap_node *node);

void heap_swap_right(struct heap *root, struct heap_node *node);

void heap_increse_key(struct heap *root, struct heap_node *node);

struct heap_node* heap_find_last_node(struct heap *root);

struct heap_node *heap_extract_min(struct heap *root);

void heap_print(struct heap_node *root);

#define HEAPNODE2STRUCT(funcname, structname, heapnodename) \
static inline structname * funcname (struct heap_node *ptr)\
{\
  return( \
    ptr ? \
      (structname *) (((size_t) ptr) - offsetof(structname, heapnodename)) : \
      NULL); \
}

#endif /* _HEAP_H */
