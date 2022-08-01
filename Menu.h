#include "BTree.h"

typedef struct cachorro Cachorro;

int le_op();
void inclui(FILE *arq, ArvB *arv);
void mostra_todos(FILE *arq);
void selecionar(int op, FILE *arq, ArvB *arv);
ArvB *importa_arvore(FILE *arq);
