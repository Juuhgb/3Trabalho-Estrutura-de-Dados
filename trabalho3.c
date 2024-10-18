#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int main(){
    int qnt_eleitores;
    int qnt_chapas;
    Lista *lst = NULL;

    FILE *boletimPrimeiroTurno = fopen("boletimTurno1.txt", "w");

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
    
    lst = cadastrar(qnt_chapas, lst);

    system("cls");
    printf("--------------------\n");
    printf("|Chapas Cadastradas|\n");
    printf("--------------------\n");

    printar_chapas(lst);

    for(int i = 0; i < qnt_eleitores; i++){
        votacao(lst);
    }

    printar_boletimPrimeiroTurno(lst, boletimPrimeiroTurno);
    
    system("cls");
    printf("----------------------\n");
    printf("|Resultado do 1 Turno|\n");
    printf("----------------------\n");
    
    int resultado = verificar_segundoTurno(lst, qnt_eleitores, boletimPrimeiroTurno);
    
    liberar_lista(lst);
    fclose(boletimPrimeiroTurno);

    if(resultado == 1){
        FILE *boletimSegundoTurno = fopen("boletimTurno2.txt", "w");
        system("cls");
        printf("-----------------------------\n");
        printf("|Candidatos do Segundo turno|\n");
        printf("-----------------------------\n");
        for(int i = 0; i < qnt_eleitores; i++){
            votacao(lst);
        }
        printar_boletimPrimeiroTurno(lst, boletimSegundoTurno);
        liberar_lista(lst);
        fclose(boletimSegundoTurno);
    }
}
