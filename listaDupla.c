#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no* prox;
    struct no* ant;
}Lista;

int vazia(Lista* l){
    return (l == NULL); 
}

Lista* insereCab(Lista *l, int info){ //insere cabeça
    Lista* aux = (Lista*) malloc (sizeof(Lista));
    aux->info = info;
    aux->ant = NULL;

    if(!vazia(l)){
        aux->prox = l;
        l->ant = aux;
    }
    else {
        aux->prox = NULL;
    }

    return aux;    
}

Lista* insere(Lista* l, int info){
    Lista* aux = (Lista*) malloc (sizeof(Lista));
    aux->info = info;
    aux->prox = NULL;

    if(vazia(l)){
        aux->ant = NULL;
        return aux;
    }
    Lista *temp = l;
    while(temp->prox != NULL){
        temp = temp->prox;
    }

    temp->prox = aux;
    aux->ant = temp;

    return l;
}

Lista* remover_dupla(Lista* l, int info){
    if(vazia(l))
        return NULL;

    if(l->ant == NULL && l->info == info){
        if(l->prox == NULL){
            free(l);
            return NULL;
        }
        Lista* aux = l->prox;
        aux->ant = NULL;
        free(l);
        return aux;
    }

    while(l != NULL){
        if(l->info == info){
            Lista* aux;
            aux->prox = l->prox;
            l->prox->ant = aux;
            aux->ant = l->ant;
            l->ant->prox = aux;
            free(l);
            return aux;
        }


    }
}

void imprimeLista(Lista* l){
        if(!vazia(l)){
        printf("%d ", l->info);
        imprimeLista(l->prox);
    } 
    else    
        printf("\n");  
}

int main(){
    Lista *l = NULL;

    l = insere(l, 1);
    l = insere(l, 2);
    l = insere(l, 30);

    imprimeLista(l);


    return 0;
}