#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_INITIAL_SIZE 10

typedef struct bucket_s
{
    char * key;
    int data;
    struct bucket_s * next;
}bucket_t;

typedef struct 
{
    int size;
    int count;
    bucket_t **table;
}HashTable;

bucket_t * CreateNewNode(int item, char * key)
{
    bucket_t * new;

    new = malloc(sizeof(bucket_t));

    if(new == NULL){
        printf("Failed memory allocation\n");
    }else{
        new->data = item;
        new->key = strdup(key);
        new->next = NULL;
    }

    return new;
}

HashTable * __init__()
{
    HashTable * new_table;
    int i;

    new_table = malloc(sizeof(HashTable));

    if(new_table = NULL){
        printf("failed memory allocation\n");
    }else{
        new_table->size = HT_INITIAL_SIZE;
        new_table->count = 0;
        new_table->table = malloc(sizeof(bucket_t *) * HT_INITIAL_SIZE);
        if(new_table->table = NULL){
            printf("failed memory allocation\n");
            free(new_table);
        }else{
            for(i = 0; i < HT_INITIAL_SIZE; i++){
                new_table->table[i] = NULL;
            }
        }
    }

    return new_table;
}

void resize(HashTable * ht, int new_size)
{
    int old_size, i, index;
    bucket_t **old_table;
    bucket_t * curr, * next, * el;

    old_size = ht->size;
    old_table = ht->table;

    ht->table = malloc(sizeof(bucket_t *) * new_size);

    if(ht->table == NULL){
        printf("failed memory allocation\n");
        ht->table = old_table;
        return;
    }

    for(i = 0; i < new_size; i++){
        ht->table[i] = NULL;
    }

    for(i = 0; i < old_size; i++){                // to be tested
        curr = old_table[i];
        while(curr != NULL){
            next = curr->next;
            index = rehash(curr->key);              // same algorithm as hash(key)
            curr->next = NULL;
            if(ht->table[index] == NULL){
                ht->table[index] = curr;
            }else{
                el = ht->table[index];
                while(el->next != NULL){
                    el = el->next;
                }
                el->next = curr;
            }
            curr = next;
        }
    }
    free(old_table);
    ht->size = new_size;
}

void Insert(HashTable * hash_table, char * key, int val)
{
    int index, load_fac;
    bucket_t * new;

    load_fac = hash_table->count * 100 / hash_table->size;

    if(load_fac > 70){                     
        resize(hash_table, hash_table->size * 2);           // logic and complexity need some adjustement
    }

    index = hash(key);                                      // to be defined
    new = CreateNewNode(val, key);
    
    if(new){
        if(hash_table->table[index] == NULL){
            hash_table->table[index] = new;
        }else{
            new->next = hash_table->table[index];
            hash_table->table[index] = new;
        }
        hash_table->count++;
    }
}

int search(HashTable * hash_table, char * key)
{
    int index;
    bucket_t * current;

    index = hash(key);
    current = hash_table->table[index];

    while(current != NULL){
        if(strcmp(key, current->key) == 0){
            return current->data;
        }
        current = current->next;
    }

    return -1;
}

void delete(HashTable * hash_table, char * key)
{
    int index, load_fac;
    bucket_t * del, * prev;

    load_fac = hash_table->count * 100 / hash_table->size;

    if(load_fac < 10 && hash_table->size > HT_INITIAL_SIZE){
        resize(hash_table, hash_table->size / 2);                  // logic and complexity need some adjustement
    }

    index = hash(key);
    prev = NULL;
    del = hash_table->table[index];

    while(del != NULL && strcmp(key, del->key) != 0){
        prev = del;
        del = del->next; 
    }

    if(del == NULL){
        return;
    }

    if(prev == NULL){
        hash_table->table[index] = del->next;
    }else{
        prev->next = del->next;
    }

    free(del->key);
    free(del);
    hash_table->count--;
}