// algoritmo di ordinamento che ordina senza spazio ausiliario, complessita' temporale ø(nlog(n))

// opera l'ordinamento su uno slice A[low,..., high] tramite un elemento arbitrario detto pivot

int PartitionLomuto(int arr[], int low, int high){

    int pivot, tmp, i, j;

    pivot = arr[high];
    i = low - 1;

    for ( j = low; j < high; j++)
    {
        if(arr[j] <= pivot){
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;                                        // ritorna l'indice dell'ultimo elemento <= del pivot, escluso il pivot stesso, l'elemento restituito sara' gia' nella sua posizione finale
    
}

int PartitionHoare(int arr[], int low, int high){       // alternativa che esegue 1/3 degli scambi ripsetto a Lomuto

    int pivot, tmp, i, j;

    pivot = arr[low];
    i = low - 1;
    j = high + 1;

    while(1)
    {
        do
        {
            i++;
        } while (arr[i] < pivot);

        do
        {
            j--;
        } while (arr[j] > pivot);
        
        if(i < j){
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }else{  
            return j;                                   // l'elemento restituito sara' l'ultimo <= a pivot, pivot incluso
        }
    }
}

void QuickSort_L(int arr[], int low, int high){

    int pivot;

    if(low < high)
    {
        pivot = PartitionLomuto(arr, low, high);
        QuickSort_L(arr, low, pivot - 1);
        QuickSort_L(arr, pivot + 1, high);
    }
}

void QuickSort_H(int arr[], int low, int high){

    int pivot;

    if(low < high)
    {
        pivot = PartitionHoare(arr, low, high);
        QuickSort_H(arr, low, pivot);
        QuickSort_H(arr, pivot + 1, high);
    }
}

