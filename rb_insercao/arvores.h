#ifndef _ARVORES_H_
#define _ARVORES_H_

#define PRETO 1
#define VERMELHO 0

typedef struct _node{
    void * reg;
    struct _node * esq;
    struct _node * dir;
    int h;
    struct _node * pai;
    int cor;
}tnode;

typedef struct _arv{
    tnode * raiz;
    int (*compara)(const void *a, const void *b);
}tarv;


void   rb_constroi(tarv * parv,int (*cmp)(const void *a, const void *b));
int    rb_insere(tarv * parv, void * preg);


void   abb_constroi(tarv * parv,int (*cmp)(const void *a, const void *b));
int    abb_insere(tarv * parv, void * preg);
void * abb_busca(tarv * parv, void * preg);
int    abb_remove(tarv * parv, void * preg);
int    abb_destroi(tarv * parv);



void   avl_constroi(tarv * parv,int (*cmp)(const void *a, const void *b));
int    avl_insere(tarv * parv, void * preg);
int    avl_remove(tarv * parv, void * preg);

#endif
