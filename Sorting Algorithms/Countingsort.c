
#include <stdlib.h>

// algoritmo che opera l'ordinamento senza confronti, ma utilizzando un dominio ben definito di elementi e la loro distribuzione dentro l'array

// la complessità temporale è O(n + k), se il dominio è composto da k elementi tali che k >> n la complessità pratica è molto alta

void CountingSort(int arr[], int dim){

    int i, k, index;
    int * ist;

    k = arr[0];
    for(i = 1;i < dim; i++)                   // calcolo del range di valori utilizzati
    {
        if(arr[i] > k){
            k = arr[i];
        }
    }

    ist = calloc(k + 1, sizeof(int));        // costruzione dell'istogramma, tutti gli elementi inizialmente hanno 0 occorrenze
    if(ist == NULL){
        return;
    }

    for(i = 0; i < dim; i++){                // conteggio delle occorrenze
        ist[arr[i]]++;
    }

    index = 0;
    for(i = 0; i <= k; i++){                // ordinamento per conteggio
        while (ist[i] > 0)
        {
            arr[index] = ist[i];
            index++;
            ist[i]--;
        }
        
    }
}

int * CountingSort_s(int arr[], int dim){   // versione stabile

    int * result;
    int i, k, index, sum;
    int * ist;

    result = calloc(dim, sizeof(int));
    if(result == NULL){
        return NULL;
    }

    k = arr[0];
    for(i = 1;i < dim; i++)                 // calcolo del range di valori utilizzati
    {
        if(arr[i] > k){
            k = arr[i];
        }
    }

    ist = calloc(k + 1, sizeof(int));       // costruzione dell'istogramma, tutti gli elementi inizialmente hanno 0 occorrenze
    if(ist == NULL){
        return NULL;
    }
    for(i = 0; i < dim; i++){              // conteggio delle occorrenze
        ist[arr[i]]++;
    }

    sum = 0;
    for(i = 0; i <= k; i++){               // ricalcolo dell'istogramma 
        sum += ist[i];
        ist[i] = sum;
    }

    for(i = dim - 1; i >= 0; i--){         // riordinamento
        index = ist[arr[i]];
        result[index - 1] = arr[i];
        ist[arr[i]]--;
    }

}