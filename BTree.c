#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#define M 4

typedef struct btree{
    int chave[M-1];
    struct arvb *filho[M];
    int numKeys;
    int isLeaf;
} BTree;




Btree* BTreeCreate(void){
    BTree *arv = (BTree *)malloc(sizeof(BTree));

    if(arv != NULL){
        arv->n = 0;
        arv->isLeaf = 1;
        for(int i = 0; i < M-1; i++){
            arv->chave[i] = 0;
            arv->filho[i] = NULL;
        }
    }
    return arv;
}
