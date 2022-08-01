#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"
#include "Menu.h"
#include <unistd.h>
int main(void){


    FILE *arq;
    int op;
    if (access("canil.dat", F_OK) == 0)
        arq = fopen("canil.dat", "r+"); // arquivo existe
    else
        arq = fopen("canil.dat", "w+"); // arquivo nao existia
    ArvB *arv = importa_arvore(arq);
    
    do{
        op = le_op();
        selecionar(op, arq, arv);


    }while(op != 4);

    fclose(arq);
    ArvB_limpa(arv);
    return 0;
}
