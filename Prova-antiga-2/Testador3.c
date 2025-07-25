//
//  main.c
//  Testador 3: testa todas as funcionalidades
//
//  Created by Patricia Dockhorn Costa on 22/06/22.
//

#include <stdio.h>
#include "Pedido.h"

int main(int argc, const char * argv[]) {
 
    //criar uma comidinhas, veganas e não veganas
    
    ComidaNaoVegana* picanha = inicComidaNaoVegana("Picanha", 300, 90.5);
    ComidaNaoVegana* linguica = inicComidaNaoVegana("Linguica", 400, 30.8);
    ComidaNaoVegana* sorvete = inicComidaNaoVegana("Sorvete de Creme", 600, 15.4);
    
    ComidaVegana* abobrinha = inicComidaVegana("abobrinha", 200);
    ComidaVegana* empadao = inicComidaVegana("Empadao", 600);
    
    
    //iniciar um pedido
    Pedido* pedidoPat = inicPedido(123);
    
    //inserir umas comidas no pedido Pat
    insereComidaVegana(pedidoPat, empadao);
    insereComidaNaoVegana(pedidoPat, sorvete);
    insereComidaNaoVegana(pedidoPat, picanha);
    
    //Imprime os dados do pedido, seguindo o formato a seguir
    /*Imprimindo Detalhes do Pedido número: 123
      Valor total do Pedido: 135.90

     Lista de Itens de Baixa Caloria: 1
     Nome comida nao vegana: Picanha, valor: 90.50, calorias: 300

     Lista de Itens de Alta Caloria: 2
     Nome comida vegana: Empadao, calorias: 600
     Nome comida nao vegana: Sorvete de Creme, valor: 15.40, calorias: 600
*/
    imprimePedido(pedidoPat);
    
    //fizeram uma alteracao na receita do empadao e o numero de calorias diminui ;)
    alteraCaloriasComidaVegana(empadao, 400);
    //precisamos atualizar o empadao para sua lista correta dentro do pedido Pat
    atualizaSituacaoComidaVegana(pedidoPat, empadao);
    
    //mesma coisa com sorvete
    alteraCaloriasComidaNaoVegana(sorvete, 200);
    atualizaSituacaoComidaNaoVegana(pedidoPat, sorvete);
    
    imprimePedido(pedidoPat);

    //fazendo testes com outro pedido
    Pedido* pedidoFulano = inicPedido(345);
    
    insereComidaVegana(pedidoFulano, empadao);
    insereComidaVegana(pedidoFulano, abobrinha);
    insereComidaNaoVegana(pedidoFulano, linguica);
    
    imprimePedido(pedidoFulano);
    
    alteraCaloriasComidaNaoVegana(linguica, 300);
    atualizaSituacaoComidaNaoVegana(pedidoFulano, linguica);
    
    imprimePedido(pedidoFulano);
    //liberando memoria de tudo
    liberaPedido(pedidoPat);
    liberaPedido(pedidoFulano);
    
    liberaComidaVegana(abobrinha);
    liberaComidaVegana(empadao);
    
    liberaComidaNaoVegana(picanha);
    liberaComidaNaoVegana(linguica);
    liberaComidaNaoVegana(sorvete);
    
    return 0;
}
