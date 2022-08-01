#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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


Indice *indice_cria(int id, int pos_seek){
    Indice *idx = (Indice*) malloc(sizeof(Indice));
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
    for (int i = 0; i < arv->n_chaves+1; i++)
    {
        ArvB_printa(arv->filhos[i]);
    }
}
int busca_pos_chave(ArvB *arv, int id)
{
    for(int i = 0; i < arv->n_chaves; i++){
        if(arv->chaves[i].id > id){
           return i;
        }
    }
    return arv->n_chaves;
}

void desloca_chaves(ArvB *arv, int pos){
    for(int i = arv->n_chaves; i > pos; i--){
        arv->chaves[pos] = arv->chaves[pos-1];
    }
}

ArvB *ArvB_insere_rec(ArvB* arv, Indice *chave, int *median)
{
    int pos;
    int mid;
    ArvB *arv2;

    pos = busca_pos_chave(arv, chave->id);

    if (pos < arv->n_chaves && arv->chaves[pos].id == chave->id)
    {
        return 0;
    }

    if (arv->folha){
        memmove(&arv->chaves[pos + 1], &arv->chaves[pos], sizeof(*(arv->chaves)) * (arv->n_chaves - pos));
        arv->chaves[pos] = *chave;
        arv->n_chaves++;
    }
    else
    {

        arv2 = ArvB_insere_rec(arv->filhos[pos], chave, &mid);

        if (arv2)
        {

            memmove(&arv->chaves[pos + 1], &arv->chaves[pos], sizeof(*(arv->chaves)) * (arv->n_chaves - pos));
        
            memmove(&arv->filhos[pos + 2], &arv->filhos[pos + 1], sizeof(*(arv->chaves)) * (arv->n_chaves - pos));
            
            
            Indice *ind = (Indice*) malloc(sizeof(Indice));
            ind->id = mid;
            ind->pos_seek = 1;
            arv->chaves[pos] = *ind;
            arv->filhos[pos + 1] = arv2;
            arv->n_chaves++;
        }
    }

    if (arv->n_chaves >= M-1)
    {
        mid = arv->n_chaves / 2;

        *median = arv->chaves[mid].id;

        arv2 = malloc(sizeof(*arv2));

        arv2->n_chaves = arv->n_chaves - mid - 1;
        arv2->folha = arv->folha;

        memmove(arv2->chaves, &arv->chaves[mid + 1], sizeof(*(arv->chaves)) * arv2->n_chaves);
        if (!arv->folha)
        {
            memmove(arv2->filhos, &arv->filhos[mid + 1], sizeof(*(arv->filhos)) * (arv2->n_chaves + 1));
        }

        arv->n_chaves = mid;

        return arv2;
    }
    else
    {
        return 0;
    }
}


void ArvB_insere(ArvB *arv, Indice *chave)
  {
      ArvB *arv1;   /* new left child */
      ArvB *arv2;   /* new right child */
      int median;
  
      arv2 = ArvB_insere_rec(arv, chave, &median);
  
      if(arv2) {
          /* basic issue here is that we are at the root */
          /* so if we split, we have to make a new root */
  
          arv1 = malloc(sizeof(*arv1));
          assert(arv1);
  
          /* copy root to b1 */
          memmove(arv1, arv, sizeof(*arv));
  
          /* make root point to b1 and b2 */
          arv->n_chaves = 1;
          arv->folha = 0;
          arv->chaves[0].id = median;
          arv->filhos[0] = arv1;
          arv->filhos[1] = arv2;
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
