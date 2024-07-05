#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int * array;
    int dim;
    int count;
}Heap;

Heap * __init__(int * arr, int dim)
{
    Heap * new;
    int i;

    new = malloc(sizeof(Heap));
    if(!new)
    {
        printf("Failed memory allocation\n");
        return NULL;
    }

    new->array = arr;
    new->count = dim;
    new->dim = dim;

    for(i = new->dim / 2; i >= 0; i--)
    {
        Heapify(new, i);
    }

    return new;
}

void Heapify(Heap * h, int index)
{
    int posmax, tmp;

    if((2 * index + 1) < h->dim && h->array[2 * index + 1] > h->array[index]){
        posmax = 2 * index + 1;
    }else{
        posmax = index;
    }

    if(2 * index + 2 < h->dim && h->array[2 * index + 2] > h->array[posmax])
    {
        posmax = 2 * index + 2;
    }

    if(posmax != index)
    {
        tmp = h->array[index];
        h->array[index] = h->array[posmax];
        h->array[posmax] = tmp;
        Heapify(h, posmax);
    }
}

int pop(Heap * h)
{
    int max;

    if(h->count < 1)
    {
        return -1;
    }

    max = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--;
    Heapify(h, 0);

    return max;
}

void Insert(Heap * h, int key)
{
    int i, tmp;

    h->count++;
    h->array[h->count - 1] = key;
    i = h->count - 1;

    while(i > 0 && h->array[(i - 1) / 2] < h->array[i])
    {
        tmp = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = h->array[i];
        h->array[i] = tmp;
        i = (i - 1) / 2;
    }
}

void HeapSort(int * arr, int dim)
{
    Heap * h = __init__(arr, dim);
    int tmp, i;

    for(i = h->dim - 1; i >= 1; i--)
    {
        tmp = h->array[0];
        h->array[0] = h->array[i];
        h->array[i] = tmp;
        Heapify(h, 0);
    }
}