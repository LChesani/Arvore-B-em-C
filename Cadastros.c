#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"


int main(void){


    FILE *arq;
    arq = fopen("cachorros.dat", "w+");
    ArvB *arv = ArvB_cria();



    Cachorro *c = (Cachorro*)malloc(sizeof(Cachorro));
    c->id = 1;
    strcpy(c->nome, "Bobby");
    strcpy(c->raca, "Labrador");
    c->idade = 2;
    ArvB_insere(arv, c);
    ArvB_printa(arv);








    ArvB_limpa(arv);
    return 0;
}
