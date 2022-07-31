#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>



int main(void){


    BTree *arv = BtreeCreate();
    BtreeInsert(arv, 10);
    BtreeInsert(arv, 5);
    BtreeInsert(arv);




    return 0;
}
