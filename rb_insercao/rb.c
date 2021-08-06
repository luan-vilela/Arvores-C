#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

#define DDIR 1
#define DESQ -1

typedef struct _reg{
    int rga;
}treg;







void RD(tnode ** pnode){
    tnode *x,*y,*b;
    tnode *aux;
    x = *pnode;
    y = x->esq;
    b = y->dir;

    x->esq = b;
    y->dir = x;
    *pnode = y;


    if (b != NULL)
       b->pai = x;

    y->pai = x->pai;
    x->pai = y;


}
void RE(tnode ** pnode){
    tnode *x,*y,*b;
    tnode *aux;
    y = *pnode;
    x = y->dir;
    b = x->esq;
    
    y->dir = b;
    x->esq = y; 
    *pnode = x;

    if (b != NULL)
        b->pai = y;

    x->pai = y->pai;
    y->pai = x;

}



void   rb_constroi(tarv * parv,int (*cmp)(const void *a, const void *b)){
    parv->raiz = NULL;
    parv->compara = cmp;
}

int obtem_cor(tnode * node){
    int ret = PRETO;
    if (node == NULL){
        ret = PRETO;
    }else{
        ret = node->cor;
    }
    return ret;
}

int _fix_up(tarv * parv, tnode * filho){
    tnode * pai;
    tnode * avo;
    tnode * tio;
    tnode ** pavo;
    int seta_pai, seta_filho;
    pai = filho->pai;
    while(obtem_cor(pai) == VERMELHO){
        avo = pai->pai;
        if (pai->esq == filho){
            seta_filho = DESQ;
        }else{
            seta_filho = DDIR;
        }
        if (avo->esq == pai){
            seta_pai = DESQ;
        }else{
            seta_pai = DDIR;
        }
        if (seta_pai == DESQ){
            tio = avo->dir;
        }else{
            tio = avo->esq;
        }
        
        if (obtem_cor(tio)==VERMELHO){/*caso 1*/
            tio->cor = PRETO;
            pai->cor = PRETO;
            avo->cor = VERMELHO;
            filho = avo;
            pai = filho->pai;
        }else{
            if (seta_pai * seta_filho < 0){ /* caso 2 cotovelo*/
                if (seta_filho == DESQ){
                    RD(&(avo->dir));
                }else{
                    RE(&(avo->esq));
                }
            }
            if (parv->raiz == avo){ /* encontra o pont de pont do avo*/
                pavo = &(parv->raiz);
            }else{
                if (avo->pai->esq == avo){
                    pavo = &(avo->pai->esq);
                }else{
                    pavo = &(avo->pai->dir);
                }
            }

            if (seta_pai == DESQ){  /* Caso 3  sem cotovelo*/
                RD(pavo);
            }else{
                RE(pavo);
            }
            avo = *pavo;
            avo->cor = PRETO;
            avo->esq->cor = VERMELHO;
            avo->dir->cor = VERMELHO;
            pai = avo; /*necessario pois o pai e vermelho, fazendo o algoritmo entrar novamente no laco*/
        }
    }
}



int rb_insere(tarv * parv, void * preg){
    tnode * filho;
    tnode * pai;
    filho = parv->raiz;
    pai = parv->raiz;
    int ret;
    
    while(filho != NULL){
        pai = filho;
        if (parv->compara(filho->reg,preg) < 0){
            filho = filho->dir;
        }else{
            filho = filho->esq;
        }
    }
    filho = (tnode *)malloc(sizeof(tnode));
    if (filho == NULL){
        ret = 0;
    }else{
        filho->reg = preg;
        filho->esq = NULL;
        filho->dir = NULL;
        filho->cor = VERMELHO;
        filho->pai = pai;
        if (parv->raiz == NULL){
            parv->raiz = filho;
        }else{
            if (parv->compara(pai->reg,preg) < 0){
                pai->dir  = filho;
            }else{
                pai->esq  = filho;
            }
            ret = _fix_up(parv,filho);
        }
    }
    parv->raiz->cor = PRETO;
    return ret;
}

