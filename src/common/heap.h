#ifndef _HEAP_H
#define _HEAP_H

#include "olsr_types.h"

#define INLINE inline __attribute__((always_inline))

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
void heap_init_node(struct heap_node *node);
void heap_decrease_key(struct heap *root, struct heap_node *node);
void heap_insert(struct heap *root, struct heap_node *node);
struct heap_node *heap_extract_min(struct heap *root);

/**
 * @param root pointer to binary heap
 * @return size of heap, 0 if is empty
 */
static INLINE unsigned int
heap_get_size(struct heap *root)
{
    return root->count;
}

/**
 * @param root pointer to binary heap
 * @return pointer to root node
 */
static INLINE struct heap_node*
heap_get_root_node(struct heap *root)
{
    return root->root_node;
}

/**
 * @param root pointer to binary heap
 * @return true if the heap is empty, false otherwise
 */
static INLINE bool
heap_is_empty(struct heap *root)
{
    return root->count == 0;
}

/**
 * @param node pointer to node of the heap
 * @return true if node is currently in the heap, false otherwise
 */
static INLINE bool
heap_is_node_added(struct heap_node *node)
{
    if(!node)
        return false;
    return !(node->parent || node->left || node->right);
}

#define HEAPNODE2STRUCT(funcname, structname, heapnodename) \
static inline structname * funcname (struct heap_node *ptr)\
{\
  return( \
    ptr ? \
      (structname *) (((size_t) ptr) - offsetof(structname, heapnodename)) : \
      NULL); \
}

#endif /* _HEAP_H */
