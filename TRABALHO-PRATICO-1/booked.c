//
//  booked.c
//
//  Created by Matheus Gon Zortea on 16/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "listaLeitores.h"
#include "listaLivros.h"
#include "recomendacoes.h"
#include "leitor.h"
#include "livro.h"
#include "booked.h"

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
    
    char linha[50];
    fgets(linha, sizeof(linha), arq);
    while (fscanf(arq, "%d;%49[^;];%49[^;];%49[^;];%d%*c", &id, titulo, autor, genero, &ano) == 5){
        Livro *l = criaLivro(titulo, autor, genero, ano, id);
        b->catalogoLivros = adicionaLivro(b->catalogoLivros, l);
        //imprimeLivro(l);
    }
    fclose(arq);
}

void leLeitoresTxt(Booked *b){
    FILE *arq = fopen("Leitores.txt", "r");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo Leitores.txt\n");
        return;
    }
    
    char linha[50];
    fgets(linha, sizeof(linha), arq);

    char nome[MAX_TAM_STRING];
    int numAfinidades;
    int id;
    while (fscanf(arq, "%d;%49[^;];%d%*c", &id, nome, &numAfinidades) == 3){
        //criar array de generos
        char **generos = (char**) malloc(numAfinidades * sizeof(char*));
        for (int i = 0; i < numAfinidades; i++){
            generos[i] = (char*) malloc(MAX_TAM_STRING * sizeof(char));
        }

        for (int i = 0; i < numAfinidades; i++) {
            if (i < numAfinidades - 1) {
                // para todos exceto o último: consome ';' e lê até antes do próximo ';'
                fscanf(arq, " %49[^;];", generos[i]);
            } else {
                // último gênero: lê até antes do '\n'
                fscanf(arq, " %49[^\n]\n", generos[i]);
            }
        }
        Leitor *l = criaLeitor(nome, generos, id, numAfinidades); 
        if (l != NULL){
            b->listaLeitores = adicionaLeitor(b->listaLeitores, l);
        } else printf("nao foi possivel criar leitor\n");
        
        //liberar array de generos
        for (int i = 0; i < numAfinidades; i++){
            free(generos[i]);
        }
        free(generos);
    }
    fclose(arq);
    preencheListaAfinidadesDiretas(b->listaLeitores);
}

void comandosTxt(Booked *b){
    FILE *arq = fopen("Comandos.txt", "r");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo Comandos.txt\n");
        return;
    }
    
    FILE *saida = fopen("Saida.txt", "w");
    
    char linha[50];
    fgets(linha, sizeof(linha), arq);

    int funcionalidade, param1, param2, param3;
    while (fscanf(arq, "%d;%d;%d;%d%*c", &funcionalidade, &param1, &param2, &param3) == 4){
        Livro *livro = buscaLivro(b->catalogoLivros, param2);
        Leitor *leitor = buscaLeitor(b->listaLeitores, param1);

        switch (funcionalidade)
        {
        case 1:
            adicionaLivroLido(leitor, livro, saida);
            break;
        case 2:
            adicionaLivroDesejado(leitor, livro, saida);
            break;
        case 3:
            fprintf(saida, "%s ", getNomeLeitor(leitor));
            Leitor *destinatario = buscaLeitor(b->listaLeitores, param3);
            if (destinatario == NULL){
                printf("Erro: Destinatário não encontrado\n");
                break;
            }
            adicionaRecomendacaoDada(destinatario, livro, leitor, saida);
            break;
        case 4:
            aceitaRecomendacao(b->listaLeitores, param1, param2, param3, saida);
            break;
        case 5:
            rejeitaRecomendacao(b->listaLeitores, param1, param2, param3, saida);
            break;
        case 6:
            //1 se tiver, 0 se nao tiver
            livrosEmComum(b->listaLeitores, param1, param3, saida);
            break;
        case 7:
            // for (int i = 1; i < 4; i++){
            //     fprintf(saida, "\n\n\nConstando afinidades diretas de %s\n", getNomeLeitor(buscaLeitor(b->listaLeitores, i)));
            //     imprimeLeitores(getListaAfinidade(buscaLeitor(b->listaLeitores, i)), saida);
            //     fprintf(saida, "acabou a lista de %s\n\n\n", getNomeLeitor(buscaLeitor(b->listaLeitores, i)));
            // }
            if(verificaSeTemAfinidade(b->listaLeitores, param1, param3) == 1){
                fprintf(saida, "Existe afinidade entre %s e %s\n", getNomeLeitor(leitor), getNomeLeitor(buscaLeitor(b->listaLeitores, param3)));
            } else{
                fprintf(saida, "Nao existe afinidade entre %s e %s\n", getNomeLeitor(leitor), getNomeLeitor(buscaLeitor(b->listaLeitores, param3)));
            }
            break;
        case 8:
            fprintf(saida, "Imprime toda a BookED\n");
            imprimeLeitores(b->listaLeitores, saida);
            break;

        default:
            break;
        }
    }
    fclose(arq);
    fclose(saida);
}

void liberaBooked(Booked *b){
    liberaListaLivros(b->catalogoLivros);
    liberaListaLeitores(b->listaLeitores);
    free(b);
}
