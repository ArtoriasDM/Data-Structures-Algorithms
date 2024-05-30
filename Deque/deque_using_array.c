#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct deque_s {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} deque_t;

deque_t *init() {
    deque_t *d = (deque_t *)malloc(sizeof(deque_t));
    if (d == NULL) {
        printf("Failed memory allocation\n");
        return NULL;
    }
    d->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    if (d->data == NULL) {
        printf("Failed memory allocation\n");
        free(d);
        return NULL;
    }
    d->front = 0;
    d->rear = 0;
    d->size = 0;
    d->capacity = INITIAL_CAPACITY;
    return d;
}

int isempty(deque_t *d) {
    return d->size == 0;
}

int isfull(deque_t *d) {
    return d->size == d->capacity;
}

void resize(deque_t *d, int new_capacity) {
    int *new_data = (int *)malloc(new_capacity * sizeof(int));
    if (new_data == NULL) {
        printf("Failed memory allocation during resize\n");
        return;
    }
    for (int i = 0; i < d->size; i++) {
        new_data[i] = d->data[(d->front + i) % d->capacity];
    }
    free(d->data);
    d->data = new_data;
    d->front = 0;
    d->rear = d->size;
    d->capacity = new_capacity;
}

void push_front(deque_t *d, int item) {
    if (isfull(d)) {
        resize(d, d->capacity * 2);
    }
    d->front = (d->front - 1 + d->capacity) % d->capacity;
    d->data[d->front] = item;
    d->size++;
}

void push_back(deque_t *d, int item) {
    if (isfull(d)) {
        resize(d, d->capacity * 2);
    }
    d->data[d->rear] = item;
    d->rear = (d->rear + 1) % d->capacity;
    d->size++;
}

void pop_front(deque_t *d) {
    if (isempty(d)) {
        printf("Deque is already empty\n");
        return;
    }
    d->front = (d->front + 1) % d->capacity;
    d->size--;
    if (d->size > 0 && d->size == d->capacity / 4) {
        resize(d, d->capacity / 2);
    }
}

void pop_back(deque_t *d) {
    if (isempty(d)) {
        printf("Deque is already empty\n");
        return;
    }
    d->rear = (d->rear - 1 + d->capacity) % d->capacity;
    d->size--;
    if (d->size > 0 && d->size == d->capacity / 4) {
        resize(d, d->capacity / 2);
    }
}

void free_deque(deque_t *d) {
    if (d) {
        free(d->data);
        free(d);
    }
}

