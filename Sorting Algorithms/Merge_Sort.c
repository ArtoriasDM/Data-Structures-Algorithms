
#include <stdlib.h>


void merge(int arr[], int p, int q, int r){      // strategia Divide-Et-Impera, vogliamo dividere l'array A[p,...,r]

    int * L, * R;                                // in due slices A[p,...,q] e A[q+1,...,r] da ordinare separatamente
    int len1, len2, i, j, k;

    len1 = q - p + 1;
    len2 = r - q;\

    L = malloc(len1 * sizeof(int));              // abbiamo una complessita' spaziale ø(n) dovuta ai due buffer
    R = malloc(len2 * sizeof(int));

    for(i = 0; i < len1; i++){
        L[i] = arr[p + i];
    }
    for (j = 0; j < len2; j++){
        R[j] = arr[q + j + 1];
    }

    i = 0;
    j = 0;
    k = p;
                
    while (i < len1 && j < len2) {               // e una complessita' temporale ø(n) per copia e ordinamento
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < len1) {                           // reinseriamo eventuali valori in eccesso
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < len2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void MergeSort(int arr[], int p, int r){       // complessita' temporale ø(nlog(n))

    int q, tmp;

    if (p < (r - 1))
    {   
        q = (r + p) / 2;                        // dividiamo l'array in maniera ricorsiva partendo da sinistra
        MergeSort(arr, p, q);                   // finche' non avremo sotto-array da massimo due elementi
        MergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
    }else{

        if (arr[p] > arr[r])                    // Se l'array contiene meno di tre elementi lo ordiniamo on-place
        {
            tmp = arr[r];
            arr[r] = arr[p];
            arr[p] = tmp;
        }
        
    }
    
}
