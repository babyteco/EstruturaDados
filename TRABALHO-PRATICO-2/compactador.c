#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arvore.h"
#include "bitmap.h"

#define tam_ASCII 256
#define UM_MEGA 8*1024*1024

Lista *preencheListaArvores(char *caminho){
    FILE *arq = fopen(caminho, "rb");

    if(!arq){
        printf("nao foi possivle abrir o arquivo de caminho %s\n", caminho);
        return NULL;
    }

    int *vetFrequency = (int*) calloc(tam_ASCII, sizeof(int));
    int byte;

    Lista *lista = criaLista();

    while ((byte = fgetc(arq)) != EOF) {
        vetFrequency[byte]++;

        if (vetFrequency[byte] == 1){
            Arvore *arv = criaArvore(byte, NULL, NULL, 0);
            lista = insereArvoreNaLista(lista, arv);
        } else {
            atualizaFrequencia(buscaArvore(lista, byte), vetFrequency[byte]);
        }
        
    }

    fclose(arq);
    free(vetFrequency);

    return lista;
}

void escreveBinario(char *caminho, bitmap *bm, char **tabela){
    char nomeSaida[100];
    sprintf(nomeSaida, "%s.comp", caminho);
    FILE *saida = fopen(nomeSaida, "wb");

    if (!saida) {
        perror("Erro ao criar arquivo de saída");
        exit(1);
    }

    // grava o bitmap com o cabeçalho
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), (bitmapGetLength(bm)+7)/8, saida);

    FILE *entrada = fopen(caminho, "rb");
    if (!entrada) {
        perror("Erro ao abrir arquivo de entrada");
        exit(1);
    }

    // cria um novo bitmap para o conteúdo codificado
    bitmap *bmConteudo = bitmapInit(UM_MEGA);

    int c;
    while ((c = fgetc(entrada)) != EOF) {
        char *codigo = tabela[(unsigned char)c];
        for (int i = 0; codigo[i] != '\0'; i++) {
            bitmapAppendLeastSignificantBit(bmConteudo, codigo[i] - '0');
        }
    }

    // grava o conteúdo codificado no arquivo de saída
    fwrite(bitmapGetContents(bmConteudo), sizeof(unsigned char), (bitmapGetLength(bmConteudo)+7)/8, saida);

    fclose(entrada);
    fclose(saida);
    bitmapLibera(bmConteudo);
    bitmapLibera(bm);
}

void Compacta(char *caminho){
    Lista *lista = preencheListaArvores(caminho);

    if (!lista){
        return;
    }

    lista = obtemListaIdeal(lista);
    Arvore *arvoreIdeal = getArvore(lista);

    char **tabela = (char**) calloc(256, sizeof(char*));
    char codigo[256] = "\0";
    tabela = preencheTabelaHuffman(arvoreIdeal, tabela, codigo);
    
    bitmap *bm = bitmapInit(UM_MEGA);
    escreveCabecalho(arvoreIdeal, bm);
    escreveBinario(caminho, bm, tabela);
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Nao foi passado o caminho do arquivo, saindo.\n");
        return 1;
    }
    
    Compacta(argv[1]);
   
    return 0;
}