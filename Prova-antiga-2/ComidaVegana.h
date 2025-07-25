//
//  ComidaVegana.h
//  HawaiEd
//
//  Created by Patricia Dockhorn Costa on 22/06/22.
//

#ifndef ComidaVegana_h
#define ComidaVegana_h

#include <stdio.h>

/*Tipo que define o alimento COMIDA VEGANA (tipo opaco)
 *Neste exemplo simples, uma comida vegana é definida por seu nome e seu numero de calorias
 * */
typedef struct vegana ComidaVegana;

//inicia uma comida vegana, com um nome e um certo numero de calorias
//comida vegana tem um valor fixo de 30 reais
//A função deve alocar dinamicamente a string nome
ComidaVegana* inicComidaVegana(char* nome, int calorias);

//imprime as informacoes da comida vegana
void imprimeComidaVegana (ComidaVegana* food);

//retorna o nome da comida vegana
char* retornaNomeComidaVegana (ComidaVegana* food);

//retorna o numero de calorias da comida vegana
int retornaCaloriasComidaVegana (ComidaVegana* food);

//altera o valor do numero de calorias da comida vegana
void alteraCaloriasComidaVegana (ComidaVegana* food, int calorias);

//libera toda a memoria alocada
void liberaComidaVegana (ComidaVegana* food);





#endif /* ComidaVegana_h */
