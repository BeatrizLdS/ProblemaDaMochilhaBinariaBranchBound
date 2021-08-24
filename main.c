#include <stdio.h>
#include <stdlib.h>

typedef struct {double capacidade, *peso, *valor; int quantidade;}MOCHILA;

/*coloca em ordem decrescente de valor relativo (valor/peso)*/
void bolha(MOCHILA p){
    int i, j;
    double aux;
    for (i=1; i<p.quantidade; i++){
        for (j=1; j<p.quantidade; j++){
            if (p.valor[j]/p.peso[j] > p.valor[j-1]/p.peso[j-1]){

                aux = p.peso[j];
                p.peso[j] = p.peso[j-1];
                p.peso[j-1] = aux;

                aux = p.valor[j];
                p.valor[j] = p.valor[j-1];
                p.valor[j-1] = aux;
            }
        }
    }
} /*fim do bolha (bubblesort)*/


/*devolve o valor de uma solução ótima para a instância do PMB*/
double pmbBB(MOCHILA p){
    int i, j, k = -1, it = 0, x[p.quantidade];
    double capacidade = p.capacidade, valor = 0, max = -1;
    int b;

    bolha(p);

    do{

        for (i= k+1; i<p.quantidade; i++){ /*calculando uma solução*/
            if(p.peso[i]<= capacidade){
                x[i] = 1;
                capacidade -= p.peso[i];
                valor += p.valor[i];
            }
            else{
                x[i] = 0;
            }

        }

        max = valor > max? valor : max;
        for(b=0; b<p.quantidade; b++){
            printf("%d", x[b]);
        }
        printf("\nv: %lf / p: %lf\n\n", valor, p.capacidade-capacidade);

        k = -1;
        for (i = p.quantidade -1; i >= 0; i--){
            if (x[i]){
                capacidade += p.peso[i];
                valor -= p.valor[i];
                if (i < p.quantidade-1 && valor + capacidade*(p.valor[i+1]/p.peso[i+1]) >= max+1){
                    k = i; break;
                }
            }
        }
        if (k>-1){
            x[k] = 0;
        }
        it ++;
    }while(k > -1);
    printf("Iteracoes: %d\n", it);
    return max;
} /*fim do pmbBB*/

int main(){
    int i;
    MOCHILA p;
    printf("Capacidade da mochila:");
    scanf("%lf", &p.capacidade);
    printf("Quantidade de itens:");
    scanf("%d", &p.quantidade);
    p.peso = malloc(sizeof(double) * p.quantidade);
    p.valor = malloc(sizeof(double) * p.quantidade);
    if (p.peso == NULL || p.valor == NULL){
        printf("Deu pau! falta de memória\n");
        return 1;
    }
    for (i=0; i<p.quantidade; i++){
        printf("Peso do item %d:", i+1);
        scanf("%lf", &p.peso[i]);
        printf("Valor do item %d:", i+1);
        scanf("%lf", &p.valor[i]);
    }
    printf("Solucao pmbEE: %lf\n", pmbBB(p));
    /*printf("Solucao pmbPD: %lf\n", pmbPD(p));*/
    return 0;
}
