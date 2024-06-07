#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    int key;
    struct node_s * parent;
    struct node_s * right;
    struct node_s * left;
}node_t;

typedef struct
{
    node_t * root;
}BinarySearchTree;

BinarySearchTree * __init__()
{
    BinarySearchTree * bst;

    bst = malloc(sizeof(BinarySearchTree));

    if(bst != NULL){
        bst->root = NULL;
    }else{
        printf("Failed memory allocation\n");
    }

    return bst;
}

node_t * CreateNode(int key)
{
    node_t * new;

    new = malloc(sizeof(node_t));

    if(new != NULL){
        new->key = key;
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
    }

    return new;
}

void InOrder(node_t * node)
{
    if(node != NULL)
    {
        InOrder(node->left);
        printf("%d ", node->key);
        InOrder(node->right);
    }
}

void PreOrder(node_t * node)
{
    if(node != NULL)
    {
        printf("%d ", node->key);
        PreOrder(node->left);
        PreOrder(node->right);
    }
}

void PostOrder(node_t * node)
{
    if(node != NULL)
    {
        PostOrder(node->left);
        PostOrder(node->right);
        printf("%d ", node->key);
    }
}

node_t * Search(node_t * root, int key)
{
    if(root->key == key || root == NULL)
    {
        return root;
    }

    if(root->key < key){
        return Search(root->right, key);
    }else if(root->key > key){
        return Search(root->left, key);
    }
}

node_t * Min(node_t * root)
{
    node_t * curr;

    curr = root;

    while(curr && curr->left)
    {
        curr = curr->left;
    }

    return curr;
}

node_t * Max(node_t * root)
{
    node_t * curr;

    curr = root;

    while(curr && curr->right)
    {
        curr = curr->right;
    }

    return curr;
}

node_t * Successor(node_t * node)
{
    node_t * parent;

    if(node->right){
        return min(node->right);
    }

    parent = node->parent;
    while(parent && parent->right == node)
    {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void Insert(BinarySearchTree * bst, int key)
{
    node_t * pre, * curr, * new;

    pre = NULL;
    curr = bst->root;

    while(curr)
    {
        pre = curr;
        if(key < curr->key){
            curr = curr->left;
        }else{
            curr = curr->right;
        }
    }

    new = CreateNode(key);
    new->parent = pre;

    if(pre == NULL){
        bst->root = new;
    }else if(new->key < pre->key){
        pre->left = new;
    }else{
        pre->right = new;
    }
}

void Delete(BinarySearchTree * bst, node_t * node)          
{
    node_t * del, * subtree;

    if(node->left == NULL || node->right == NULL){           // caso 1: il nodo ha 1 o nessun figlio
        del = node;
    }else{                                                   // caso 2: il nodo ha 2 figli, copio il valore del successore su di esso ed elimino il successore 
        del = Successor(node);
    }

    if (del->left != NULL)                                   // individuiamo il sottoalbero da reinserire
    {
        subtree = del->left;                                 // NOTA: il successore di un nodo con due figli non ha mai il figlio SX
    }else{
        subtree = del->right;
    }

    if(subtree != NULL){
        subtree->parent = del->parent;                       // ripristino dei riferimenti del sottoalbero
    }

    if(del->parent == NULL){                                 // Se il nodo è la radice dell'albero
        bst->root = subtree;
    }else if(del == del->parent->left){                      // se il nodo è figlio sx o dx
        del->parent->left = subtree;
    }else{
        del->parent->right = subtree;
    }

    if (del != node){                                        // Nel caso del successore dobbiamo ricopiare il valore della chiave
        node->key = del->key;
    }
    free(del);
}
