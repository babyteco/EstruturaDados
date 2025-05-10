#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct produto {
    char *nome;
    int valor;
} Produto;

typedef struct itemEstoque {
    int qtd;
    Produto *p; //ponteiro
} ItemEstoque;

typedef struct estoque {
    int preco;
    ItemEstoque **ie; //vetor
    int qtd;
} Estoque;

typedef struct filial {
    char *nome;
    Estoque *e; //ponteiro
} Filial;

typedef struct super {
    char *nome;
    Filial **f; //vetor
    int qtd;
    int valor;
} Super;

char *leLinha();

Produto *criaLeProduto();

ItemEstoque *criaLeItemEstoque();

Estoque *criaLeEstoque();

Filial *criaLeFilial();

Super *criaLeSuper();

void imprime(Super *s);

void desaloca(Super *s);

int main(){
    Super *s = criaLeSuper();
    imprime(s);
    desaloca(s);
    return 0;
}

char *leLinha(){
    char temp[100];
    scanf("%99[^\n]", temp);
    char *str = strdup(temp);
    return str;
}

Produto *criaLeProduto(){
    Produto *p = (Produto*) malloc(sizeof(Produto));
    p->nome = leLinha();
    scanf("%d\n", &p->valor);
    return p;
}

ItemEstoque *criaLeItemEstoque(){
    ItemEstoque *ie = (ItemEstoque*) malloc(sizeof(ItemEstoque));  
    scanf("%d\n", &ie->qtd);
    ie->p = criaLeProduto();
    return ie;
}

Estoque *criaLeEstoque(){
    Estoque *e = (Estoque*) malloc(sizeof(Estoque));
    scanf("%d\n", &e->qtd);
    e->ie = (ItemEstoque**) malloc(e->qtd * sizeof(ItemEstoque*));
    e->preco = 0;
    for (int i = 0; i < e->qtd; i++){
        e->ie[i] = criaLeItemEstoque();
        e->preco += e->ie[i]->qtd * e->ie[i]->p->valor;
    }
    return e;
}

Filial *criaLeFilial(){
    Filial *f = (Filial*) malloc(sizeof(Filial));
    f->nome = leLinha();
    f->e = criaLeEstoque();
    return f;
}

Super *criaLeSuper(){
    Super *s = (Super*) malloc(sizeof(Super));
    s->nome = leLinha();
    scanf("%d\n", &s->qtd);
    s->f = (Filial**) malloc(s->qtd * sizeof(Filial*));
    s->valor = 0;
    for (int i = 0; i < s->qtd; i++){
        s->f[i] = criaLeFilial();
        s->valor += s->f[i]->e->preco;
    }
    return s;
}

void imprime(Super *s){
    printf("SUPERMERCADO:\n");
    printf("Nome: %s\nEstoque Total: R$%d.00\n\n", s->nome, s->valor);
    
    printf("FILIAIS:\n\n");
    for (int i = 0; i < s->qtd; i++){
        printf("    Filial: %s\n", s->f[i]->nome);
        printf("    Estoque: %d\n", s->f[i]->e->preco);
        printf("\n  ITENS:\n");
        for (int j = 0; j < s->f[i]->e->qtd; j++){
            printf("        Item %d: %s, valor unitário: %d, quantidade: %d\n", j+1, s->f[i]->e->ie[j]->p->nome, s->f[i]->e->ie[j]->p->valor, s->f[i]->e->ie[j]->qtd);
        }
        printf("\n");
    }
    
}

void desaloca(Super *s){
    for (int i = 0; i < s->qtd; i++){
        
        //libera cada item de estoque
        for (int h = 0; h < s->f[i]->e->qtd; h++){
            free(s->f[i]->e->ie[h]->p->nome);
            free(s->f[i]->e->ie[h]->p);
            free(s->f[i]->e->ie[h]);
        }

        //libera o array de itens de estoque
        free(s->f[i]->e->ie);
        
        //desaloca o estoque da filial
        free(s->f[i]->e);
        
        //desaloca o nome da filial
        free(s->f[i]->nome);
        
        //desaloca filial
        free(s->f[i]);
    }
    
    //desaloca array de filiais
    free(s->f);

    //desaloca nome do super
    free(s->nome);

    //desaloca supermercado
    free(s);
}

/*
INPUT:
Carone (nome do super)
2 (numero de filiais)
Jardim camburi (primeira filial)
1 (qtd de produtos no estoque)
10 (qtd de itens do produto 1)
doritos (nome do produto 1)
10 (preco do produto 1)
Mata da Praia
2 (qtd de produtos no estoque da segunda filiaç)
10 (qtd de itens do produto 1)
miojo (nome do produto 1)
2 (preco do produto 1)
3 (qtd de itens do produto 2)
pasta de amendoim (nome do produto 2)
30 (preco do produto 2)

Carone 
2 
Jardim camburi 
1 
10 
doritos 
10 
Mata da Praia
2 
10 
miojo 
2 
3 
pasta de amendoim 
30 
*/