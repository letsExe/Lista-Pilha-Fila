#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no* prox;
}Lista;

int vazia(Lista* l){
    return (l == NULL);
}

Lista* insere (Lista* l, int info){
    Lista* aux = malloc (sizeof(Lista));
    aux->info = info;
    aux->prox = l;
    return aux;
}

Lista* insereFila (Lista *l, int info){
    if(vazia(l)){
        Lista* aux = malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = NULL;
        return aux;
    }
 
    l->prox = insereFila(l->prox, info);
    return l;
}

Lista* insereOrdenado(Lista* l, int info) {
    if (vazia(l) || info < l->info) {
        Lista* aux = (Lista*) malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = l;
        return aux;
    }

    l->prox = insereOrdenado(l->prox, info);
    return l;
}

Lista* removeLista(Lista* l, int info){
    if(!vazia(l)){
        if(l->info == info){
            Lista* aux = l->prox;
            free(l);
            return aux;
        }
        l->prox = removeLista(l->prox, info);
    }
    return l;
}

Lista* removeOcorrencias(Lista* l, int info){ //remove todas as ocorrencias de info
    if(!vazia(l)){
        if(l->info == info){
            Lista* aux = l->prox;
            free(l);

            return removeOcorrencias(aux, info);
        }  

        l->prox = removeOcorrencias(l->prox, info);
        return l;
    }
    return NULL;   
}

int buscaLista(Lista* l, int info){
    if(!vazia(l)){
        if(info == l->info){
            return l->info;
        }  
        return buscaLista(l->prox, info);
    }
    return -1;
}

int busca_Lista(Lista* l, int info){
    if(!vazia(l)){
        if(info == l->info){
            return 1;
        }  
        return busca_Lista(l->prox, info);
    }
    return 0;
}

int somaIntervalo(Lista* l, int a, int b){
    if(!vazia(l)){
        if(l->info >= a && l->info <= b){
            return l->info + somaIntervalo (l->prox, a, b);
        }
 
        return somaIntervalo(l->prox, a , b);
    }  
    return 0;
}

void printLista (Lista* l){
    if(!vazia(l)){
        printf("%d ", l->info);
        printLista(l->prox);
    } 
    else    
        printf("\n");   
}

Lista* obter_sublista2(Lista* l, int a, int b){ 
    if(vazia(l)) return NULL;  

    Lista* aux = NULL;
    if(b == 0){
        return insereFila(aux, l->info);
    }
    if(a == 0){
        aux = insereFila(aux, l->info);
        aux->prox = obter_sublista2(l->prox, a, --b);
        return aux;
    }
    return obter_sublista2(l->prox, --a, --b);
}

void imprimeIntervalo(Lista *l, int a, int b){
    if(!vazia(l)){
        if(l->info >= a && l->info <= b){
            printf("%d ", l->info);
            imprimeIntervalo(l->prox, a, b);
        }
        else {
            imprimeIntervalo(l->prox, a, b);
        }
    }
    return;
}

Lista* concatena(Lista* l1, Lista* l2){
    Lista* l3 = NULL;
    if(!vazia(l1)){
        l3 = insereFila (l3, l1->info);
        l3->prox = concatena (l1->prox, l2);
    }
    else{
        if(!vazia(l2)){
            l3 = insereFila(l3, l2->info);
            l3->prox = concatena(l1, l2->prox);
        }
    }
    return l3;
}

Lista* intercala(Lista* l1, Lista* l2){//casos: se a l1 for menor ent continua inserindo// se a l1 eh maior
    Lista* l3 = NULL;

    if(!vazia(l1)){
        l3 = insereFila(l3, l1->info);
        if(!vazia(l2)){
            l3 = insereFila(l3, l2->info); 
            l3->prox->prox = intercala(l1->prox, l2->prox);
        }
        else
            l3->prox = intercala(l1->prox, l2);
    }
    else {
        if(!vazia(l2)){
            l3 = insereFila(l3, l2->info);
            l3->prox = intercala(l1, l2->prox);
        }
    }
    return l3;
}

void liberaLista(Lista* l){
    Lista* aux;
    while(l != NULL){
        aux = l;
        l = l->prox;
        free(aux);
    }
}

//////////exercicos de prova
Lista* inserir_apos_i(Lista* l, int info_ref, int info){
    if(vazia(l)) 
        return NULL;

    Lista* temp = l;
    while(temp->prox != NULL){
        if(temp->info == info_ref){
            Lista* aux = (Lista*) malloc (sizeof(Lista));
            aux->info = info;
            aux->prox = temp->prox;
            temp->prox = aux;
            return l;
        }
        temp = temp->prox;            
    }
    Lista* aux = (Lista*) malloc (sizeof(Lista));
    aux->info = info;
    aux->prox = NULL;
    temp->prox = aux;

    return l;
}

Lista* insere_apoos_rec(Lista*l, int vr, int info){
    if(l != NULL && l->info == vr){
        Lista* aux = (Lista*) malloc (sizeof(Lista));
        aux->info = info;
        aux->prox = l->prox;
        l->prox = aux;
    }

    else if(l == NULL){
        Lista* aux = (Lista*) malloc (sizeof(Lista));
        aux->info = info;
        aux->prox = NULL;
        l = aux;
    }
    else
        l->prox = insere_apoos_rec(l->prox, vr, info);

    return l;
}

Lista* insere_apos_pos(Lista* l, int pos, int info){
    if(l != NULL && pos == 0){
        Lista* aux = (Lista*) malloc (sizeof(Lista));
        aux->info = info;
        aux->prox = l;
        l = aux;
        return l;
    }
    l->prox = insere_apos_pos(l->prox, pos-1, info);
    return l;
}

int contar_ocorrencias(Lista* l, int x){
    if(!vazia(l)){
        if(l->info == x){
            return 1 + contar_ocorrencias(l->prox, x);
        }
        return contar_ocorrencias(l->prox, x);
    }
    return 0;
}

Lista * menores_r(Lista* l, int val_ref){
    if(vazia(l))
        return NULL;
    if(l->info < val_ref) 
        return insere(menores_r(l->prox, val_ref), l->info);
    else 
        return menores_r(l->prox,val_ref);
}

int somar_multiplos(Lista* l, int n){
    if(vazia(l))
        return 0;

    if(l->info%n == 0){
        return somar_multiplos(l->prox, n) + l->info;
    }
    return somar_multiplos(l->prox, n);
}

int soma(Lista* l, int s){
    if(vazia(l)){
        return s;
    }
    s += l->info;

    return soma(l->prox, s);
}

int soma_s(Lista* l){
    if(!vazia(l)){
        return l->info + soma_s(l->prox);
    }
    return 0;
}

void print_intervalo_pos(Lista *l, int pos1, int pos2){
    if(vazia(l)){
        return;
    }

    if(pos2 == 0){
        printf("%d\n", l->info);
        return;
    }
    if(pos1 <= 0){
        printf("%d ", l->info);
        //print_intervalo_pos(l->prox, pos1, --pos2);
    }
    //else
        print_intervalo_pos(l->prox, --pos1, --pos2);
}

Lista* sub_lista(Lista* l1, Lista* l2){
    if(vazia(l2))
        return l1;

    if(vazia(l1))
        return NULL;

    if(busca_Lista(l2, l1->info)){
        Lista* aux = l1->prox;
        free(l1);
        aux = sub_lista(aux, l2);
        return aux;        
    }

    l1->prox = sub_lista(l1->prox, l2);
    return l1;
}

Lista* inverte_int(Lista* l){
    Lista* aux = NULL;
    while(l != NULL){
        aux = insere(aux ,l->info);
        l = l->prox;
    }
    return aux;
}

Lista* inverte (Lista* l){
    if(vazia(l))
        return NULL;
    
    return insereFila(inverte(l->prox), l->info);
}

int main (){
    Lista* l = NULL;
    Lista* l2 = NULL;
    Lista* l3 = NULL;

    l = insereFila(l, 8);
    l = insereFila(l, 7);
    l = insereFila(l, 1);
    l = insereFila(l, 6);
    l = insereFila(l, 2);
    l = insereFila(l, 4);
    l = insereFila(l, 3);

    /*l2 = insereFila(l2, 6);
    l2 = insereFila(l2, 8);
    l2 = insereFila(l2, 1);
    l2 = insereFila(l2, 3);
    l2 = insereFila(l2, 15);
    l2 = insereFila(l2, 22);*/
    
    //int s = 0;
    printLista(l);
    //printf("%d", soma_s(l2));
    //printLista(l2);

    //l = removeOcorrencias(l, 2);
    //l2 = obter_sublista(l, 0, 3);

    //l3 = intercala(l, l2);
    //printLista(l3);

    //printf("%d\n", somaIntervalo(l, 2, 5));

    //l = inserir_apos_i(l, 8, 156);
    //print_intervalo_pos(l, 1, 3);
    //printf("o numero de ocorrencias eh %d", contar_ocorrencias(l, 5));

    //l3 = menores_r(l, 7);
    //printf("a soma eh igual: %d", somar_multiplos(l, 1));

    //l = sub_lista(l, l2);
    l = inverte(l);
    printLista(l);


    liberaLista(l);
    //liberaLista(l2);
    //liberaLista(l3);


    return 0;
}