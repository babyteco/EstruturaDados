//
//  ComidaVegana.c
//  HawaiEd
//
//  Created by Patricia Dockhorn Costa on 22/06/22.
//

#include "ComidaVegana.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vegana{
    char* nome;
    int calorias;
};

ComidaVegana* inicComidaVegana(char* nome, int calorias){
    ComidaVegana* food = (ComidaVegana*)malloc(sizeof(ComidaVegana));
    food->nome = strdup(nome);
    food->calorias = calorias;
    return food;
}

void imprimeComidaVegana (ComidaVegana* food){
    printf("\nNome comida vegana: %s, calorias: %d\n", food->nome, food->calorias);
}

char* retornaNomeComidaVegana (ComidaVegana* food){
    return food->nome;
}

int retornaCaloriasComidaVegana (ComidaVegana* food){
    return food->calorias;
}

void alteraCaloriasComidaVegana (ComidaVegana* food, int calorias){
    food->calorias = calorias;
}

void liberaComidaVegana (ComidaVegana* food){
    free(food->nome);
    free(food);
}
