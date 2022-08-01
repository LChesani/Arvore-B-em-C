#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

#define M 4



struct indice{
    int pos_seek;
    int id;
};

struct cachorro{
    char nome[10];
    char raca[10];
    int idade;
    int id;
};

struct arvb{
    Indice keys[M-1];
    struct arvb *filhos[M];
    int n_chaves;
    int folha; //e folha ou nao e
};




ArvB* ArvB_cria(void){
    ArvB *arv = (ArvB*)malloc(sizeof(ArvB));
    arv->n_chaves = 0;
    arv->folha = 1;
    for(int i = 0; i < M-1; i++){
        arv->keys[i].pos_seek = -1;
        arv->keys[i].id = -1;
    }
    for(int i = 0; i < M; i++){
        arv->filhos[i] = NULL;
    }
    return arv;
}

Indice *Arv_busca(ArvB *arv, Indice idx){
    int i = 0;
    while(i < arv->n_chaves && idx.id > arv->keys[i].id){
        i++;
    }
    if(i < arv->n_chaves && idx.id == arv->keys[i].id){
        return &(arv->keys[i]);
    }
    if(arv->folha == 1){
        return NULL;
    }
    return Arv_busca(arv->filhos[i], idx);
}

void ArvB_printa(ArvB *arv){
    if(arv == NULL){
        return;
    }
    for(int i = 0; i < arv->n_chaves; i++){
        printf("%d ", arv->keys[i].id);
    }
    printf("\n");
    for(int i = 0; i < M; i++){
        ArvB_printa(arv->filhos[i]);
    }
}


void ArvB_insere(ArvB *arv, Cachorro *c){
    
}

























void ArvB_limpa(ArvB *arv){
    if(arv == NULL) return;
    for(int i = 0; i < M; i++){
        ArvB_limpa(arv->filhos[i]);
    }
    free(arv);
}
