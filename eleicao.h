#ifndef TRABALHO3_H
#define TRABALHO3_H

typedef struct chapas Chapas;

typedef struct lista Lista;

Chapas *criar_chapas();

Lista *cadastrar(int qnt_chapas , Lista *lst);

Lista* inserir_chapas(Lista *lst, Chapas *novaChapa);

void printar_chapas(Lista *lst);

void votacao(Lista *lst);

void printar_boletim(Lista *lst, FILE *boletimPrimeiroTurno);

void liberar_lista(Lista *lst);

int verificar_numero(Lista *lst, int voto);

void verificar_segundoTurno(Lista *lst, int quantidadeEleitores, FILE *boletim);

void verificarMaisVelho(Lista *lst, FILE *boletim);

#endif // TRABALHO3_H