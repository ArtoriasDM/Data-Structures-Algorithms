#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 100

typedef struct
{
    int key;
    int val;
}element;

typedef struct 
{
    element **table;
    int size;
    int count;
}dictionary;

void  __init__(dictionary * dict)
{
    int i;

    dict = malloc(sizeof(dictionary));

    if(dict == NULL){
        printf("__init__ failed memory allocation\n");
        return;
    }

    dict->size = INITIAL_SIZE;
    dict->count = 0;
    dict->table = malloc(sizeof(element *) * dict->size);

    if(dict->table == NULL){
        printf("__init__ failed memory allocation\n");
        free(dict);
        return;
    }

    for(i = 0; i < dict->size; i++){
        dict->table[i] = NULL;
    }
}

int isempty(dictionary * dict)
{
    return (dict->count == 0);
}

int isfull(dictionary * dict)
{
    return (dict->count == dict->size);
}

element * CreateNewElement(int key, int data)
{
    element * new;

    new = malloc(sizeof(element));

    if(new == NULL){
        printf("unable to allocate memory for the new element\n");
        return NULL;
    }

    new->val = data;
    new->key = key;

    return new;
}

void resize(dictionary * dict)
{
    element **new;
    int new_size, i;

    new_size = dict->size + INITIAL_SIZE;
    new = malloc(sizeof(element *) * new_size);

    if(new != NULL){
        for(i = 0; i < new_size; i++){
            new[i] = NULL;
        }
        for(i = 0; i < dict->size; i++){
            new[i] = dict->table[i];
        }
        free(dict->table);
        dict->table = new;
        dict->size = new_size;
    }
    printf("resize failed buffer memory allocation\n");
}

void insert(dictionary * dict, int item, int key)
{
    element * new;

    if(key < 0){
        printf("key outside range\n");
        return;
    }

    while (key >= dict->size)
    {
        resize(dict);
    }
    
    new = CreateNewElement(key, item);

    dict->table[new->key] = new;
    dict->count = dict->count + 1;
}

void delete(dictionary * dict, int key)
{
    if(key < 0 || key >= dict->size){
        printf("key outside range\n");
        return;
    }
    free(dict->table[key]);
    dict->table[key] == NULL;
    dict->count--;
}

element * search(dictionary * dict, int key)
{
    if(key < 0 || key >= dict->size){
        printf("key outside range\n");
        return;
    }
    
    return dict->table[key];
}

