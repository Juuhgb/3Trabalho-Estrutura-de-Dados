#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int main(){
    int qnt_eleitores;
    int qnt_chapas;
    Lista *lst = NULL;

    fopen("eleitores.txt", "w");

    Chapas *chapas = criar_chapas();
    printf("-----------------------------------------\n");
    printf("|Eleicoes do Executivo Municipal de 2024|\n");
    printf("-----------------------------------------\n");
    printf("->Digite o numero de eleitores:\n");
    scanf("%d", &qnt_eleitores);

    printf("->Quantidade de chapas:\n");
    scanf("%d", &qnt_chapas);
    
    while(qnt_chapas > 100){
        printf("Maximo de chapas e 100, digite outro valor\n");
        scanf("%d", &qnt_chapas);
    }
    getchar();
    
    lst = cadastrar(chapas, qnt_chapas, lst);

    printf("--------------------\n");
    printf("|Chapas Cadastradas|\n");
    printf("--------------------\n");
    printar_chapas(lst);

    for(int i = 0; i < qnt_eleitores; i++){
        votacao(lst);
    }

    printar_votos(lst);

    liberar_lista(lst);
}