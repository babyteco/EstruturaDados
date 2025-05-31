#ifndef _PRODUTO_
#define _PRODUTO_


typedef struct produto Produto;

Produto* criaProduto(int preco, int codigo, char *nome);

void imprimeProduto(Produto *p);

void liberaProduto(Produto *p);

int getCodigoProduto(Produto *p);

#endif 
