#include <stdio.h>
#include <stdlib.h>

int *contaFrequenciaCaracter(char *caminho){
    FILE *arq = fopen(caminho, "r");
}

void Compacta(char *caminho){
    FILE *arq = fopen(caminho, "r");
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Nao foi passado o caminho do arquivo, saindo.\n");
        return 1;
    }
    
    Compacta(argv[1]);
   
    return 0;
}