#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

int main(void){


    FILE *arq;
    arq = fopen("cachorros.dat", "w+");
    ArvB *arv = ArvB_cria();



    Indice *idx0 = indice_cria(3, 22);
    Indice *idx1 = indice_cria(1, 22);
    Indice *idx2 = indice_cria(2, 22);
    Indice *idx3 = indice_cria(5, 22);
    Indice *idx4 = indice_cria(4, 22);
    Indice *idx5 = indice_cria(20, 22);
    Indice *idx6 = indice_cria(35, 22);
    Indice *idx7 = indice_cria(14, 22);
    Indice *idx8 = indice_cria(18, 22);
    ArvB_insere(arv, idx0);
    ArvB_insere(arv, idx1);
    ArvB_insere(arv, idx2);
    ArvB_insere(arv, idx3);
    ArvB_insere(arv, idx4);
    ArvB_insere(arv, idx5);
    ArvB_insere(arv, idx6);
    ArvB_insere(arv, idx7);
    ArvB_insere(arv, idx8);
    ArvB_printa(arv);

    Indice *idx = indice_cria(14, 22);

    if(Arv_busca(arv,idx))
        printf("Existe");



    //ArvB_limpa(arv);
    return 0;
}
