#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no* prox;
};

typedef struct{
    struct no* cab;
    struct no* cauda;
}Lista;

int vazia(Lista* l){
    return(l->cab == NULL);
}

Lista* criar_lista_vazia(){
    Lista *l = (Lista*) malloc (sizeof(Lista));
    l->cab = NULL;
    l->cauda = NULL;
}

void insere(Lista* l, int info){
    struct no* aux = malloc (sizeof(struct no));
    aux->info = info;
    aux->prox = NULL;

    if(vazia(l)){
        l->cab = aux;
        l->cauda = aux;
    }
    else {
        l->cauda->prox = aux;
        l->cauda = aux;
    }
}

Lista* remover(Lista* l, int info){
    if(vazia(l))
        return NULL;

    if(l->cab == l->cauda)
        return NULL;
    
    if(l->cab->info == info){
        l->cab = l->cab->prox;
        return l;
    }
    /*struct no* aux = l->cab->prox;
    while(aux != NULL){
        if(aux->info == info){
            struct no* temp = aux->prox;
            free(aux);

        }
    }*/
    
    return l;
}

void imprimir(Lista* l){
    struct no* aux = l->cab;
    while (aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int main(){
    Lista* l = criar_lista_vazia();

    insere(l, 4);
    insere(l, 5);
    insere(l, 8);

    imprimir(l);    

    l = remover(l, 5);
    imprimir(l);

    return 0;
}