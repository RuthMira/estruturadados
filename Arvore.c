#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no* esq;
    struct no* dir;
} no;

no* criar_no(int valor) {
    no* novo = (no*)malloc(sizeof(no));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

no* inserir(no* atual, int valor) {
    if (atual == NULL) {
        return criar_no(valor);
    }
    if (valor < atual->valor) {
        atual->esq = inserir(atual->esq, valor);
    } else {
        atual->dir = inserir(atual->dir, valor);
    }
    return atual;
}

no* buscar(no* raiz) {
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

no* remover(no* raiz, int valor) {
    if (raiz == NULL) {
        return NULL; 
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Caso 1: Nó sem filhos (folha)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho
        else if (raiz->esq == NULL) {
            no* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            no* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            no* maior_esq = buscar(raiz->esq);
            raiz->valor = maior_esq->valor; 
            raiz->esq = remover(raiz->esq, maior_esq->valor); 
        }
    }
    return raiz;
}

void imprimir(no* atual) {
    if (atual != NULL) {
        imprimir(atual->esq);
        printf("%d ", atual->valor);
        imprimir(atual->dir);
    }
}

int main() {
    no* raiz = NULL; 

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 20);


    imprimir(raiz);
    printf("\n");

    raiz = remover(raiz, 10); 

    imprimir(raiz);
    printf("\n");


    return 0;
}
