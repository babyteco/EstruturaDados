//
//  ComidaNaoVegana.h
//  HawaiEd
//
//  Created by Patricia Dockhorn Costa on 22/06/22.
//

#ifndef ComidaNaoVegana_h
#define ComidaNaoVegana_h

#include <stdio.h>

/*Tipo que define o alimento COMIDA NAO VEGANA (tipo opaco)
 *Neste exemplo simples, uma comida vegana é definida por seu nome e seu numero de calorias e o valor
 * */
typedef struct vegana ComidaNaoVegana;

//inicia uma comida nao vegana, com um nome, um certo numero de calorias e um valor
//A função deve alocar dinamicamente a string nome
ComidaNaoVegana* inicComidaNaoVegana(char* nome, int calorias, float valor);

void imprimeComidaNaoVegana (ComidaNaoVegana* food);

char* retornaNomeComidaNaoVegana (ComidaNaoVegana* food);

void alteraCaloriasComidaNaoVegana (ComidaNaoVegana* food, int calorias);

int retornaCaloriasComidaNaoVegana (ComidaNaoVegana* food);
                                 
float retornaValorComidaNaoVegana (ComidaNaoVegana* food);

void liberaComidaNaoVegana (ComidaNaoVegana* food);
#endif /* ComidaNaoVegana_h */
