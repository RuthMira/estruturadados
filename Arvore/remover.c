#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No* esquerdo;
    struct No* direito;
};

struct No* criarNovoNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = valor;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

struct No* inserirNo(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNovoNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerdo = inserirNo(raiz->esquerdo, valor);
    } else if (valor > raiz->valor) {
        raiz->direito = inserirNo(raiz->direito, valor);
    }

    return raiz;
}

struct No* encontrarMinimo(struct No* raiz) {
    while (raiz->esquerdo != NULL) {
        raiz = raiz->esquerdo;
    }
    return raiz;
}

struct No* removerNo(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return raiz; 
    }

    if (valor < raiz->valor) {
        raiz->esquerdo = removerNo(raiz->esquerdo, valor);
    } else if (valor > raiz->valor) {
        raiz->direito = removerNo(raiz->direito, valor);
    } else {
        if (raiz->esquerdo == NULL && raiz->direito == NULL) {
            free(raiz);
            return NULL;
        }
        if (raiz->esquerdo == NULL) {
            struct No* temp = raiz->direito;
            free(raiz);
            return temp;
        } else if (raiz->direito == NULL) {
            struct No* temp = raiz->esquerdo;
            free(raiz);
            return temp;
        }
        struct No* temp = encontrarMinimo(raiz->direito);
        raiz->valor = temp->valor; 
        raiz->direito = removerNo(raiz->direito, temp->valor); 
    }

    return raiz;
}


void percursoEmOrdem(struct No* raiz) {
    if (raiz != NULL) {
        percursoEmOrdem(raiz->esquerdo);
        printf("%d ", raiz->valor);
        percursoEmOrdem(raiz->direito);
    }
}

int main() {
    struct No* raiz = NULL;

    raiz = inserirNo(raiz, 10);
    raiz = inserirNo(raiz, 5);
    raiz = inserirNo(raiz, 20);
    raiz = inserirNo(raiz, 7);
    raiz = inserirNo(raiz, 15);
    raiz = inserirNo(raiz, 25);

    raiz = removerNo(raiz, 20);
    percursoEmOrdem(raiz);
    printf("\n");

    return 0;
}
