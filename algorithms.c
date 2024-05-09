
#include <stdlib.h>
#include <stdio.h>

void InsertionSort(int arr[], int dim){           // algoritmo di ordinamento con complessita' O(n^2)

    int i, j, tmp;

    for(i = 1; i < dim; i++){                     // Prendo un elemento dell'array e lo reinserisco a sinistra nllea porzione ordinata
                                                  
        tmp = arr[i];                             // e mi fermo alla posizione corretta(versione che ordina in verso crescente)
        j = i - 1;
        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j +1] = tmp;
    }
}

void merge(int arr[], int p, int q, int r){      // strategia Divide-Et-Impera, vogliamo dividere l'array A[p,...,r]

    int * L, * R;                                // in due slices A[p,...,q] e A[q+1,...,r] da ordinare separatamente
    int len1, len2, i, j, k;

    len1 = q - p + 1;
    len2 = r - q;\

    L = malloc(len1 * sizeof(int));              // abbiamo una complessita' spaziale ø(n) dovuta ai due buffer
    R = malloc(len2 * sizeof(int));

    for(i = 0; i < len1; i++)
        L[i] = arr[p + i];
    for (j = 0; j < len2; j++)
        R[j] = arr[q + j + 1];
    
    i = 0;
    j = 0;

    for ( k = p; k <= r; k++)                    // e una complessita' temporale ø(n) per copia e ordinamento
    {
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
    }

    free(L);
    free(R);
}

void MergeSort(int arr[], int p, int r){

    int q, tmp;

    if (p < (r - 1))
    {   
        q = (r + p) / 2;
        MergeSort(arr, p, q);
        MergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
    }else{

        if (arr[p] > arr[r])
        {
            tmp = arr[r];
            arr[r] = arr[p];
            arr[p] = tmp;
        }
        
    }
    
}

int main(){

    int vec[] = {1, 0, 5, 6, 8, 7};
    int i;

    for (i = 0; i < 6; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");

    MergeSort(vec, 0, 5);

    for (i = 0; i < 6; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");

    return 0;
    
}