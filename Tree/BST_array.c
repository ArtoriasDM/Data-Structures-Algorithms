#include <stdio.h>
#include <stdlib.h>

#define BASE 2

typedef struct
{
    int * array;
    int size;
    int count;
    int height;
}BinarySearchTree;

BinarySearchTree * init()
{
    BinarySearchTree * new;
    int i;

    new = malloc(sizeof(BinarySearchTree));
    if(!new){
        printf("Failed memory allocation\n");
        return NULL;
    }

    new->size = 1;
    new->height = 0;
    new->count = 0;

    new->array = malloc(sizeof(int) * new->size);
    if(new->array == NULL)
    {
        printf("Failed memory allocation\n");
        free(new);
        return NULL;
    }

    for(i = 0; i < new->size; i++)
    {
        new->array[i] = -1;
    }

    return new;
}

int Height(BinarySearchTree * bst, int index)
{
    int left, right;

    if(index >= bst->size || bst->array[index] == -1)
    {
        return 0;
    }

    left = Height(bst, index * BASE + 1);
    right = Height(bst, index * BASE + 2);

    if(left > right)
        return left;
    return right;
}

void InOrder(BinarySearchTree * bst, int index)
{
    if(index < bst->size || bst->array[index] != -1)
    {
        InOrder(bst->array, (BASE * index + 1));
        printf("%d", bst->array[index]);
        InOrder(bst->array, (BASE * index + 2));
    }
}

void PreOrder(BinarySearchTree * bst, int index)
{
    if(index < bst->size || bst->array[index] != -1)
    {
        printf("%d", bst->array[index]);
        PreOrder(bst->array, (BASE * index + 1));
        PreOrder(bst->array, (BASE * index + 2));
    }
}

void PostOrder(BinarySearchTree * bst, int index)
{
    if(index < bst->size || bst->array[index] != -1)
    {
        PostOrder(bst->array, (BASE * index + 1));
        PostOrder(bst->array, (BASE * index + 2));
        printf("%d", bst->array[index]);
    }
}

int Search(BinarySearchTree * bst, int key, int index)
{
    if(bst->array[index] == key){
        return index;
    }else if(index >= bst->size || bst->array[index] == -1){
        return -1;      // not found
    }

    if(bst->array[index] < key){
        return Search(bst, key, (index * BASE + 1));
    }else{
        return Search(bst, key, (index * BASE + 2));
    }
}

int Min(BinarySearchTree * bst, int index)
{
    while((BASE * index + 1) < bst->size && bst->array[BASE * index + 1] != -1)
    {
        index = BASE * index + 1;
    }

    if(bst->array[index] == -1)
        return -1; // minimun doesn't exist
    else
        return bst->array[index];
}

int Max(BinarySearchTree * bst, int index)
{
    while((BASE * index + 2) < bst->size && bst->array[BASE * index + 2] != -1)
    {
        index = BASE * index + 2;
    }

    if(bst->array[index] == -1)
        return -1;
    else
        return bst->array[index];
}

int Successor(BinarySearchTree * bst, int index)
{
    int parent_index;

    if((index * BASE + 2) < bst->size && bst->array[index * BASE + 2] != -1)
    {
        return Min(bst, (index * BASE + 2));
    }

    parent_index = (index - 1) / 2;
    while(parent_index >= 0 && (parent_index * BASE + 2) == index)
    {
        index = parent_index;
        parent_index = (parent_index - 1) / 2;
    }

    return parent_index;
}

void Resize(BinarySearchTree * bst, int new_height)
{
    int new_size, pow, i;
    int * tmp;

    new_size = 0;
    pow = 1;
    for(i = 0; i < new_height; i++)
    {
        new_size += pow;
        pow *= BASE;
    }

    tmp = realloc(bst->array, sizeof(int) * new_size);

    if(tmp == NULL)
    {
        printf("Failed memory allocation\n");
        return;
    }

    bst->array = tmp;
    bst->height = new_height;
    bst->size = new_size;
}

void Insert(BinarySearchTree * bst, int key)
{
    int index = 0;

    while(index < bst->size && index != -1)
    {
        if(key < bst->array[index])
            index = BASE * index + 1;
        else
            index = BASE * index + 2;
    }

    if(index >= bst->size)
    {
        resize(bst, bst->height + 1);
    }

    bst->array[index] = key;
    bst->count += 1;
}

void delete(BinarySearchTree * bst, int key)
{
    int del_index, new_height;

    if((BASE * key + 1 < bst->size && bst->array[BASE * key + 1] != -1) && (BASE * key + 2 < bst->size && bst->array[BASE * key + 2] != -1))
    {
        del_index = Successor(bst, key);
        bst->array[key] = bst->array[del_index];
        delete(bst, del_index);
    }else{
        if(BASE * key + 1 < bst->size && bst->array[BASE * key + 1] != -1)
        {
            del_index = BASE * key + 1;
        }else if(BASE * key + 2 < bst->size && bst->array[BASE * key + 2] != -1){
            del_index = BASE * key + 2;
        }else{
            del_index = -1;
        }

        if(del_index != -1){
            bst->array[key] = bst->array[del_index];
            delete(bst, del_index);
        }else{
            bst->array[key] = -1;
        }
    }

    if(Height(bst, 0) < bst->height)
    {
        new_height = bst->height - Height(bst, 0);
        Resize(bst, new_height);
    }

    bst->count--;
}