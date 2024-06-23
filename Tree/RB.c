#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct node_s
{
    int key;
    int color;
    struct node_s * parent;
    struct node_s * left;
    struct node_s * right;
}node_t;

typedef struct 
{
    node_t * root;
    node_t * tail;
}RedBlackTree;

RedBlackTree * __init__()
{
    RedBlackTree * new;

    new = malloc(sizeof(RedBlackTree));

    if(new != NULL)
    {
        new->tail = NULL;
        new->root = NULL;
    }else{
        printf("Failed memory allocation\n");
    }

    return new;
}

void LeftRotate(RedBlackTree * rb, node_t * x)
{
    node_t * y;

    y = x->right;                               // riferimento al figlio destro di x, con figli destro e sinistro rispettivamente γ e β

    x->right = y->left;                         // sposta il sottoalbero β nella posizione corretta
    if(y->left != rb->tail)
    {
        y->left->parent = x;                    // sistema il riferimento al padre di β
    }

    y->parent = x->parent;                      // sistema i riferimenti al padre p
    if(x->parent == rb->tail)
    {
        rb->root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }

    y->left = x;                               // aggancia x a sinistra di y;
    x->parent = y;
}

void RightRotate(RedBlackTree * rb, node_t * x)
{
    node_t * y;

    y = x->left;

    x->left = y->right;
    if(y->right != rb->tail)
    {
        y->right->parent = x;
    }

     y->parent = x->parent;                      
    if(x->parent == rb->tail)
    {
        rb->root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}