#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"abb.h"



typedef struct _reg{
    int id;
    int idade;
}treg;

int compara(const void *a, const void *b){
    return (*(treg *)a).id - (*(treg *)b).id; 
}

treg * aloca_reg(int id){
    treg * aux = (treg *)malloc(sizeof(treg));
    aux->id = id;
    return aux;
}

int    test_construtor(){
    int a,b;
    tarv arv;
    abb_constroi(&arv,&compara);
    a = 10;
    b = 20;
    assert(arv.raiz == NULL);
    assert(arv.compara(&a,&b) == -10);
    assert(arv.compara(&b,&a) == 10);
    assert(arv.compara(&b,&b) == 0);
    assert(arv.compara(&a,&a) == 0);
    abb_destroi(&arv);
    printf("Construcao OK\n");
}
int    test_insere(){
    int v[] = {30,15,50,7,20,35,55};
    int n = sizeof(v)/sizeof(v[0]);
    int i;
    int a,b;
    tarv arv;
    abb_constroi(&arv,&compara);
    
    for(i = 0; i < n;i++)
        abb_insere(&arv,aloca_reg(v[i]));
    


    tnode * pnode    = arv.raiz;
    treg * aux       = (treg *)malloc(sizeof(treg));
    treg * aux_busca = (treg *)malloc(sizeof(treg));

    aux->id = 30;assert(compara(pnode->reg,aux)==0);
    aux->id = 15;assert(compara(pnode->esq->reg,aux)==0);
    aux->id = 50;assert(compara(pnode->dir->reg,aux)==0);
    aux->id = 7 ;assert(compara(pnode->esq->esq->reg,aux)==0);
    aux->id = 20;assert(compara(pnode->esq->dir->reg,aux)==0);
    aux->id = 35;assert(compara(pnode->dir->esq->reg,aux)==0);
    aux->id = 55;assert(compara(pnode->dir->dir->reg,aux)==0);

    assert(pnode->esq->esq->esq==NULL);
    assert(pnode->esq->esq->dir==NULL);
    assert(pnode->esq->dir->esq==NULL);
    assert(pnode->esq->dir->dir==NULL);
    assert(pnode->dir->esq->esq==NULL);    
    assert(pnode->dir->esq->dir==NULL);    
    assert(pnode->dir->dir->dir==NULL);
    assert(pnode->dir->dir->esq==NULL);
    
    abb_destroi(&arv);
    printf("Insercao OK\n");
}
int    test_busca(){
    int v[] = {30,15,50,7,20,35,55};
    int n = sizeof(v)/sizeof(v[0]);
    int i;
    int a,b;
    tarv arv;
    abb_constroi(&arv,&compara);
    
    for(i = 0; i < n;i++)
        abb_insere(&arv,aloca_reg(v[i]));
    


    tnode * pnode    = arv.raiz;
    treg * aux       = (treg *)malloc(sizeof(treg));
    treg * aux_busca = (treg *)malloc(sizeof(treg));

  
    aux->id = 0 ;aux_busca = abb_busca(&arv,aux);assert(aux_busca==NULL);
    aux->id = 30;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->reg,aux_busca)==0);
    aux->id = 15;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->esq->reg,aux_busca)==0);
    aux->id = 50;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->dir->reg,aux_busca)==0);
    aux->id = 7 ;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->esq->esq->reg,aux_busca)==0);
    aux->id = 20;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->esq->dir->reg,aux_busca)==0);
    aux->id = 35;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->dir->esq->reg,aux_busca)==0);
    aux->id = 55;aux_busca = abb_busca(&arv,aux);assert(compara(pnode->dir->dir->reg,aux_busca)==0);

    printf("Busca OK\n");
}


int    test_remove(){
    int v[] = {30,15,50,7,20,35,55};
    int n = sizeof(v)/sizeof(v[0]);
    int i;
    int a,b;
    tarv arv;
    abb_constroi(&arv,&compara);
    
    for(i = 0; i < n;i++)
        abb_insere(&arv,aloca_reg(v[i]));
    


    tnode * pnode    = arv.raiz;
    treg * aux       = (treg *)malloc(sizeof(treg));
    treg * aux_busca = (treg *)malloc(sizeof(treg));

    aux->id = 0 ;assert(abb_remove(&arv,aux)==0);
    
    /* Remove 55 */
    aux->id = 55;assert(abb_remove(&arv,aux)==1);


    assert(pnode->dir->dir == NULL);
    
    aux->id = 30;assert(compara(pnode->reg,aux)==0);
    aux->id = 15;assert(compara(pnode->esq->reg,aux)==0);
    aux->id = 50;assert(compara(pnode->dir->reg,aux)==0);
    aux->id = 7 ;assert(compara(pnode->esq->esq->reg,aux)==0);
    aux->id = 20;assert(compara(pnode->esq->dir->reg,aux)==0);
    aux->id = 35;assert(compara(pnode->dir->esq->reg,aux)==0);

    assert(pnode->esq->esq->esq==NULL);
    assert(pnode->esq->esq->dir==NULL);
    assert(pnode->esq->dir->esq==NULL);
    assert(pnode->esq->dir->dir==NULL);
    assert(pnode->dir->esq->esq==NULL);    
    assert(pnode->dir->esq->dir==NULL);    

     /* Remove 15 */
    aux->id = 15;assert(abb_remove(&arv,aux)==1);


    assert(pnode->esq->dir == NULL);
    
    aux->id = 30;assert(compara(pnode->reg,aux)==0);
    aux->id = 20;assert(compara(pnode->esq->reg,aux)==0);
    aux->id = 50;assert(compara(pnode->dir->reg,aux)==0);
    aux->id = 7 ;assert(compara(pnode->esq->esq->reg,aux)==0);
    aux->id = 35;assert(compara(pnode->dir->esq->reg,aux)==0);

    assert(pnode->esq->esq->esq==NULL);
    assert(pnode->esq->esq->dir==NULL);
    assert(pnode->dir->esq->esq==NULL);    
    assert(pnode->dir->esq->dir==NULL);    
 
     
    abb_insere(&arv,aloca_reg(40));

     /* Remove 30 */
    aux->id = 30;assert(abb_remove(&arv,aux)==1);

    aux->id = 35;assert(compara(pnode->reg,aux)==0);
    aux->id = 20;assert(compara(pnode->esq->reg,aux)==0);
    aux->id = 50;assert(compara(pnode->dir->reg,aux)==0);
    aux->id = 7 ;assert(compara(pnode->esq->esq->reg,aux)==0);
    aux->id = 40;assert(compara(pnode->dir->esq->reg,aux)==0);

    assert(pnode->esq->esq->esq==NULL);
    assert(pnode->esq->esq->dir==NULL);
    assert(pnode->dir->esq->esq==NULL);    
    assert(pnode->dir->esq->dir==NULL);    
 

    assert(pnode->esq->dir ==NULL);
    assert(pnode->dir->dir ==NULL);


    /* remove 20*/
    aux->id = 20;assert(abb_remove(&arv,aux)==1);

    aux->id = 35;assert(compara(pnode->reg,aux)==0);
    aux->id = 7;assert(compara(pnode->esq->reg,aux)==0);
    aux->id = 50;assert(compara(pnode->dir->reg,aux)==0);
    aux->id = 40;assert(compara(pnode->dir->esq->reg,aux)==0);

    assert(pnode->esq->esq==NULL);
    assert(pnode->esq->dir==NULL);
    assert(pnode->dir->esq->esq==NULL);    
    assert(pnode->dir->esq->dir==NULL);    


    /* remove 50*/
    aux->id = 50;assert(abb_remove(&arv,aux)==1);

    aux->id = 35;assert(compara(pnode->reg,aux)==0);
    aux->id = 7 ;assert(compara(pnode->esq->reg,aux)==0);
    aux->id = 40;assert(compara(pnode->dir->reg,aux)==0);

    assert(pnode->esq->esq==NULL);
    assert(pnode->esq->dir==NULL);
    assert(pnode->dir->esq==NULL);    
    assert(pnode->dir->dir==NULL);    

    /* remove 35*/
    aux->id = 35;assert(abb_remove(&arv,aux)==1);

    aux->id = 40;assert(compara(pnode->reg,aux)==0);
    aux->id = 7 ;assert(compara(pnode->esq->reg,aux)==0);

    assert(pnode->esq->esq==NULL);
    assert(pnode->esq->dir==NULL);
    assert(pnode->dir==NULL);    

    /* remove 40*/
    aux->id = 40;assert(abb_remove(&arv,aux)==1);

    aux->id = 7 ;assert(compara(arv.raiz->reg,aux)==0);

    assert(arv.raiz->esq==NULL);
    assert(arv.raiz->dir==NULL);    

    /* remove 7*/
    aux->id = 7;assert(abb_remove(&arv,aux)==1);

    assert(arv.raiz==NULL);


    assert(abb_destroi(&arv)==0);

    printf("Remove OK\n");

}
int main(void){
    test_construtor();
    test_insere();
    test_busca();
    test_remove();
    return 0;
}

