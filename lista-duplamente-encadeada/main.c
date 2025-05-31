#include<stdio.h>
#include<stdlib.h>
#include "lista.h"
#include "produto.h"

int main(){

    Lista *l = criaLista();

    l = insereProduto(l, criaProduto(100, 10, "oculos"));
    l = insereProduto(l, criaProduto(200, 20, "chapeu"));
    l = insereProduto(l, criaProduto(300, 30, "cordao"));
    l = insereProduto(l, criaProduto(400, 40, "celular"));
    l = insereProduto(l, criaProduto(500, 15, "relogio"));
    l = insereProduto(l, criaProduto(600, 25, "mochila"));
    l = insereProduto(l, criaProduto(700, 12, "carteira"));
    l = insereProduto(l, criaProduto(800, 18, "cinto"));
    l = insereProduto(l, criaProduto(900, 22, "sapato"));
    l = insereProduto(l, criaProduto(1000, 35, "camisa"));
    l = insereProduto(l, criaProduto(1100, 8, "calca"));
    l = insereProduto(l, criaProduto(1200, 14, "tenis"));
    l = insereProduto(l, criaProduto(1300, 9, "meia"));
    l = insereProduto(l, criaProduto(1400, 16, "blusa"));
    l = insereProduto(l, criaProduto(1500, 11, "jaqueta"));
    l = insereProduto(l, criaProduto(1600, 13, "bone"));
    l = insereProduto(l, criaProduto(1700, 19, "vestido"));
    l = insereProduto(l, criaProduto(1800, 7, "saia"));
    l = insereProduto(l, criaProduto(1900, 21, "shorts"));
    l = insereProduto(l, criaProduto(2000, 17, "terno"));  
    
    imprimeLista(l);

    l = RetiraProduto(l, 10);
    l = RetiraProduto(l, 35);
    l = RetiraProduto(l, 9);
    l = RetiraProduto(l, 17);
    

    printf("\nLISTA APOS RETIRADA DOS PRODUTOS\n\n");
    imprimeLista(l);

    liberaLista(l);
    printf("fim do programa\n");
    return 0;
}