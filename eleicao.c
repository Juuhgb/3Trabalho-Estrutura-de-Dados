#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eleicao.h"

int votoNulo, votoBranco, votoValido;

typedef struct chapas Chapas;
typedef struct lista Lista;

struct chapas{
    char candidato[50];
    char vice[50];
    int num;
    int data_nascimento[3];
    int votos;
};

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

Lista *cadastrar(int qnt_chapas, Lista *lst){
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
        novaChapa->num = verificar_numero(lst, novaChapa->num);

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

    if(lst == NULL){
        printf("Nao ha chapas cadastradas!\n");
        return;
    }

    printf("->Digite o numero da chapa que deseja votar: ");
    scanf("%d", &voto);
    getchar();

    if(voto == 0){
        printf("Voto em branco!\n");
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
        printf("Voto nulo!\n");
        votoNulo++;
    }
    else{
        printf("Voto nulo!\n");
        votoNulo++;
    }
}

void printar_boletim(Lista *lst, FILE *boletim){
    Lista *atual = lst;
    int count = 1;

    while (atual != NULL) {
        fprintf(boletim,"Chapa %d\n", count);
        fprintf(boletim, "Prefeito: %s\n", atual->inicio->candidato);
        fprintf(boletim, "Vice: %s\n", atual->inicio->vice);
        fprintf(boletim, "Numero: %d\n", atual->inicio->num);
        fprintf(boletim, "Votos: %d\n", atual->inicio->votos);
        fprintf(boletim, "\n");

        atual = atual->prox;
        count++;
    }
    float porcetagemVotosValidos = (float)(votoValido*100)/(votoValido+votoBranco+votoNulo);
    float porcetagemVotosBranco = (float)(votoBranco*100)/(votoValido+votoBranco+votoNulo);
    float porcetagemVotosNulos = (float)(votoNulo*100)/(votoValido+votoBranco+votoNulo);
    float porcetagemRelacaoAosEleitores = (float)(votoValido*100)/(votoValido+votoBranco+votoNulo);
    float porcetagemVotosNulosBrancos = (float)((votoBranco+votoNulo)*100)/(votoValido+votoBranco+votoNulo);

    fprintf(boletim, "Votos Validos: %d\nVotos totais: %d\nVotos Brancos: %d\nVotos Nulos: %d\n",votoValido, votoValido+votoBranco+votoNulo, votoBranco, votoNulo);
    fprintf(boletim,"\n");
    fprintf(boletim, "Porcentagem de votos validos: %.2f%%\nPorcentagem de votos brancos: %.2f%%\nPorcentagem de votos nulos: %.2f%%\nPorcentagem em Relação aos eleitores: %.2f%%\nPorcentagem dos votos nulos e brancos: %.2f%%\n\n", porcetagemVotosValidos, porcetagemVotosBranco, porcetagemVotosNulos,porcetagemRelacaoAosEleitores, porcetagemVotosNulosBrancos);
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

int verificar_numero(Lista *lst, int voto){
    Lista *aux = lst;

    while(aux != NULL){
        while(aux->inicio->num == voto){
            printf("Este numero ja foi cadastrado, por favor, digite outro: ");
            scanf("%d", &voto);
        }
        aux = aux->prox;
    }
    return voto;
}

void verificar_segundoTurno(Lista *lst, int quantidadeEleitores, FILE *boletim){
    if(lst == NULL){
        printf("Nao ha chapas cadastradas!\n");
        return;
    }
    int segundoTurno = 0;

    printf("Votos validos: %d\n", votoValido);

    Lista *atual = lst;
    Lista *chapaMaisVotada1 = NULL;
    Lista *chapaMaisVotada2 = NULL;

    while(atual != NULL){
        if(chapaMaisVotada1 == NULL || atual->inicio->votos > chapaMaisVotada1->inicio->votos){
            chapaMaisVotada2 = chapaMaisVotada1;
            chapaMaisVotada1 = atual;
        } else if(chapaMaisVotada2 == NULL || atual->inicio->votos > chapaMaisVotada2->inicio->votos){
            chapaMaisVotada2 = atual;
        }
        atual = atual->prox;
    }
    Lista *listaSegundoTurno = NULL;
    listaSegundoTurno = inserir_chapas(listaSegundoTurno, chapaMaisVotada1->inicio);
    listaSegundoTurno = inserir_chapas(listaSegundoTurno, chapaMaisVotada2->inicio);

    Lista *chapaVencedora = NULL;
    int candidatoVencedor = 0;

    if(quantidadeEleitores >= 10 && votoValido > 0){
        for(chapaVencedora = lst; chapaVencedora != NULL; chapaVencedora = chapaVencedora->prox){
            if(chapaVencedora->inicio->votos > ((float)votoValido/2.0)){
                fprintf(boletim, "Chapa vencedora: %s\n", chapaVencedora->inicio->candidato);
                printf("Candidato vencedor: %s\n", chapaVencedora->inicio->candidato);
                candidatoVencedor = 1;
            }
        }
    }
    if(candidatoVencedor){
        fprintf(boletim, "Nao precisa de segundo turno\n");
        printf("Nao precisa de segundo turno");
        return;
    }
    else{
        fprintf(boletim, "Nao houve vencedor no primeiro turno, vamos para o segundo turno!\n");
        printf("Nao houve vencedor no primeiro turno, vamos para o segundo turno!\n\n");
        segundoTurno = 1;
    }

    if(segundoTurno){
        FILE *boletimSegundoTurno = fopen("boletimTurno2.txt", "w");
        printf("-------------------------\n");
        printf("|Chapas do Segundo Turno|\n");
        printf("-------------------------\n");

        votoBranco = 0; votoNulo = 0; votoValido = 0;
        chapaMaisVotada1->inicio->votos = 0;
        chapaMaisVotada2->inicio->votos = 0;

        printar_chapas(listaSegundoTurno);
        for(int i = 0; i < quantidadeEleitores; i++){
            votacao(listaSegundoTurno);
        }
        system("cls");
        if(chapaMaisVotada1->inicio->votos == chapaMaisVotada2->inicio->votos){
            printf("Empate! Vamos verificar o candidato mais velho\n");
            verificarMaisVelho(listaSegundoTurno, boletimSegundoTurno);
        } else{
            printf("Candidato vencedor: %s\n", chapaMaisVotada1->inicio->candidato);
            fprintf(boletimSegundoTurno, "Candidato vencedor: %s\n", chapaMaisVotada1->inicio->candidato);
        }
        printar_boletim(listaSegundoTurno, boletimSegundoTurno); 
        liberar_lista(listaSegundoTurno);
        fclose(boletimSegundoTurno);
    }
}

void verificarMaisVelho(Lista *lst, FILE *boletim){
    Lista *atual = lst;
    Lista *maisVelho = NULL;

    while(atual != NULL){
        if(maisVelho == NULL || atual->inicio->data_nascimento[2] < maisVelho->inicio->data_nascimento[2]){
            maisVelho = atual;
        } else if(atual->inicio->data_nascimento[2] == maisVelho->inicio->data_nascimento[2]){
            if(atual->inicio->data_nascimento[1] < maisVelho->inicio->data_nascimento[1]){
                maisVelho = atual;
            } else if(atual->inicio->data_nascimento[1] == maisVelho->inicio->data_nascimento[1]){
                if(atual->inicio->data_nascimento[0] < maisVelho->inicio->data_nascimento[0]){
                    maisVelho = atual;
                }
            }
        }
        atual = atual->prox;
    }
    printf("Candidato mais velho e  %s, logo e o vencedor!\n", maisVelho->inicio->candidato);
    fprintf(boletim, "Candidato mais velho e o %s, logo e o vencedor!\n", maisVelho->inicio->candidato);
}