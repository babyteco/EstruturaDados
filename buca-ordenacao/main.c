//A diferença foi clara entre o algoritmo de ordenação bubble ou o quick
//enquanto o bubble demorou 23 segundos para ordenar um vetor de 10000 inteiros, o quick demorou menos de 1 segundo

#include <stdio.h>
#include <stdlib.h>

#define max_tam_vet 100000

void bubbleSort(int *vet, int tamanho);

void quickSort(int *vet, int firstIndex, int lastIndex);

int main(){
    int vet[max_tam_vet];
    for (int i = 0; i < max_tam_vet; i++){
        vet[i] = rand();
    }
    
    for (int i = 0; i < max_tam_vet; i++){
        printf("vet[%d]: %d\n", i, vet[i]);
    }
    

    // bubbleSort(vet, max_tam_vet);
    quickSort(vet, 0, max_tam_vet - 1);


    for (int i = 0; i < max_tam_vet; i++){
        printf("vet[%d]: %d\n", i, vet[i]);
    }

    return 0;
}

void bubbleSort(int *vet, int tamanho){
    for (int i = 0; i < tamanho - 1; i++){
        for (int j = 0; j < tamanho - i - 1; j++){
            if (vet[j] > vet[j+1]){
                int temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
            }
        }
    }
}

void quickSort(int *vet, int firstIndex, int lastIndex){
    if (lastIndex <= firstIndex){
        return;
    }
    
    int j = firstIndex;
    int i = j - 1;


    int pivot = vet[lastIndex];
    while (j < lastIndex){
        if (vet[j] < pivot){
            i++;
            int temp = vet[i];
            vet[i] = vet[j];
            vet[j] = temp;
        }
        
        j++;
    }

    i++;
    int temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;

    quickSort(vet, firstIndex, i - 1);
    quickSort(vet, i + 1, lastIndex);
}