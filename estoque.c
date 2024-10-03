#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int votoNulo, votoBranco, votoValido;

typedef struct chapas Chapas;

struct chapas{
    char candidato[50];
    char vice[50];
    int num;
    int data_nascimento[3];
    int votos;
};

typedef struct lista Lista;

struct lista{
    Chapas *inicio;
    struct lista *prox;
};

Chapas *criar_chapas(){
    return NULL;
}

Lista* inserir_chapas(Lista *lst, Chapas *novaChapa){
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    if(novo == NULL){
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }

    novo->inicio = novaChapa;
    novo->prox = lst;
    return novo;
}

Lista *cadastrar(Chapas *chapas, int qnt_chapas, Lista *lst){
    for(int i = 0; i < qnt_chapas; i++){
        Chapas *novaChapa = (Chapas*) malloc(sizeof(Chapas));

        if(novaChapa == NULL){
            printf("Erro ao alocar memoria.\n");
            return NULL;
        }

        printf("->Digite o nome do candidato a ser cadastrado: ");
        setbuf(stdin, NULL);
        fgets(novaChapa->candidato, 50, stdin);
        novaChapa->candidato[strlen(novaChapa->candidato) - 1] = '\0';

        printf("->Digite o nome do vice-candidato: ");
        setbuf(stdin, NULL);
        fgets(novaChapa->vice, 50, stdin);
        novaChapa->vice[strlen(novaChapa->vice) - 1] = '\0';

        printf("->Digite o numero da chapa: ");
        scanf("%d", &novaChapa->num);

        printf("->Digite a data de nascimento do candidato(dia/mes/ano): ");
        for(int i= 0; i < 3;i++){
            scanf("%d", &novaChapa->data_nascimento[i]);
        }
        getchar();   
        lst = inserir_chapas(lst, novaChapa);
    }
    return lst;
}

void printar_chapas(Lista *lst) {
    Lista *atual = lst;
    int count = 1;

    while (atual != NULL) {
        printf("Chapa %d\n", count);
        printf("Prefeito: %s\n", atual->inicio->candidato);
        printf("Vice: %s\n", atual->inicio->vice);
        printf("Numero: %d\n", atual->inicio->num);
        printf("Data de Nascimento: %d/%d/%d\n", 
                atual->inicio->data_nascimento[0], 
                atual->inicio->data_nascimento[1], 
                atual->inicio->data_nascimento[2]);
        printf("\n");

        atual = atual->prox;
        count++;
    }
}

void votacao(Lista *lst){
    Lista *atual = lst;
    int voto;
    printf("->Digite o numero da chapa que deseja votar: ");
    scanf("%d", &voto);
    getchar();

    if(voto == 0){
        votoBranco++;
    }
    else if(voto <= 99){
        while(atual != NULL){
            if(atual->inicio->num == voto){
                atual->inicio->votos++;
                votoValido++;
                printf("Seu voto em %s com Vice %s foi confirmado!\n", atual->inicio->candidato, atual->inicio->vice);
                return;
            }
            atual = atual->prox;
        }
    }
    else{
        votoNulo++;
    }
}

void printar_votos(Lista *lst){
    Lista *atual = lst;
    int count = 1;

    while (atual != NULL) {
        printf("Chapa %d\n", count);
        printf("Prefeito: %s\n", atual->inicio->candidato);
        printf("Vice: %s\n", atual->inicio->vice);
        printf("Numero: %d\n", atual->inicio->num);
        printf("Votos: %d\n", atual->inicio->votos);
        printf("\n");

        atual = atual->prox;
        count++;
    }
}

void liberar_lista(Lista *lst){
    Lista *atual = lst;
    Lista *proximo;

    while(atual != NULL){
        proximo = atual->prox;
        free(atual->inicio);
        free(atual);
        atual = proximo;
    }
}