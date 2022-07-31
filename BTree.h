typedef struct btree BTree;
BTree *BTreeCreate(void);
BTree *BTreeFree(BTree *arv);
BTree *BTreeInsert(BTree *arv, int ch);
void BTreePrint(BTree *arv);
Btree *BTreeSearch(BTree *arv, int ch);
