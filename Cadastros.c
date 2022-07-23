#include <stdio.h>
#include <stdlib.h>
#define ORDEM 4

typedef struct arvb{
    int chave[ORDEM-1];
    struct arvb *filho[ORDEM];
    int n;
} ArvB;

ArvB *arvb_cria(void){
    int i;
    ArvB *arv;
    arv = (ArvB*)malloc(sizeof(ArvB));
    if(arv != NULL){
        arv->n = 0;
        for(i=0; i<ORDEM; i++)
            arv->filho[i] = NULL;
    }
    return arv;
}
ArvB *arvb_libera(ArvB *arv){
    int i;
    if(arv != NULL){
        for(i=0; i<ORDEM; i++)
            arvb_libera(arv->filho[i]);
        free(arv);
    }
    return NULL;
}

ArvB *arvb_insere(ArvB *arv, int ch){
    int i;
    if(arv == NULL)
        arv = arvb_cria();
    else if(arv->n < ORDEM-1){
        for(i=arv->n-1; i>=0 && ch < arv->chave[i]; i--)
            arv->chave[i+1] = arv->chave[i];
        arv->chave[i+1] = ch;
        arv->n++;
    }
    else{
        ArvB *filho;
        int meio = (ORDEM-1)/2;
        if(arv->filho[meio] == NULL)
            arv->filho[meio] = arvb_cria();
        arv->filho[meio] = arvb_insere(arv->filho[meio], ch);
        for(i=meio-1; i>=0 && arv->filho[meio]->chave[0] < arv->chave[i]; i--)
            arv->chave[i+1] = arv->chave[i];
        arv->chave[i+1] = arv->filho[meio]->chave[0];
        filho = arv->filho[meio];
        for(i=meio; i<ORDEM-1; i++)
            arv->filho[i] = arv->filho[i+1];
        arv->filho[i] = filho->filho[0];
        for(i=0; i<filho->n; i++)
            arv->filho[i] = filho->filho[i+1];
        arv->n = ORDEM-1;
        arvb_libera(filho);
    }
    return arv;
}

void arvb_imprime(ArvB *arv){
    int i;
    if(arv != NULL){
        for(i=0; i<arv->n; i++)
            printf("%d ", arv->chave[i]);
        printf("\n");
        for(i=0; i<ORDEM; i++)
            arvb_imprime(arv->filho[i]);
    }
}

ArvB *arvb_busca(ArvB *arv, int ch){
    int i;
    if(arv == NULL || ch == arv->chave[0])
        return arv;
    else{
        for(i=0; i<arv->n && ch > arv->chave[i]; i++);
        return arvb_busca(arv->filho[i], ch);
    }
}


int main(void){


    ArvB *arv = arvb_cria();
    arvb_insere(arv, 10);
    arvb_insere(arv, 5);
    arvb_imprime(arv);




    return 0;
}
