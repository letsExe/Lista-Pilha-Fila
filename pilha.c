#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no* prox;
};

typedef struct{
    struct no* topo;
}Pilha;

int vazia(Pilha *p){
    return(p->topo == NULL);
}

Pilha* criar_pilha_vazia(){
    Pilha* p = malloc (sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void push(Pilha *p, int info){
    struct no* aux = (struct no*) malloc (sizeof(struct no));
    aux->info = info;

    if(vazia(p)){
        p->topo = aux;
        aux->prox = NULL;
    }
    else{
        aux->prox = p->topo;
        p->topo = aux;
    }
}

int pop(Pilha* p){
    if(!vazia(p)){
        struct no* aux = p->topo;
        int x = p->topo->info;

        if(aux->prox == NULL){
            p->topo = NULL;
            free(aux);
        }
        else{
            p->topo = aux->prox;
            free(aux);
        }
        return x;
    }
}

void imprimirPilha(Pilha* p){
    struct no* aux = p->topo;
    while(aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int posfix(char *str){
    int num = 0;
    Pilha *p = inicializaPilha(); 
    int x, y, resultado;
    while(*str){

        if (digito(*str)){
            num *=10 + (*str - '0');
        }
        else if (*str == ' '){ // guarda na pilha
            push(p, num);     /// n lembro como  ta o push da prova kkkk
            num = 0;
        }
        else {   /// tira da pilha e faz conta
            x = pop(p);
            y= pop(p);

            if (*str == '+'){
                resultado = x + y;
            }
            else if(*str == '-'){
                resultado = y - x;
            }
            else if(*str == '*'){
                resultado = x * y;
            }
            else if(*str == '/'){
                resultado = y / x;
            }

            push(p, resultado); /// n lembro como  ta o push da prova kkkk

        }

        str++;
    }

    return pop(p);
}

int main(){
    Pilha *p = criar_pilha_vazia();

    push(p, 5);
    push(p, 8);
    push(p, 3);

    imprimirPilha(p);

    pop(p);
    imprimirPilha(p);

    return 0;
}