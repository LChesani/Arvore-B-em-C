#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

#define M 4

struct indice
{
    int pos_seek;
    int id;
};

struct cachorro
{
    char nome[10];
    char raca[10];
    int idade;
    int id;
};

struct arvb
{
    Indice chaves[M - 1];
    struct arvb *filhos[M];
    int n_chaves;
    int folha; // e folha ou nao e
};

ArvB *ArvB_cria(void)
{
    ArvB *arv = (ArvB *)malloc(sizeof(ArvB));
    arv->n_chaves = 0;
    arv->folha = 1;
    for (int i = 0; i < M - 1; i++)
    {
        arv->chaves[i].pos_seek = -1;
        arv->chaves[i].id = -1;
    }
    for (int i = 0; i < M; i++)
    {
        arv->filhos[i] = NULL;
    }
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
    for (int i = 0; i < arv->n_chaves; i++)
    {
        printf("%d ", arv->chaves[i].id);
    }
    printf("\n");
    for (int i = 0; i < M; i++)
    {
        ArvB_printa(arv->filhos[i]);
    }
}

int chave(ArvB *arv, Indice *idx){
    for(int i = 0; i < arv->n_chaves; i++){
        if(arv->chaves[i].id < idx->id){
            return i;
        }
    }
    return -1;
}

void ordena(ArvB *arv, Indice *idx, int pos){
    for(int i = arv->n_chaves; i > pos+1; i--){
        arv->chaves[i+1] = arv->chaves[i];
    }
}


void ArvB_insere_rec(ArvB *arv, Indice *idx){
    if(arv == NULL)
        return;
    int pos = chave(arv, idx); //acha o ultimo elemento menor
    if(arv->n_chaves < M-1 && arv->folha == 1 && pos != -1){
        insere_ordenado(arv, idx, pos);
        arv->n_chaves++;
    }
}


void ArvB_insere(ArvB *arv, Indice *idx)
{
    if(Arv_busca(arv, idx) != NULL){
        return;
    }
    ArvB_insere_rec(arv, idx);
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
