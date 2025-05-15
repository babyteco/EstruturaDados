#include <stdio.h>
#include <stdlib.h>

//Tipo matriz (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementacao do TAD
typedef struct matriz {
    int linhas, colunas;
    int **matriz;
 } Matriz;

/*Inicializa uma matriz de nlinhas e ncolunas
 * inputs: nlinhas (no de linhas) e ncolunas (no de colunas)
 * output: ponteiro para a matriz inicializada
 * pre-condicao: nlinhas e ncolunas diferentes de 0
 * pos-condicao: matriz de retorno existe e contem nlinhas e ncolunas
 */
Matriz* inicializaMatriz (int nlinhas, int ncolunas){
    Matriz *m = (Matriz*) malloc(sizeof(Matriz*));
    m->matriz = (int **) malloc(nlinhas * sizeof(int*));
    for (int i = 0; i < nlinhas; i++){
        m->matriz[i] = malloc(ncolunas * sizeof(int));
    }
    m->colunas = ncolunas;
    m->linhas = nlinhas;

    return m;
}

/*Modifica o elemento [linha][coluna] da matriz mat
 * inputs: a matriz, a linha, a coluna, e o novo elemento
 * output: nenhum
 * pre-condicao: matriz mat existe, linha e coluna sao validos na matriz
 * pos-condicao: elemento [linha][coluna] da matriz modificado
 */
void modificaElemento (Matriz* mat, int linha, int coluna, int elem){
    mat->matriz[linha][coluna] = elem;
}

/*Retorna o elemento mat[linha][coluna]
 * inputs: a matriz, a linha e a coluna
 * output: elemento mat[linha][coluna]
 * pre-condicao: matriz mat existe, linha e coluna sao validos na matriz
 * pos-condicao: mat nao eh modificada
 */
int recuperaElemento(Matriz* mat, int linha, int coluna){
    return mat->matriz[linha][coluna];
}

/*Retorna o numero de colunas da matriz mat
 * inputs: a matriz
 * output: o numero de colunas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat nao eh modificada
 */
int recuperaNColunas (Matriz* mat){
    return mat->colunas;
}

/*Retorna o numero de linhas da matriz mat
 * inputs: a matriz
 * output: o numero de linhas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat nao eh modificada
 */
int recuperaNLinhas (Matriz* mat){
    return mat->linhas;
}

/*Retorna a matriz transposta de mat
 * inputs: a matriz
 * output: a matriz transposta
 * pre-condicao: matriz mat existe
 * pos-condicao: mat nao eh modificada e matriz transposta existe
 */
Matriz* transposta (Matriz* mat){
    Matriz *m = inicializaMatriz(mat->colunas, mat->linhas);
    for (int i = 0; i < mat->linhas; i++){
        for (int j = 0; j < mat->colunas; j++){
            m->matriz[j][i] = mat->matriz[i][j];
        }
    }
    return m;
}

/*Retorna a matriz multiplicacao entre mat1 e mat2
 * inputs: as matrizes mat1 e mat2
 * output: a matriz multiplicacao
 * pre-condicao: matrizes mat1 e mat2 existem, e o numero de colunas de mat1 correponde ao numero de linhas de mat2
 * pos-condicao: mat1 e mat2 nao sao modificadas e a matriz multiplicacao existe
 */
Matriz* multiplicacao (Matriz* mat1, Matriz* mat2){
    Matriz *m = inicializaMatriz(mat1->linhas, mat2->colunas);
    for (int i = 0; i < mat1->linhas; i++){
        for (int h = 0; h < mat2->colunas; h++){
            int temp = 0;
            for (int j = 0; j < mat1->colunas; j++){
                temp += mat1->matriz[i][j] * mat2->matriz[j][h];
            }
            m->matriz[i][h] = temp;
        }
    }
    return m;
}

/*Imprime a matriz completa
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: nenhuma
 */
void imprimeMatriz(Matriz* mat){
    for (int i = 0; i < mat->linhas; i++){
        for (int j = 0; j < mat->colunas; j++){
            printf("%d ", mat->matriz[i][j]);
        }
        printf("\n");
    }
    
}

/*Imprime apenas uma linha da matriz
 * inputs: matriz mat e o indice da linha
 * output: nenhum
 * pre-condicao: matriz mat existe e indice eh valido na matriz
 * pos-condicao: nenhuma
 */
void imprimeLinha (Matriz* mat, int indice){
    if (indice <= mat->linhas){
        for (int i = 0; i < mat->colunas; i++){
            printf("%d ", mat->matriz[indice][i]);
        }
    }
    printf("\n");
}

/*Libera toda a memoria alocada para a size_tmatriz
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: memoria ocupada por linhas e colunas liberada!
 */
void destroiMatriz (Matriz* mat){
    for (int i = 0; i < mat->linhas; i++){
        free(mat->matriz[i]);
    }
    free(mat->matriz);
    free(mat);
}