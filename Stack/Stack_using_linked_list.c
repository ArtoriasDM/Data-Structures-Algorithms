#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct stack_s{

    int data;
    struct stack_s * next;

}Stack;

void push(Stack * top, int val){

    Stack * new;

    new = malloc(sizeof(Stack));
    if(new){
        new->data = val;
        new->next = top;
        top = new;
    }else
        printf("Push: allocation error\n");
    
}

void pop(Stack * top){

    Stack * tmp;

    if(top == NULL){

        printf("Stack is already empty\n");

    }else{
        tmp = top;
        top = top->next;
        free(tmp);
    }
}

int peek(Stack * top){
    
    if(top == NULL){
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}

int empty(Stack * top){

    if(top == NULL)
        return TRUE;
    return FALSE;
}

void destroy(Stack * top){
    
    while(top)
        pop(top);
        
}