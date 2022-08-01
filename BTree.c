#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

#define M 4
#define OK 0

struct indice
{
    int pos_seek;
    int id;
};

struct arvb
{
    Indice chaves[M - 1];
    struct arvb *filhos[M];
    int n_chaves;
    int folha; // e folha ou nao e
};

Indice *indice_cria(int id, int pos_seek)
{
    Indice *idx = (Indice *)malloc(sizeof(Indice));
    idx->id = id;
    idx->pos_seek = pos_seek;
    return idx;
}

ArvB *ArvB_cria(void)
{
    ArvB *arv = (ArvB *)malloc(sizeof(ArvB));
    arv->n_chaves = 0;
    arv->folha = 1;
    return arv;
}

int getPos(Indice *idx){
    return idx->pos_seek;
}

Indice *Arv_busca(ArvB *arv, Indice *idx)
{
    int i = 0;
    while (i < arv->n_chaves && idx->id > arv->chaves[i].id)
    {
        i++;
    }
    if (i < arv->n_chaves && idx->id == arv->chaves[i].id)
    {
        return &(arv->chaves[i]);
    }
    if (arv->folha == 1)
    {
        return NULL;
    }
    return Arv_busca(arv->filhos[i], idx);
}

int busca_pos_chave(ArvB *arv, int id)
{
    for (int i = 0; i < arv->n_chaves; i++)
    {
        if (arv->chaves[i].id > id)
        {
            return i;
        }
    }
    return arv->n_chaves;
}

void desloca_chaves(ArvB *arv, int pos)
{
    for (int i = arv->n_chaves; i > pos; i--)
    {
        arv->chaves[i] = arv->chaves[i - 1];
    }
}

void desloca_filhos(ArvB *arv, int pos)
{
    for (int i = arv->n_chaves + 1; i > pos + 1; i--)
    {
        arv->filhos[i] = arv->filhos[i - 1];
    }
}

void coloca_chaves_no_filho(ArvB *arv, ArvB *noFilho, int pos)
{
    for (int i = pos; i < arv->n_chaves; i++)
    {
        noFilho->chaves[i - pos] = arv->chaves[i];
    }
}

void coloca_filhos_no_filho(ArvB *arv, ArvB *noFilho, int pos)
{
    for (int i = pos; i < arv->n_chaves + 1; i++)
    {
        noFilho->filhos[i - pos] = arv->filhos[i];
        arv->filhos[i] = NULL;
    }
}

void nova_raiz(ArvB *raiz, ArvB *noArvEsq, ArvB *noArvDir, int idMeio)
{
    noArvEsq = (ArvB *)malloc(sizeof(ArvB));

    coloca_chaves_no_filho(raiz, noArvEsq, 0);
    for (int i = 0; i < raiz->n_chaves + 1; i++)
        noArvEsq->filhos[i] = raiz->filhos[i];
    noArvEsq->folha = raiz->folha;
    noArvEsq->n_chaves = raiz->n_chaves;

    raiz->n_chaves = 1;
    raiz->folha = 0;
    raiz->chaves[0].id = idMeio;
    raiz->filhos[0] = noArvEsq;
    raiz->filhos[1] = noArvDir;
}

ArvB *ArvB_insere_rec(ArvB *arv, Indice *chave, int *idMeio)
{
    int pos;
    int idMeioAux;
    int filhoNchaves;
    ArvB *noFilho;

    pos = busca_pos_chave(arv, chave->id);

    if (pos < arv->n_chaves && arv->chaves[pos].id == chave->id)
    {
        return OK;
    }

    if (arv->folha)
    {
        desloca_chaves(arv, pos);
        arv->chaves[pos] = *chave;
        arv->n_chaves++;
    }
    else
    {

        noFilho = ArvB_insere_rec(arv->filhos[pos], chave, &idMeioAux);

        if (noFilho != OK)
        {

            desloca_chaves(arv, pos);

            desloca_filhos(arv, pos);

            arv->chaves[pos].id = idMeioAux;
            arv->chaves[pos].pos_seek = 1;
            arv->filhos[pos + 1] = noFilho;
            arv->n_chaves++;
        }
    }

    if (arv->n_chaves >= M - 1)
    {
        filhoNchaves = arv->n_chaves / 2;

        *idMeio = arv->chaves[filhoNchaves].id;

        noFilho = (ArvB *)malloc(sizeof(ArvB));

        noFilho->n_chaves = arv->n_chaves - filhoNchaves - 1;
        noFilho->folha = arv->folha;

        coloca_chaves_no_filho(arv, noFilho, filhoNchaves + 1);

        if (!arv->folha)
            coloca_filhos_no_filho(arv, noFilho, filhoNchaves + 1);

        arv->n_chaves = filhoNchaves;

        return noFilho;
    }
    else
    {
        return OK;
    }
}

void ArvB_insere(ArvB *arv, Indice *chave)
{
    ArvB *noArvEsq = NULL;
    ArvB *noArvDir = NULL;
    int idMeio;

    noArvDir = ArvB_insere_rec(arv, chave, &idMeio);

    if (noArvDir != OK)
        nova_raiz(arv, noArvEsq, noArvDir, idMeio);
}

void ArvB_limpa(ArvB *arv)
{
    if (arv == NULL)
        return;
    for (int i = 0; i < M; i++)
    {
        ArvB_limpa(arv->filhos[i]);
    }
    free(arv);
}
