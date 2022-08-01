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
    for (int i = 0; i < M; i++)
    {
        ArvB_printa(arv->filhos[i]);
    }
}
int busca_chave(int n, Indice *a, int id)
{
    int lo;
    int hi;
    int mid;

    /* invariant: a[lo] < chave <= a[hi] */
    lo = -1;
    hi = n;

    while (lo + 1 < hi)
    {
        mid = (lo + hi) / 2;
        if (a[mid].id == id)
        {
            return mid;
        }
        else if (a[mid].id < id)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }

    return hi;
}



ArvB *ArvB_insere_rec(ArvB* b, Indice *chave, int *median)
{
    int pos;
    int mid;
    ArvB *b2;

    pos = busca_chave(b->n_chaves, b->chaves, chave->id);

    if (pos < b->n_chaves && b->chaves[pos].id == chave->id)
    {
        return 0;
    }

    if (b->folha){

        memmove(&b->chaves[pos + 1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->n_chaves - pos));
        b->chaves[pos] = *chave;
        b->n_chaves++;
    }
    else
    {

        b2 = ArvB_insere_rec(b->filhos[pos], chave, &mid);

        if (b2)
        {

            memmove(&b->chaves[pos + 1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->n_chaves - pos));

            memmove(&b->filhos[pos + 2], &b->filhos[pos + 1], sizeof(*(b->chaves)) * (b->n_chaves - pos));
            
            
            Indice *ind = (Indice*) malloc(sizeof(Indice));
            ind->id = mid;
            ind->pos_seek = 1;
            b->chaves[pos] = *ind;
            b->filhos[pos + 1] = b2;
            b->n_chaves++;
        }
    }

    if (b->n_chaves >= M-1)
    {
        mid = b->n_chaves / 2;

        *median = b->chaves[mid].id;

        b2 = malloc(sizeof(*b2));

        b2->n_chaves = b->n_chaves - mid - 1;
        b2->folha = b->folha;

        memmove(b2->chaves, &b->chaves[mid + 1], sizeof(*(b->chaves)) * b2->n_chaves);
        if (!b->folha)
        {
            memmove(b2->filhos, &b->filhos[mid + 1], sizeof(*(b->filhos)) * (b2->n_chaves + 1));
        }

        b->n_chaves = mid;

        return b2;
    }
    else
    {
        return 0;
    }
}


void ArvB_insere(ArvB *b, Indice *chave)
  {
      ArvB *b1;   /* new left child */
      ArvB *b2;   /* new right child */
      int median;
  
      b2 = ArvB_insere_rec(b, chave, &median);
  
      if(b2) {
          /* basic issue here is that we are at the root */
          /* so if we split, we have to make a new root */
  
          b1 = malloc(sizeof(*b1));
          assert(b1);
  
          /* copy root to b1 */
          memmove(b1, b, sizeof(*b));
  
          /* make root point to b1 and b2 */
          b->n_chaves = 1;
          b->folha = 0;
          b->chaves[0].id = median;
          b->filhos[0] = b1;
          b->filhos[1] = b2;
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
