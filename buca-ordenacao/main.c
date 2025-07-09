#include <stdio.h>
#include <stdlib.h>

#define max_tam_vet 100

void bubbleSort(int *vet, int tamanho);

void quickSort(int *vet, int tamanho);

int main(){
    int vet[max_tam_vet];
    for (int i = 0; i < max_tam_vet; i++){
        vet[i] = rand();
    }
    
    for (int i = 0; i < 100; i++){
        printf("vet[%d]: %d\n", i, vet[i]);
    }
    

    bubbleSort(vet, max_tam_vet);

    for (int i = 0; i < 100; i++){
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

void quickSort(int *vet, int tamanho){

}