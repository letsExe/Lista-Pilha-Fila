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

Lista* insere(Lista* l, int info){
    Lista* aux = malloc (sizeof(Lista));
    aux->info = info;

    if(vazia(l)){
        aux->ant = aux;
        aux->prox = aux;
    }
    else {
        aux->prox = l;
        aux->ant = l->ant;
        l->ant = aux;
        aux->ant->prox = aux;
    }
    return aux;
}

void imprimeLista(Lista* l){
    if(!vazia(l)){
        Lista* aux = l;
        while(aux != l->prox){
            printf("%d ", l->info);
            l = l->prox;
        }
        printf("%d\n", l->info);
    }
    else    
        printf("\n");
}

Lista* remover(Lista* l, int info) {
    if (l == NULL)
        return NULL;
    
    Lista* cab = l;

    while (l->prox != cab){
        if(l->info == info){
            l->ant->prox = l->prox;
            l->prox->ant = l->ant;

            if(cab == l) 
                cab =  l->prox;

            free(l);
            return cab;
        }
        l = l->prox;
    }
    if(l->info == info){
        l->ant->prox = l->prox;
        l->prox->ant = l->ant;

        cab = (l == l->prox) ? NULL : l->prox;

        free(l);
        return cab;
    }    
    return cab;
}

Lista* remover_rec(Lista* l, int info) {
    if (l == NULL) {
        // Se a lista estiver vazia, não há nada para remover
        return NULL;
    }

    // Caso base: Se o elemento for encontrado na cabeça, remova-o
    if (l->info == info) {
        Lista* proximo = l->prox;
        
        if (l->prox == l) {
            // Se houver apenas um nó na lista, libere-o e retorne NULL
            free(l);
            return NULL;
        } else {
            // Caso contrário, ajuste os ponteiros para remover a cabeça
            l->ant->prox = l->prox;
            l->prox->ant = l->ant;
            free(l);
            return proximo; // Retorna o próximo nó como a nova cabeça da lista
        }
    }

    // Caso recursivo: Chama a função para o próximo nó
    l->prox = remover(l->prox, info);

    return l; // Retorna o nó atual (pode ter sido alterado ou não)
}


int main (){
    Lista* l = NULL;

    l = insere(l, 1);
    l = insere(l, 5);
    l = insere(l, 9);
    l = insere(l, 7);

    imprimeLista(l);

    l = remover_rec(l, 6);
    imprimeLista(l);


}