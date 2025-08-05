#ifndef arvore_h
#define arvore_h

typedef struct arv Arvore;

//Cria uma árvore vazia
Arvore* arv_criavazia (void);

//cria uma árvore com a informação do nó raiz c, e com subárvore esquerda e e subárvore direita d
Arvore* arv_cria (char c, Arvore* e, Arvore* d);

//libera o espaço de memória ocupado pela árvore a
Arvore* arv_libera (Arvore* a);

//retorna true se a árvore estiver vazia e false caso contrário
int arv_vazia (Arvore* a);

//indica a ocorrência (1) ou não (0) do aluno (pela chave de busca mat)
int arv_pertence (Arvore* a, char caractere);

//imprime as informações dos nós da árvore
void arv_imprime (Arvore* a);

//retorna a mãe/pai de um dado no que contém o aluno com a matrícula mat
Arvore* arv_pai (Arvore* a, char caractere);

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arvore* a);

//retorna o numero de ocorrencias de um dado aluno na árvore
int ocorrencias (Arvore* a, int mat);

//retorna a altura da árvore a
int altura(Arvore* a);

char getCaractere(Arvore *arvore);

#endif 