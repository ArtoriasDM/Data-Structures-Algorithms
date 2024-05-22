#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    int data;
    struct node_s * next;
}node_t;

typedef struct queue_s
{
    node_t * head;
    node_t * tail;
}queue_t;

void __init__(queue_t * queue)
{
    queue = malloc(sizeof(queue_t));
    if (queue)
    {
        queue->head = NULL;
        queue->tail = NULL;
        return;
    }
    printf("__init__ failed memeory allocation\n");
}

int isempty(queue_t * queue)
{
    return (queue->head == NULL && queue->tail == NULL);
}

void enqueue(queue_t * queue, int val)
{
    node_t * new;

    new = malloc(sizeof(node_t));
    if(new == NULL){
        printf("enque failed memory allocation\n");
        return;
    }
    new->data = val;
    new->next = NULL;
    if(queue->tail == NULL && queue->head == NULL){
        queue->tail = new;
        queue->head = new;
    }else{
        queue->tail->next = new;
        queue->tail = new;
    }
}

int dequeue(queue_t * queue)
{
    node_t * tmp;
    int val;

    if(queue->head == NULL){
        printf("queue is already empty");
        return -1;
    }
    tmp = queue->head;
    queue->head = queue->head->next;
    int val = tmp->data;
    if(queue->head == NULL)
        queue->tail == NULL;
    free(tmp);

    return val;
}