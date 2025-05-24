#include<stdio.h>
#include<stdlib.h>
#include "lista.h"
#include "produto.h"

int main(){

    Lista *l = criaLista();

    insereProduto(l, criaProduto(100, 10, "oculos"));
    insereProduto(l, criaProduto(200, 20, "chapeu"));
    insereProduto(l, criaProduto(300, 30, "cordao"));
    insereProduto(l, criaProduto(400, 40, "celular"));
    insereProduto(l, criaProduto(500, 15, "relogio"));
    insereProduto(l, criaProduto(600, 25, "mochila"));
    insereProduto(l, criaProduto(700, 12, "carteira"));
    insereProduto(l, criaProduto(800, 18, "cinto"));
    insereProduto(l, criaProduto(900, 22, "sapato"));
    insereProduto(l, criaProduto(1000, 35, "camisa"));
    insereProduto(l, criaProduto(1100, 8, "calca"));
    insereProduto(l, criaProduto(1200, 14, "tenis"));
    insereProduto(l, criaProduto(1300, 9, "meia"));
    insereProduto(l, criaProduto(1400, 16, "blusa"));
    insereProduto(l, criaProduto(1500, 11, "jaqueta"));
    insereProduto(l, criaProduto(1600, 13, "bone"));
    insereProduto(l, criaProduto(1700, 19, "vestido"));
    insereProduto(l, criaProduto(1800, 7, "saia"));
    insereProduto(l, criaProduto(1900, 21, "shorts"));
    insereProduto(l, criaProduto(2000, 17, "terno"));  
    
    imprimeLista(l);

    RetiraProduto(l, 10);
    RetiraProduto(l, 20);
    RetiraProduto(l, 30);
    RetiraProduto(l, 40);

    printf("\n\nLISTA APOS RETIRADA DOS PRODUTOS\n\n");
    imprimeLista(l);

    liberaListaCelula(l);

    return 0;
}