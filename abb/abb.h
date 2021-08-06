#ifndef _ABB_H_
#define _ABB_H_

typedef struct _node{
    void * reg;
    struct _node * esq;
    struct _node * dir;
}tnode;

typedef struct _arv{
    tnode * raiz;
    int (*compara)(const void *a, const void *b);
}tarv;


void   abb_constroi(tarv * parv,int (*cmp)(const void *a, const void *b));
int    abb_insere(tarv * parv, void * preg);
void * abb_busca(tarv * parv, void * preg);
int    abb_remove(tarv * parv, void * preg);
int    abb_destroi(tarv * parv);
#endif
