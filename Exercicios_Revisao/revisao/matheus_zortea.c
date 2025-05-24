#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define PI 3

void calc_esfera (float r, float* area, float* volume);

int raizes (float a, float b, float c, float* x1, float* x2);

int pares (int n, int* vet);

void inverte (int n, int* vet);

double avalia (double* poli, int grau, double x);

int main(){
    /* EXERCICIO 1
    float raio;
    float volume, area;
    scanf("%f", &raio);
    calc_esfera(raio, &area, &volume);
    printf("Area: %.2f Volume: %.2f\n", area, volume);
    */

    /* EXERCICIO 2
    float a, b, c, x1, x2;
    scanf("%f %f %f", &a, &b, &c);
    if(raizes(a, b, c, &x1, &x2) == 0){
        printf("Nao existem raizes reais\n");
    } else{
        printf("Raiz 1: %.2f\n", x1);
        printf("Raiz 2: %.2f\n", x2);
    }
    */

    /* EXERCICIO 3
    int tam;
    int *vet;
    scanf("%d", &tam);
    vet = (int*) malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++){
        scanf("%d", &vet[i]);
    }
    printf("Qtd Pares: %d\n", pares(tam, vet));
    free(vet);
    */

    /* EXERCICIO 4
    int tam;
    int *vet;
    scanf("%d", &tam);
    vet = (int*) malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++){
        scanf("%d", &vet[i]);
    }
    inverte(tam, vet);
    for (int i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
    free(vet);
    */

    /* EXERCICIO 5
    int grau;
    double x;
    scanf("%d", &grau);
    grau++;
    scanf("%lf", &x);
    double *vet = (double*) malloc(grau * sizeof(double));
    for (int i = 0; i < grau; i++){
        scanf("%lf", &vet[i]);
    }
    printf("O valor do polinômio em x = %.2lf vale: %.2lf\n", x, avalia(vet, grau, x));
    */
}

void calc_esfera (float r, float* area, float* volume){
    *area  = 4 * PI * r * r; 
    *volume = (4 * PI * r * r * r) / 3;
}

int raizes (float a, float b, float c, float* x1, float* x2){
    float delta = (b * b) - (4 * a * c);

    if (delta < 0){
        return 0;
    }
    
    *x1 = ((-1)*b + sqrt(delta)) / 2 * a;
    *x2 = ((-1)*b - sqrt(delta)) / 2 * a;

    return 1;
}

int pares (int n, int* vet){
    int cont = 0;
    for (int i = 0; i < n; i++){
        if ((vet[i] % 2) == 0){
            cont++;
        }
    }
    
    return cont;
}

void inverte (int n, int* vet){
    int temp;
    for (int i = 0; i < n/2; i++){
        temp = vet[i];
        vet[i] = vet[n - i - 1];
        vet[n - i - 1] = temp;
    }   
}

double avalia (double* poli, int grau, double x){
    double valor = poli[0];
    for (int i = 1; i < grau; i++){
        valor += (poli[i] * pow(x, i));
    }
    return valor;
}
