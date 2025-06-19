//
//  booked.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include "listaLeitores.h"
#include "listaLivros.h"
#include "recomendacoes.h"

typedef struct booked{
    ListaLeitores *listaLeitores;
    ListaLivros *catalogoLivros;
} Booked;

Booked *criaBooked(){
    Booked *b = (Booked*) malloc(sizeof(Booked));
    b->listaLeitores = criaListaLeitores();
    b->catalogoLivros = criaListaLivros();
    return b;
}

void leLivrosTxt(Booked *b){
    FILE *arq = fopen("Livros.txt", "r");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo Livros.txt\n");
        return;
    }
    
    char titulo[MAX_TAM_STRING];
    char autor[MAX_TAM_STRING];
    char genero[MAX_TAM_STRING];
    int ano;
    int id;
    while (5 == fscanf(arq, "%d;""%49[^;]""%49[^;]""%49[^;]""%d\n", &id, titulo, autor, genero, &ano)){
        Livro *l = criaLivro(titulo, autor, genero, ano, id);
        b->catalogoLivros = adicionaLivro(b->catalogoLivros, l);
    }
    fclose(arq);
}

void leLeitoresTxt(Booked *b){
    FILE *arq = fopen("Leitores.txt", "r");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo Leitores.txt\n");
        return;
    }
    
    char nome[MAX_TAM_STRING];
    int numAfinidades;
    int id;
    while (3 == fscanf(arq, "%d;""%49[^;]""%d", &id, nome, &numAfinidades)){
        char **generos = (char**) malloc(numAfinidades * sizeof(char*));
        for (int i = 0; i < numAfinidades; i++){
            generos[i] = (char*) malloc(MAX_TAM_STRING * sizeof(char));
        }

        for (int i = 0; i < numAfinidades; i++){
            fscanf(arq, "%49[^;]", generos[i]);
        }
        Leitor *l = criaLeitor(nome, generos, id, numAfinidades); 
        b->listaLeitores = adicionaLeitor(b->listaLeitores, l);
        
        for (int i = 0; i < numAfinidades; i++){
            free(generos[i]);
        }
        free(generos);
    }
    fclose(arq);
}

void comandosTxt(Booked *b){
    FILE *arq = fopen("Comandos.txt", "r");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo Comandos.txt\n");
        return;
    }
    int funcionalidade, param1, param2, param3;
    while (4 == fscanf(arq, "%d;""%d;""%d;""%d;", &funcionalidade, &param1, &param2, &param3)){
        Livro *livro = buscaLivro(b->catalogoLivros, param2);
        Leitor *leitor = buscaLeitor(b->listaLeitores, param1);
        if (livro == NULL || leitor == NULL){
            printf("Erro: Livro ou leitor nao encontrado (comandosTxt)\n");
            continue;
        }

        switch (funcionalidade)
        {
        case 1:
            adicionaLivroLido(leitor, livro);
            break;
        case 2:
            adicionaLivroDesejado(leitor, livro);
            break;
        case 3:
            printf("%s ", getNomeLeitor(buscaLeitor(b->listaLeitores, param1)));
            adicionaRecomendacaoDada(leitor, livro);
            break;
        case 4:
            aceitaRecomendacao(b->listaLeitores, param1, param2, param3);
            break;
        case 5:
            rejeitaRecomendacao(b->listaLeitores, param1, param2, param3);
            break;
        case 6:
            //1 se tiver, 0 se nao tiver
            livrosEmComum(b->listaLeitores, param1, param3);
            break;
            case 7:
            //1 se tiver, 0 se nao tiver
            preencheListaAfinidadesDiretas(b->listaLeitores);
            verificaSeTemAfinidade(b->listaLeitores, param1, param3);
            break;
        case 8:
            printf("Imprime toda a BookED\n");
            break;

        default:
            break;
        }
    }
    fclose(arq);
}

void liberaBooked(Booked *b){
    liberaListaLeitores(b->listaLeitores);
    liberaListaLivros(b->catalogoLivros);
    free(b);
}
