#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arvores.h"

typedef struct _reg{
    int rga;
}treg;

int compara(const void *a, const void *b){
    return (*(treg *)a).rga - (*(treg *)b).rga;
}

treg * aloca_reg(int chave){
    treg * aux;
    aux = (treg *) malloc(sizeof(treg));
    aux->rga = chave;
    return aux;
}


void imprime_arvore(tnode * arv,int prof){
    int anda = 3;
    int verbose = 0;
    int i;
    char cor;
    if (arv != NULL){
        imprime_arvore(arv->dir,prof+anda);
        for (i=0;i<prof;i++)
            printf(" ");
        cor = arv->cor == VERMELHO?'v':'p';
        if (verbose)
            printf("%c%d %p %p\n",cor,((treg *)arv->reg)->rga, arv,arv->pai);
        else
            printf("%c%d\n",cor,((treg *)arv->reg)->rga);
        imprime_arvore(arv->esq,prof+anda);
        if (prof == 0)
            printf("------\n");
        
    }
}





void test_construtor(){
    tarv arv;
    rb_constroi(&arv,&compara);
    treg * a;
    treg * b;
    a = aloca_reg(10);
    b = aloca_reg(0);
    assert(arv.compara(a,b)==10);
    assert(arv.compara(b,a)==-10);
    b->rga = 10;
    assert(arv.compara(b,a)==0);

}

void test_insere(){
    tarv arv;
    treg * aux;
    rb_constroi(&arv,&compara);
    aux = aloca_reg(10);
    rb_insere(&arv,aloca_reg(10));
    assert(compara(arv.raiz->reg,aux) == 0);
    assert(arv.raiz->cor == PRETO);
    
    
    rb_insere(&arv,aloca_reg(50));
    imprime_arvore(arv.raiz,0);

    aux->rga = 10; assert(compara(arv.raiz->reg,aux) == 0);    assert(arv.raiz->cor == PRETO);
    aux->rga = 50; assert(compara(arv.raiz->dir->reg,aux) == 0);assert(arv.raiz->dir->cor == VERMELHO);
    
    assert(arv.raiz->pai == NULL);
    assert(arv.raiz->dir->pai == arv.raiz);


    rb_insere(&arv,aloca_reg(80));
    imprime_arvore(arv.raiz,0);

    aux->rga = 50; assert(compara(arv.raiz->reg,aux) == 0)     ;assert(arv.raiz->cor == PRETO);
    aux->rga = 10; assert(compara(arv.raiz->esq->reg,aux) == 0);assert(arv.raiz->esq->cor == VERMELHO);
    aux->rga = 80; assert(compara(arv.raiz->dir->reg,aux) == 0);assert(arv.raiz->dir->cor == VERMELHO);

    assert(arv.raiz->pai == NULL);
    assert(arv.raiz->esq->pai == arv.raiz);
    assert(arv.raiz->dir->pai == arv.raiz);


    rb_insere(&arv,aloca_reg(30));
    imprime_arvore(arv.raiz,0);

    aux->rga = 50; assert(compara(arv.raiz->reg,aux) == 0)     ;assert(arv.raiz->cor == PRETO);
    aux->rga = 10; assert(compara(arv.raiz->esq->reg,aux) == 0);assert(arv.raiz->esq->cor == PRETO);
    aux->rga = 80; assert(compara(arv.raiz->dir->reg,aux) == 0);assert(arv.raiz->dir->cor == PRETO);

    aux->rga = 30; assert(compara(arv.raiz->esq->dir->reg,aux) == 0);assert(arv.raiz->esq->dir->cor == VERMELHO);
    
    rb_insere(&arv,aloca_reg(5));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(20));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(40));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(25));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(90));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(85));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(100));
    imprime_arvore(arv.raiz,0);
    rb_insere(&arv,aloca_reg(95));
    imprime_arvore(arv.raiz,0);


    aux->rga = 30; assert(compara(arv.raiz->reg,aux) == 0)     ;assert(arv.raiz->cor == PRETO);
    aux->rga = 10; assert(compara(arv.raiz->esq->reg,aux) == 0);assert(arv.raiz->esq->cor == PRETO);
    aux->rga = 50; assert(compara(arv.raiz->dir->reg,aux) == 0);assert(arv.raiz->dir->cor == PRETO);


    aux->rga = 5  ; assert(compara(arv.raiz->esq->esq->reg,aux) == 0) ;assert(arv.raiz->esq->esq->cor == PRETO);
    aux->rga = 20 ; assert(compara(arv.raiz->esq->dir->reg,aux) == 0) ;assert(arv.raiz->esq->dir->cor == PRETO);

    aux->rga = 40  ; assert(compara(arv.raiz->dir->esq->reg,aux) == 0);assert(arv.raiz->dir->esq->cor == PRETO);
    aux->rga = 85  ; assert(compara(arv.raiz->dir->dir->reg,aux) == 0);assert(arv.raiz->dir->dir->cor == VERMELHO);



    aux->rga = 25 ; assert(compara(arv.raiz->esq->dir->dir->reg,aux) == 0) ;assert(arv.raiz->esq->dir->dir->cor == VERMELHO);
    
    aux->rga = 80 ; assert(compara(arv.raiz->dir->dir->esq->reg,aux) == 0) ;assert(arv.raiz->dir->dir->esq->cor == PRETO);
    aux->rga = 95 ; assert(compara(arv.raiz->dir->dir->dir->reg,aux) == 0) ;assert(arv.raiz->dir->dir->dir->cor == PRETO);

    aux->rga = 90  ; assert(compara(arv.raiz->dir->dir->dir->esq->reg,aux) == 0) ;assert(arv.raiz->dir->dir->dir->esq->cor == VERMELHO);
    aux->rga = 100 ; assert(compara(arv.raiz->dir->dir->dir->dir->reg,aux) == 0) ;assert(arv.raiz->dir->dir->dir->dir->cor == VERMELHO);
    printf("PASSOU!\n");
}

int main(void){
    test_construtor();
    test_insere();
}
