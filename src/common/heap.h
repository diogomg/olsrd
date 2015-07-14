#ifndef _HEAP_H
#define _HEAP_H

#include "olsr_types.h"

/**
 * Element included into a heap.
 */
struct heap_node{
    /**
     * node's key based on the link cost type.
     */
    olsr_linkcost key;

    /**
     * Pointer to parent node in the heap, NULL if root node.
     */
    struct heap_node *parent;

    /**
     * Pointer to left child, NULL if there isn't.
     */
    struct heap_node *left;

    /**
     * Pointer to right child, NULL if there isn't.
     */
    struct heap_node *right;
};

/**
 * Manager struct of the heap.
 * One of them is necessary for each heap.
 */
struct heap{
    /**
     * Number of nodes in the heap.
     */
    unsigned int count;

    /**
     * Pointer to the root node of the heap, NULL if heap is empty.
     */
    struct heap_node *root_node;

    /**
     * Pointer to the rightest node of the lowest level in the heap,
     * NULL if heap is empty.
     */
    struct heap_node *last_node;
};

void heap_init(struct heap *root);
void heap_decrease_key(struct heap *root, struct heap_node *node);
void heap_insert(struct heap *root, struct heap_node *node);
struct heap_node *heap_extract_min(struct heap *root);

#define HEAPNODE2STRUCT(funcname, structname, heapnodename) \
static inline structname * funcname (struct heap_node *ptr)\
{\
  return( \
    ptr ? \
      (structname *) (((size_t) ptr) - offsetof(structname, heapnodename)) : \
      NULL); \
}

#endif /* _HEAP_H */
