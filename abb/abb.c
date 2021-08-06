#include<stdio.h>
#include<stdlib.h>
#include"abb.h"

void abb_constroi(tarv * parv,int (*cmp)(const void *a, const void *b)){
   parv->raiz = NULL; 
   parv->compara = cmp;
}
int _insere_arv(tarv * parv, tnode **pnode, void * preg){
    int ret=1;
    if (*pnode == NULL){
        *pnode = (tnode *)malloc(sizeof(tnode));
        if (*pnode == NULL)
            ret = 0;
        else{
            (*pnode)->reg       = preg;
            (*pnode)->esq       = NULL;
            (*pnode)->dir       = NULL;
        }
    }else{
        if (parv->compara(((*pnode)->reg), preg) > 0){
            ret = _insere_arv(parv,&((*pnode)->esq) , preg);
        }else{
            ret = _insere_arv(parv,&((*pnode)->dir) , preg);
        }
    }

}


int abb_insere(tarv * parv, void * preg){
    return _insere_arv(parv,&(parv->raiz),preg);
}

void * _busca_reg(tarv * parv, tnode ** pnode, void * preg){
    void * ret;
    if (*pnode == NULL){
        ret = NULL;
    }else if(parv->compara(((*pnode)->reg), preg)==0){
        ret = (*pnode)->reg;
    }else{
        if (parv->compara(((*pnode)->reg), preg) > 0){
            ret = _busca_reg(parv,&((*pnode)->esq) , preg);
        }else{
            ret = _busca_reg(parv,&((*pnode)->dir) , preg);
        }
    }
    return ret;
}

void * abb_busca(tarv * parv, void * preg){
    return _busca_reg(parv,&(parv->raiz),preg);
}


tnode ** busca_pont(tarv * parv, tnode ** pnode, void * preg){
    tnode ** ret;
    if (*pnode == NULL){
        ret = NULL;
    }else if(parv->compara((*pnode)->reg,preg)==0){
        ret = pnode;
    }else{
        if (parv->compara(((*pnode)->reg), preg) > 0){
            ret = busca_pont(parv,&((*pnode)->esq), preg);
        }else{
            ret = busca_pont(parv,&((*pnode)->dir), preg);
        }
    }
    return ret;
}

int remove_raiz(tnode ** pnode){
    int ret = 0;
    tnode * aux;
    if (*pnode!=NULL){
        if (((*pnode)->esq == NULL) && (*pnode)->dir == NULL){ /* Caso 1*/
            free((*pnode)->reg);
            free(*pnode);
            *pnode = NULL;
            ret = 1;
        }else if ((*pnode)->esq == NULL && (*pnode)->dir != NULL){ /* Caso 2*/
            free((*pnode)->reg);
            aux = *pnode;
            *pnode = (*pnode)->dir;
            free(aux);
            ret = 1;

        }else if ((*pnode)->esq != NULL && (*pnode)->dir == NULL){
            free((*pnode)->reg);
            aux = *pnode;
            *pnode = (*pnode)->esq;
            free(aux);
            ret = 1;
        }else{ /*Caso 3*/
             /*encontrar sucessor*/
             aux = (*pnode)->dir;
             tnode ** paux =  &((*pnode)->dir);
             while(aux->esq != NULL){
                 paux = &(aux->esq);
                 aux = aux->esq;
             }
             free((*pnode)->reg);
             (*pnode)->reg = aux->reg;
             *paux = aux->dir;
             free(aux);
             ret = 1;
        }
    }
    return ret;
}

int abb_remove(tarv *parv, void * preg){
    int ret = 0;
    tnode ** aux = busca_pont(parv,&(parv->raiz),preg);
    if (aux != NULL){
        ret = remove_raiz(aux);
    }
    return ret;
}

void _destroi(tnode * pnode){
    if (pnode != NULL){
        _destroi(pnode->esq);
        _destroi(pnode->dir);
        free(pnode->reg);
        free(pnode);
    }
}


int    abb_destroi(tarv * parv){
    int ret = 0;
    if (parv->raiz != NULL){
        _destroi(parv->raiz);
        ret = 1;
    }
    return ret;
}

