#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    int data;
    struct node_s * next;
    struct node_s * prev;
}node_t;

typedef struct deque_s
{
    node_t * head;
    node_t * tail;
}deque_t;

deque_t * __init__(deque_t * d)
{
    d = malloc(sizeof(deque_t));
    if(d == NULL){
        printf("__init__ failed memory allocation\n");
        return NULL;
    }
    d->head = NULL;
    d->tail = d->head;

    return d;
}

int isempty(deque_t * d)
{
    return ((d->head == d->tail) == NULL);
}

deque_t * pushfront(deque_t * d, int item)
{
    node_t * new;

    new = malloc(sizeof(node_t));
    if(new == NULL){
        printf("pushfront failed memory allocation\n");
    }else{
        new->data = item;
        new->prev = NULL;
        if(isempty(d)){
            new->next = NULL;
            d->head = new;
            d->tail = new;
        }else{
            new->next = d->head;
            d->head->prev = new;
            d->head = new;
        }
    }

    return d;
}

deque_t * popfront(deque_t * d)
{
    node_t * tmp;

    if(isempty(d)){
        printf("deque is already empty\n");
    }else{
        tmp = d->head;
        d->head = d->head->next;
        if(d->head == NULL){
            d->tail = NULL;
        }else{
            d->head->prev = NULL;
        }
        free(tmp);
    }

    return d;
}

deque_t * pushback(deque_t * d, int item)
{
    node_t * new;

    new = malloc(sizeof(node_t));
    if(new == NULL){
        printf("pushback failed memory allocation\n");
    }else{
        new->data = item;
        new->next = NULL;
        if(isempty(d)){
            new->prev = NULL;
            d->tail = new;
            d->head = d->tail;
        }else{
            new->prev = d->tail;
            d->tail->next = new;
            d->tail = new;
        }
    }

    return d;
}

deque_t * popback(deque_t * d)
{
    node_t * tmp;

    if(isempty(d)){
        printf("deque is already empty\n");
    }else{
        tmp = d->tail;
        d->tail = d->tail->prev;
        if(d->tail == NULL){
            d->head = NULL;
        }else{
            d->tail->next = NULL;
        }
        free(tmp);
    }

    return d;
}