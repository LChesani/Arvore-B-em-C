#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

int getPos(Indice *idx){
    return idx->pos_seek;
}

ArvB *ArvB_cria(void)
{
    ArvB *arv = (ArvB *)malloc(sizeof(ArvB));
    arv->n_chaves = 0;
    arv->folha = 1;
    return arv;
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

void ArvB_printa(ArvB *arv)
{
    if (arv == NULL)
    {
        return;
    }
    printf("folha: %d ", arv->folha);
    for (int i = 0; i < arv->n_chaves; i++)
    {
        printf("%d ", arv->chaves[i].id);
    }
    printf("\n");
    for (int i = 0; i < arv->n_chaves + 1; i++)
    {
        ArvB_printa(arv->filhos[i]);
    }
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

            desloca_chaves(arv,pos);

            memmove(&arv->filhos[pos + 2], &arv->filhos[pos + 1], sizeof(*(arv->chaves)) * (arv->n_chaves - pos));

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

        noFilho = (ArvB*) malloc(sizeof(ArvB));

        noFilho->n_chaves = arv->n_chaves - filhoNchaves - 1;
        noFilho->folha = arv->folha;

        memmove(noFilho->chaves, &arv->chaves[filhoNchaves + 1], sizeof(*(arv->chaves)) * noFilho->n_chaves);
        if (!arv->folha)
        {
            memmove(noFilho->filhos, &arv->filhos[filhoNchaves + 1], sizeof(*(arv->filhos)) * (noFilho->n_chaves + 1));
        }

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
    ArvB *noArvEsq;
    ArvB *noArvDir;
    int idMeio;

    noArvDir = ArvB_insere_rec(arv, chave, &idMeio);

    if (noArvDir != OK)
    {

        noArvEsq = (ArvB*) malloc(sizeof(ArvB));
        assert(noArvEsq);

        memmove(noArvEsq, arv, sizeof(*arv));

        arv->n_chaves = 1;
        arv->folha = 0;
        arv->chaves[0].id = idMeio;
        arv->filhos[0] = noArvEsq;
        arv->filhos[1] = noArvDir;
    }
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
