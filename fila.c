#include <stdio.h>
#include <stdlib.h>

// estrutura de no para lista encadeada
struct no {
    int info;
    struct no *prox;
};
// estrutura para fila
struct fila {
    int n; // numero de elementos
    struct no* prim;
    struct no* ultimo;
};

int vazia(struct fila* f){
    return (f->n == 0);
}

struct fila* cria_fila_vazia(){
    struct fila* aux = (struct fila*) malloc (sizeof(struct fila));
    aux->prim = NULL;
    aux->ultimo = NULL;
    aux->n = 0;

    return aux;
}

void enqueue(struct fila* f, int info){
    struct no* aux = (struct no*) malloc(sizeof(struct no));
    aux->info = info;
    aux->prox = NULL;

    if(vazia(f)) 
        f->prim = aux;
    else 
        f->ultimo->prox = aux;

    f->ultimo = aux;
    f->n++;
}

void insere(struct fila* f, int info){
    if(vazia(f)){
        struct no* aux = (struct no*) malloc (sizeof(struct no));
        aux->info = info;
        f->prim = aux;
        f->ultimo = aux;
    }
    struct no* aux = (struct no*) malloc (sizeof(struct no));
    aux->info = info;
    f->ultimo->prox = aux;
    f->ultimo = aux;
}

void dequeue(struct fila* f){
    if(!vazia(f)){
        struct no* aux = f->prim;
        if(f->prim == f->ultimo) 
            f->prim = NULL;
        else 
            f->prim = f->prim->prox;
            
        free(aux);
        f->n--;
    }
}

void printFila(struct fila *f){
    if(!vazia(f)){
        struct no* aux = f->prim;
        while(aux != NULL){
            printf("%d ", aux->info);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void inverter(struct fila* f) {
    if (!vazia(f)) {
        struct fila* temp = cria_fila_vazia();
        struct no* stack = NULL;

        // Dequeue todos os elementos da fila e empilhe-os
        while (!vazia(f)) {
            struct no* aux = (struct no*) malloc(sizeof(struct no));
            aux->info = f->prim->info;
            aux->prox = stack;
            stack = aux;
            dequeue(f);
        }

        // Desempilhe todos os elementos e enfileire novamente
        while (stack != NULL) {
            enqueue(f, stack->info);
            struct no* temp = stack;
            stack = stack->prox;
            free(temp);
        }

        free(temp);
        printFila(f);
    }
}

void inverterRec(struct fila* f, struct fila* aux) {
    if (!vazia(f)) {
        // Desenfileira da fila original e armazena o valor temporariamente
        int valor = f->prim->info;
        dequeue(f);
        // Chama recursivamente para o restante da fila
        inverterRec(f, aux);
        // Enfileira o valor armazenado na fila auxiliar (inverte a ordem)
        enqueue(aux, valor);
    }
}

// Função principal para inverter a fila
void inverte(struct fila* f) {
    struct fila* aux = cria_fila_vazia();
    inverterRec(f, aux);
    // Copia os elementos da fila auxiliar de volta para a fila original
    while (!vazia(aux)) {
        int valor = aux->prim->info;
        dequeue(aux);
        enqueue(f, valor);
    }
    free(aux);
}

int main (){
    struct fila* fila = cria_fila_vazia();

    enqueue(fila, 2);
    enqueue(fila, 3);
    enqueue(fila, 4);

    printFila(fila);

    //dequeue(fila);
    //printFila(fila);

    //inverter(fila);

    inverte(fila);
    printFila(fila);

}
