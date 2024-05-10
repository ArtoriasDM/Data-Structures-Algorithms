void InsertionSort(int arr[], int dim){           // algoritmo di ordinamento con complessita' O(n^2)

    int i, j, tmp;

    for(i = 1; i < dim; i++){                     // Prendo un elemento dell'array e lo reinserisco a sinistra nella porzione ordinata
                                                  
        tmp = arr[i];                             // e mi fermo alla posizione corretta(versione che ordina in verso crescente)
        j = i - 1;
        while (j >= 0 && arr[j] > tmp)            // buona alternativa da utilizzare in dataset ristretti
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j +1] = tmp;
    }
}