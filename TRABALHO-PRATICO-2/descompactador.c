#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arvore.h"
#include "bitmap.h"

#define tam_ASCII 256
#define UM_MEGA 8*1024*1024


void Descompacta(char* caminhoComp) {
    FILE* entrada = fopen(caminhoComp, "rb");
    if (!entrada) {
        perror("Erro ao abrir o arquivo compactado");
        exit(1);
    }

    // Lê o conteúdo inteiro do arquivo .comp para o bitmap
    bitmap* bm = bitmapInit(UM_MEGA);
    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), 1, entrada) == 1) {
        for (int i = 7; i >= 0; i--) {
            bitmapAppendLeastSignificantBit(bm, (byte >> i) & 1);
        }
    }

    fclose(entrada);

    // Reconstrói a árvore a partir do bitmap
    int pos = 0;
    Arvore* arv = reconstroiArvore(bm, &pos);

    char nomeSaida[256];
    sprintf(nomeSaida, "%s.txt", caminhoComp);
    FILE* saida = fopen(nomeSaida, "w");
    if (!saida) {
        perror("Erro ao criar o arquivo de saída");
        exit(1);
    }

    decodificaArvore(arv, bm, saida);

    fclose(saida);
    bitmapLibera(bm);
    liberaArvore(arv);
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Nao foi passado o caminho do arquivo, saindo.\n");
        return 1;
    }
    
    Descompacta(argv[1]);
   
    return 0;
}