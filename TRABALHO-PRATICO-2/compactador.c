#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        unsigned char u = (unsigned char) byte;
        vetFrequency[u]++;

        if (vetFrequency[u] == 1){
            Arvore *arv = criaArvore(u, NULL, NULL, 1);
            lista = insereArvoreNaLista(lista, arv);
        } else {
            atualizaFrequencia(buscaArvore(lista, u), vetFrequency[u]);
        }
        
    }

    fclose(arq);
    free(vetFrequency);

    return lista;
}

void escreveBinario(const char *caminho, bitmap *bmCabecalho, char **tabela){
    char nomeSaida[512];
    sprintf(nomeSaida, "%s.comp", caminho);

    FILE *saida = fopen(nomeSaida, "wb");
    if (!saida) {
        perror("Erro ao criar arquivo de saída");
        exit(1);
    }

    fwrite(bitmapGetContents(bmCabecalho),
           1,
           (bitmapGetLength(bmCabecalho)+7)/8,
           saida);

    bitmapLibera(bmCabecalho);

    FILE *entrada = fopen(caminho, "rb");
    if (!entrada) {
        perror("Erro ao abrir arquivo de entrada");
        fclose(saida);
        exit(1);
    }

    bitmap *bmConteudo = bitmapInit(UM_MEGA);

    int ch;
    while ((ch = fgetc(entrada)) != EOF) {
        unsigned char u = (unsigned char) ch;
        const char *codigo = tabela[u];
        size_t len = strlen(codigo);
        size_t offset = 0;

        while (len > 0) {
            unsigned int livre = bitmapGetMaxSize(bmConteudo) - bitmapGetLength(bmConteudo);
            if (livre == 0) {
                // bloco cheio -> flush para o arquivo
                fwrite(bitmapGetContents(bmConteudo),
                       1,
                       (bitmapGetLength(bmConteudo)+7)/8,
                       saida);
                bitmapLibera(bmConteudo);
                bmConteudo = bitmapInit(UM_MEGA);
                livre = bitmapGetMaxSize(bmConteudo);
            }

            unsigned int escrever = (len < livre) ? (unsigned int)len : livre;

            for (unsigned int i = 0; i < escrever; i++) {
                bitmapAppendLeastSignificantBit(bmConteudo, codigo[offset + i] - '0');
            }
            offset += escrever;
            len    -= escrever;
        }
    }

    if (bitmapGetLength(bmConteudo) > 0) {
        fwrite(bitmapGetContents(bmConteudo),
               1,
               (bitmapGetLength(bmConteudo)+7)/8,
               saida);
    }

    bitmapLibera(bmConteudo);
    fclose(entrada);
    fclose(saida);
}

void Compacta(char *caminho){
FILE *test = fopen(caminho, "rb");
    if (!test) {
        perror("Nao foi possivel abrir o arquivo de entrada");
        return;
    }
    fseek(test, 0, SEEK_END);
    long tam = ftell(test);
    fclose(test);

    if (tam == 0) {
        char nomeSaida[100];
        sprintf(nomeSaida, "%s.comp", caminho);
        FILE *saida = fopen(nomeSaida, "wb");
        if (saida) fclose(saida);
        return;
    }

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

    int originalSize = somaFrequenciasLista(lista);
    
    // Escreve 32 bits do tamanho original no próprio bitmap de cabeçalho
    for (int i = 31; i >= 0; --i) {
        bitmapAppendLeastSignificantBit(bm, (originalSize >> i) & 1);
    }

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