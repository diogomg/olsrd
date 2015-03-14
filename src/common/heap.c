#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heap.h"

void heap_init(struct heap *root){
    root->count = 0;
    root->root_node = root->last_node = NULL;
}

unsigned int heap_perfect_log2 (unsigned int number) {
    unsigned int log = 0, pow=1, original_number=number, i;
    while (number >>= 1) ++log;
    for (i = 0; i < log; i++) {
        pow <<= 1;
    }
    return original_number-pow;
}

struct heap_node* heap_find_parent_insert_node(struct heap *root){
    struct heap_node *aux = root->last_node;
    unsigned int N = root->count+1;
    if ( !heap_perfect_log2(N) ){
        aux = root->root_node;
        while (aux->left) {
            aux = aux->left;
        }
    }
    else if ( N % 2 == 0){
        while(aux->parent->right == aux)
            aux = aux->parent;
        if(!aux->parent->right)
            return aux->parent;
        aux = aux->parent->right;
        while(aux->left)
            aux = aux->left;
    }
    else{
        aux = aux->parent;
    }
    return aux;
}

void heap_decrease_key(struct heap *root, struct heap_node *node){
    struct heap_node *parent = node->parent;
    struct heap_node *left = node->left;
    struct heap_node *right = node->right;
    if(!parent)
        return;
    if(parent->key > node->key){
        if(root->last_node == node)
            root->last_node = parent;
    }
    while(parent && (parent->key > node->key)){
        if(parent->left == node){
            node->left = parent;
            node->right = parent->right;
            if(node->right)
                node->right->parent = node;
            node->parent = parent->parent;
            if(node->parent){
                if(node->parent->left == parent)
                    node->parent->left = node;
                else
                    node->parent->right = node;
            }
            else
                root->root_node = node;
        }
        else{
            node->right = parent;
            node->left = parent->left;
            if(node->left)
                node->left->parent = node;
            node->parent = parent->parent;
            if(node->parent){
                if(node->parent->left == parent)
                    node->parent->left = node;
                else
                    node->parent->right = node;
            }
            else
                root->root_node = node;
        }
        parent->left = left;
        parent->right = right;
        parent->parent = node;
        if(left)
            left->parent = parent;
        if(right)
            right->parent = parent;
        parent = node->parent;
        left = node->left;
        right = node->right;
    }
}

void heap_insert(struct heap *root, struct heap_node *node){
    struct heap_node *parent = NULL;
    if(!root->count){
        root->root_node = root->last_node = node;
        root->count++;
    }
    else{
        parent = heap_find_parent_insert_node(root);
        if(parent->left){
            parent->right = node;
        }
        else{
            parent->left = node;
        }
        node->parent = parent;
        root->count++;
        root->last_node = node;
        heap_decrease_key(root, node);
    }
}


void heap_swap_left(struct heap *root, struct heap_node *node){
    struct heap_node *parent = node->parent;
    struct heap_node *left = node->left;
    struct heap_node *right = node->right;

    node->parent = left;
    node->left = left->left;
    if(node->left)
        node->left->parent = node;
    node->right = left->right;
    if(node->right)
        node->right->parent = node;

    left->parent = parent;
    if(parent){
        if(parent->left == node)
            parent->left = left;
        else
            parent->right = left;
    }
    else
        root->root_node = left;
    left->left = node;
    left->right = right;
    if(right)
        right->parent = left;
    if(root->last_node == left)
        root->last_node = node;
}

void heap_swap_right(struct heap *root, struct heap_node *node){
    struct heap_node *parent = node->parent;
    struct heap_node *left = node->left;
    struct heap_node *right = node->right;

    node->parent = right;
    node->left = right->left;
    if(node->left)
        node->left->parent = node;
    node->right = right->right;
    if(node->right)
        node->right->parent = node;

    right->parent = parent;
    if(parent){
        if(parent->left == node)
            parent->left = right;
        else
            parent->right = right;
    }
    else
        root->root_node = right;
    right->right = node;
    right->left = left;
    if(left)
        left->parent = right;
    if(root->last_node == right)
        root->last_node = node;
}

void heap_increse_key(struct heap *root, struct heap_node *node){
    struct heap_node *left = node->left;
    struct heap_node *right = node->right;
    if(left && (node->key > left->key)){
        if(right && (node->key > right->key)){
            if(left->key < right->key)
                heap_swap_left(root, node);
            else
                heap_swap_right(root, node);
        }
        else
            heap_swap_left(root, node);
        heap_increse_key(root, node);
    }
    else if(right && (node->key > right->key)){
        heap_swap_right(root, node);
        heap_increse_key(root, node);
    }
}

struct heap_node* heap_find_last_node(struct heap *root){
    struct heap_node *aux = root->last_node;
    unsigned int N = root->count+1;
    if ( !heap_perfect_log2(N) ){
        aux = root->root_node;
        while (aux->right) {
            aux = aux->right;
        }
    }
    else if ( N % 2 == 0){
        while(aux->parent->left == aux)
            aux = aux->parent;
        aux = aux->parent->left;
        while(aux->right)
            aux = aux->right;
    }
    return aux;
}

struct heap_node *heap_extract_min(struct heap *root){
    struct heap_node *min_node = root->root_node;
    struct heap_node *new_min = root->last_node;
    if(!min_node)
        return NULL;
    root->count--;
    if(root->count == 0){
        root->last_node = root->root_node = NULL;
        return min_node;
    }
    if(root->count == 1){
        root->last_node = root->root_node = new_min;
        new_min->parent = NULL;
        return min_node;
    }
    else{
        if(new_min->parent->left == new_min){
            new_min->parent->left = NULL;
            root->last_node = new_min->parent;
            root->last_node = heap_find_last_node(root);
        }
        else{
            new_min->parent->right = NULL;
            root->last_node = new_min->parent->left;
        }
        new_min->left = min_node->left;
        if(new_min->left)
            new_min->left->parent = new_min;
        new_min->right = min_node->right;
        if (new_min->right)
            new_min->right->parent = new_min;
        new_min->parent = NULL;
        root->root_node = new_min;
        heap_increse_key(root, new_min);
    }
    return min_node;
}

void heap_print(struct heap_node *root){
    if(root){
        printf("%d\n", root->key);
        heap_print(root->left);
        heap_print(root->right);
    }
}
