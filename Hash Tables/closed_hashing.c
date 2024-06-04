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

void Insert(HashTable * ht, int data, char * key)
{
    bucket_t * new, * slot;
    int index, try;

    do 
    {
        index = hash(key);                                      // da rivedere per aggiungere logica sulle tombstone
        slot = ht->table[index];

        if (slot != EMPTY)
        {
            try = index;
            do
            {
                try = (try + 1) % ht->size;
                slot = ht->table[try];
            } while (try != index && slot != EMPTY);
        
            if(try == index){
                index = -1;
                resize(ht, ht->size * 2);
            }else{
                index = try;
            }
        }
    } while(index == -1);

    new = CreateNode(key, data);
    ht->table[index] = new;
    ht->count++;
}

void Delete(HashTable * ht, char * key)
{
    bucket_t * slot;
    int index, try;

    index = hash(key);
    slot = ht->table[index];

    if(strcmp(slot->key, key) != 0){   
        try = (index + 1) % ht->size;
        slot = ht->table[try];
        while(try != index && slot != EMPTY && strcmp(slot->key, key) != 0)
        {
            try = (try + 1) % ht->size;
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