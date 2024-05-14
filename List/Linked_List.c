#include <stdio.h>
#include <stdlib.h>

typedef struct ilist_s{

    int data;
    struct ilist_s * next;
    
}ilist_t;

ilist_t * append(ilist_t * head, int val){

    ilist_t * n, * el;

    n = malloc(sizeof(ilist_t));
    if(!n){
        printf("append: error in memory allocation/n");
    }else{

        n->data = val;
        n->next = NULL;
        if(head == NULL){
            head = n; 
        }else{
            el = head;
            while(el->next){
                el = el->next;
            }
            el->next = n;
        }
    }
    return head;
}

ilist_t * push(ilist_t * head, int val){

    ilist_t * n;

    n = malloc(sizeof(ilist_t));
    if(!n){
        printf("append: error in memory allocation/n");
    }else{
        n->data = val;
        n->next = NULL;
        if(head){
            n->next = head;
        }
        head = n;
    }

    return head;
}

ilist_t * pop(ilist_t * head){

    ilist_t * el;

    if(head == NULL){
        printf("List is empty: impossible to execute pop\n");
    }else{
        el = head;
        head = head->next;
        free(el);
    }

    return head;
}

int list_lenght(ilist_t * head){

    int lenght;
    ilist_t * el;

    lenght = 0;
    el = head;
    while(el){
        lenght++;
        el = el->next;
    }

    return lenght;
}

void display(ilist_t * head){

    if(head){
        printf("%d ", head->data);
        display(head->next);
    }else  
        printf("\n");
        
}