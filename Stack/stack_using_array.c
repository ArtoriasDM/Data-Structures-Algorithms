
#include <stdio.h>
#include <stdlib.h>

#define STANDARD_LENGHT 100                                     // buona alternativa per evitare di sovraccaricare la cache, può avere senso se non si fanno troppe 

typedef struct stack_s                                          // riallocazioni in memoria
{
    int * data;
    int dim;
    int top;
}stack_t;

void __init__(stack_t * stack){

    stack->dim = STANDARD_LENGHT;
    stack->data = malloc(sizeof(int) * stack->dim);
    if(stack->data == NULL)
        printf("__init__ failed memory allocation\n");
    else
        stack->top = -1;
}

int is_empty(stack_t * stack){
    return stack->top == -1;
}

int is_full(stack_t * stack){
    return stack->top == stack->dim - 1;
}

void resize(stack_t * stack){

    stack->data = realloc(stack->data, sizeof(int) * (stack->dim + STANDARD_LENGHT));
    if(stack->data == NULL){
        printf("resize failed memory allocation\n");
        return;
    }
    stack->dim += STANDARD_LENGHT;
}

void push(stack_t * stack, int n){

    if(is_full(stack)){
        resize(stack);
    }
    (stack->top)++;
    stack->data[stack->top] = n;
}

void pop(stack_t * stack){

    if(is_empty(stack)){
        printf("stack underflow\n");
        return;
    }
    (stack->top)--;
}





