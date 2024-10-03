#ifndef TRABALHO3_H
#define TRABALHO3_H

typedef struct chapas Chapas;

typedef struct lista Lista;

Chapas *criar_chapas();

Lista *cadastrar(Chapas *chapas, int qnt_chapas , Lista *lst);

Lista* inserir_chapas(Lista *chalstpas, Chapas *novaChapa);

void printar_chapas(Lista *lst);

void votacao(Lista *lst);

void printar_boletimPrimeiroTurno(Lista *lst, FILE *boletimPrimeiroTurno);

void liberar_lista(Lista *lst);

int verificar_numero(Lista *lst, int voto);

#endif // TRABALHO3_H