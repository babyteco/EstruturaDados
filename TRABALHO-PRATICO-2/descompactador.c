#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"
#include "bitmap.h"

#define tam_ASCII 256
#define UM_MEGA 8*1024*1024

void derivaNomeSaida(const char* caminhoComp, char* nomeSaida, size_t cap) {
    const char *extensao = ".txt";  // padrão

    // Procura pela última ocorrência de ".txt.comp" ou ".png.comp"
    const char *txtComp = strstr(caminhoComp, ".txt.comp");
    const char *pngComp = strstr(caminhoComp, ".png.comp");

    if (txtComp && strcmp(txtComp, ".txt.comp") == 0) {
        extensao = ".txt";
    } else if (pngComp && strcmp(pngComp, ".png.comp") == 0) {
        extensao = ".png";
    }

    // Cria o nome final adicionando a extensão original no final
    snprintf(nomeSaida, cap, "%s%s", caminhoComp, extensao);
}

void Descompacta(char* caminhoComp) {
    FILE* entrada = fopen(caminhoComp, "rb");
    if (!entrada) { perror("Erro ao abrir o arquivo compactado"); exit(1); }

    fseek(entrada, 0, SEEK_END);
    long tamArquivo = ftell(entrada);
    rewind(entrada);

    if (tamArquivo <= 0) {
        char nomeSaida[256];
        derivaNomeSaida(caminhoComp, nomeSaida, sizeof(nomeSaida));
        FILE* saidaVazio = fopen(nomeSaida, "wb");
        if (saidaVazio) fclose(saidaVazio);
        fclose(entrada);
        return;
    }

    bitmap* bm = bitmapInit((unsigned int)tamArquivo * 8);

    unsigned char byte;
    while (fread(&byte, 1, 1, entrada) == 1) {
        for (int i = 7; i >= 0; i--) {
            bitmapAppendLeastSignificantBit(bm, (byte >> i) & 1);
        }
    }
    fclose(entrada);

    int pos = 0;
    Arvore* arv = reconstroiArvore(bm, &pos);

    int originalSize = 0;
    for (int i = 0; i < 32; ++i) {
        originalSize = (originalSize << 1) | bitmapGetBit(bm, pos++);
    }

    int padCabecalho = (8 - (pos % 8)) % 8;
    pos += padCabecalho;

    char nomeSaida[256];
    derivaNomeSaida(caminhoComp, nomeSaida, sizeof(nomeSaida));
    FILE* saida = fopen(nomeSaida, "wb");
    if (!saida) {
        perror("Erro ao criar o arquivo de saída");
        exit(1);
    }

    decodificaBitmapComArvore(bm, pos, arv, saida, originalSize);

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