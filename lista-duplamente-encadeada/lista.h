#ifndef _LISTA_
#define _LISTA_
#include "produto.h"

typedef struct lista Lista;

Lista* criaLista();

Lista* insereProduto(Lista *l, Produto *p);

Lista* RetiraProduto(Lista *l, int codigo);

void imprimeLista(Lista *l);

void liberaLista(Lista *l);

#endif // Lista
