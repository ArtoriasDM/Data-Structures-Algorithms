#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_INITIAL_SIZE 8
#define EMPTY NULL
#define DELETED ((char*)-1)

typedef struct 
{
    int data;
    char * key;
}bucket_t;

typedef struct 
{
    int count;
    int size;
    bucket_t ** table;
}HashTable;

HashTable * __init__()
{
    HashTable * ht;
    int i;

    ht = malloc(sizeof(HashTable));

    if(ht == NULL){
        printf("failed memory allocation\n");
    }else{
        ht->count = 0;
        ht->size = HT_INITIAL_SIZE;
        ht->table = malloc(sizeof(bucket_t *) * HT_INITIAL_SIZE);
        if(ht->table == NULL){
            printf("failed memory allocation\n");
            free(ht);
        }else{
            for(i = 0; i < HT_INITIAL_SIZE; i++){
                ht->table[i] = EMPTY;
            }
        }
    }

    return ht;
}

bucket_t * CreateNode(char * key, int data)
{
    bucket_t * new;

    new = malloc(sizeof(bucket_t));

    if(new == NULL){
        printf("failed memory allocation\n");
    }else{
        new->data = data;
        new->key = strdup(key);
    }

    return new;
}

/* Non può essere implementato in questo modo, va adattato alle singole funzioni
int linear_probing(HashTable * ht, char * key)     
{
    int first_index, try;
    bucket_t * slot;

    first_index = hash(key);
    slot = ht->table[first_index];

    if(slot != EMPTY){
        try = first_index;
        do
        {
            try = (try + 1) % ht->size;
            slot = ht->table[try];
        } while (try != first_index && slot != EMPTY && slot->key != DELETED);   
    }

    if(try == index)
        return -1;
    return try;  
}
*/

int hash(char * key, int step, int table_size)               // hash algorithm with linear probing or quadratic probing
{
    int index;

    // hashing

    // index = (index + step) % table_size;                    linear probing

    return index;
}

void Insert(HashTable * ht, int data, char * key)
{
    bucket_t * new, * slot;
    int index, try, step;

    do 
    {   
        step = 0;
        index = hash(key, step, ht->size);                                      
        slot = ht->table[index];

        if (slot != EMPTY)
        {
            do
            {
                step++;
                try = hash(key, step, ht->size);
                slot = ht->table[try];
            } while (try != index && slot != EMPTY && strcmp(slot->key, DELETED) != 0);
        
            if(try == index){
                index = -1;
                resize(ht, ht->size * 2);
            }else{
                index = try;
            }
        }
    } while(index == -1);

    if(ht->table[index] == EMPTY){
        new = CreateNode(key, data);
        ht->table[index] = new;
    }else{
        ht->table[index]->data = data;
        ht->table[index]->key = strdup(key);
    }

    ht->count++;
}

void Delete(HashTable * ht, char * key)
{
    bucket_t * slot;
    int index, try, step;

    step = 0;
    index = hash(key, step, ht->size);
    slot = ht->table[index];

    if(slot == EMPTY || strcmp(slot->key, key) != 0){   
        step++;
        try = hash(key, step, ht->size);
        slot = ht->table[try];
        while(try != index && slot != EMPTY && strcmp(slot->key, key) != 0)
        {
            step++;
            try = hash(key, step, ht->size);
            slot = ht->table[try];
        }

        if(try == index){
            index = -1;
        }else
            index = try;
    }

    if(index != -1)
    {
        slot->key = strdup(DELETED);
        ht->count--;
    }
}

int Search(HashTable * ht, char * key)
{
    bucket_t * slot;
    int index, try, step;

    step = 0;
    index = hash(key, step, ht->size);
    slot = ht->table[index];

    if(slot == EMPTY || strcmp(slot->key, key) != 0){
        do
        {
            step++;
            try = hash(key, step, ht->size);
            slot = ht->table[try];
        } while (try != index && (slot == EMPTY || strcmp(slot->key, key) != 0));
        
        if(index == try){
            index = -1;
        }else{
            index = try;
        }
    }

    if(index == -1){
        printf("Item not found\n");
    }
    
    return ht->table[index]->data;
}