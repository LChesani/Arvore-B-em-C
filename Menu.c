#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "BTree.h"

struct cachorro
{
    char nome[10];
    char raca[10];
    int idade;
    int id;
};

int le_op(){
    printf("\nMenu\n 1. Mostrar todos\n 2. Pesquisar\n 3. Incluir\n 4. Sair\nInforme uma opcao: ");
    int op;
    scanf("%d", &op);
    return op;
}

void inclui(FILE *arq, ArvB *arv){
    printf("\nDigite as seguintes informacoes: nome, raca, idade, id\n");
    Cachorro c;
    scanf("%s%s%d%d", c.nome, c.raca, &c.idade, &c.id);
    Indice *c_idx = indice_cria(c.id, ftell(arq));
    ArvB_insere(arv, c_idx);
    fwrite(&c, sizeof(c), 1, arq);
}

void mostra_todos(FILE *arq){
    Cachorro c;
    rewind(arq);
    while (fread(&c, sizeof(c), 1, arq)){
        printf("\nnome: %s \t raca: %s \t idade: %d \t id: %d", c.nome, c.raca, c.idade, c.id);
    }
}

void selecionar(int op, FILE *arq, ArvB *arv){
    int id;
    switch (op){
        case 1:
            printf("\nCachorros: \n");
            mostra_todos(arq);
            break;
        case 2:
            printf("\nDigite o id do cachorro: ");
            scanf("%d", &id);
            Indice *idx = indice_cria(id, 0);
            Indice *busca = Arv_busca(arv, idx);
            if(busca != NULL){
                printf("\nAluno encontrado");
                //busca o cachorro no arquivo
            }
            else{
                printf("\n Valor nao encontrado");
            }
            break;
        case 3:
            inclui(arq, arv);
            break;
        case 4:
            printf("\nsaindo...");
            break;
        default:
            printf("\nOpcao invalida!\n");
            break;
    }
}
