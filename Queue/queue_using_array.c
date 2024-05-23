#include <stdio.h>
#include <stdlib.h>

#define STANDARD_LENGHT 100

typedef struct queue_s
{
    int capacity;                    // per questa implementazione è necessario conoscere sempre la dimensione dell'area di memoria
    int size;                        // e della quantità di spazio occupato
    int * data;
    int head;
    int tail;                        // in questo caso tail indica lo slot in cui inserire un nuovo elemento
}queue_t;


void __init__(queue_t * q)
{
    q = malloc(sizeof(queue_t));
    if(q == NULL){
        printf("__init__ failed memory allocation");
        return;
    }
    q->capacity = STANDARD_LENGHT;
    q->data = malloc(sizeof(int) * q->capacity);
    if(q->data == NULL){
        printf("__init__ failed memory allocation\n");
        return;
    }
    q->size = 0;
    q->head = 0;
    q->tail = q->head;
}

int isempty(queue_t * q)
{
    return (q->size == 0);
}

int isfull(queue_t * q)
{
    return(q->size == q->capacity);
}

int dequeue(queue_t * q)
{
    int item;

    if(isempty(q)){
        printf("queue is already empty\n");
        return -1;
    }
    item = q->data[q->head];
    q->size = q->size -1;
    q->head = (q->head + 1) % q->capacity;

    return item;
}

void enqueue(queue_t * q, int item)
{
    if(isfull(q)){
        resize(q);
    }
    q->tail = (q->tail + 1) % q->capacity;
    q->data[q->tail] = item;
    q->size = q->size + 1;
}

void resize(queue_t * q)
{
    int * resized_arr;
    int new_capacity, current_size, i;

    new_capacity = q->capacity * 2;
    current_size = q->size;
    resized_arr = malloc(sizeof(int) * new_capacity);
    if(resized_arr == NULL){
        printf("resize failed memory allocation\n");
        return;
    }
    for(i = 0; i < q->size; i++){
        resized_arr[i] = dequeue(q);
    }
    free(q->data);
    q->data = resized_arr;
    q->capacity = new_capacity;
    q->head = 0;
    q->size = current_size;
    q->tail = q->size - 1;
}



