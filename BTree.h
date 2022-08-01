typedef struct arvb ArvB;
typedef struct cachorro Cachorro;
typedef struct indice Indice;
ArvB *ArvB_cria(void);
void ArvB_limpa(ArvB *arv);
void ArvB_insere(ArvB *arv, Indice *idx);
void ArvB_printa(ArvB *arv);
Indice *Arv_busca(ArvB *arv, Indice *idx);
