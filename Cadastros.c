#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

int main(void){


    FILE *arq;
    arq = fopen("cachorros.dat", "w+");
    ArvB *arv = ArvB_cria();



    Indice *idx;
    

    ArvB_printa(arv);





    //ArvB_limpa(arv);
    return 0;
}
