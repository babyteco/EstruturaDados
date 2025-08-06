#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define tam_ASCII 256

Lista *preencheListaArvores(char *caminho){
    FILE *arq = fopen(caminho, "r");

    if(!arq){
        printf("nao foi possivle abrir o arquivo de caminho %s\n", caminho);
        exit(1);
    }

    int *vetFrequency = (int*) calloc(tam_ASCII, sizeof(int));
    int byte;

    Lista *lista = criaLista();

    while ((byte = fgetc(arq)) != EOF) {
        if (vetFrequency[byte] == 0){
            Arvore *arv = criaArvore(byte, NULL, NULL, 0);
            lista = insereArvoreNaLista(lista, arv);
        }
        vetFrequency[byte]++;
        
        atualizaFrequencia(buscaArvore(lista, byte), vetFrequency[byte]);
    }

    fclose(arq);


    for (int i = 0; i < tam_ASCII; i++){
        
    }
    

    return lista;
}


void Compacta(char *caminho){
    

}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Nao foi passado o caminho do arquivo, saindo.\n");
        return 1;
    }
    
    Compacta(argv[1]);
   
    return 0;
}