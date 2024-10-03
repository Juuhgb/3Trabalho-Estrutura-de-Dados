#ifndef TRABALHO3_H
#define TRABALHO3_H

typedef struct chapas Chapas;

typedef struct lista Lista;

Chapas *criar_chapas();

Lista *cadastrar(Chapas *chapas, int qnt_chapas , Lista *lst);

Lista* inserir_chapas(Lista *chalstpas, Chapas *novaChapa);

void printar_chapas(Lista *lst);

void votacao(Lista *lst);

void printar_votos(Lista *lst);

void liberar_lista(Lista *lst);

#endif // TRABALHO3_H