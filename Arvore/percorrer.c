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

void percursoPreOrdem(struct No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        percursoPreOrdem(raiz->esquerdo);
        percursoPreOrdem(raiz->direito);
    }
}

void percursoEmOrdem(struct No* raiz) {
    if (raiz != NULL) {
        percursoEmOrdem(raiz->esquerdo);
        printf("%d ", raiz->valor);
        percursoEmOrdem(raiz->direito);
    }
}

void percursoPosOrdem(struct No* raiz) {
    if (raiz != NULL) {
        percursoPosOrdem(raiz->esquerdo);
        percursoPosOrdem(raiz->direito);
        printf("%d ", raiz->valor);
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

    printf("Percurso em pré-ordem: ");
    percursoPreOrdem(raiz);
    printf("\n");

    printf("Percurso em ordem: ");
    percursoEmOrdem(raiz);
    printf("\n");

    printf("Percurso em pós-ordem: ");
    percursoPosOrdem(raiz);
    printf("\n");

    // printf("Removendo o nó 20\n");
    // raiz = removerNo(raiz, 20);
    // printf("Percurso em ordem após remover 20: ");
    // percursoEmOrdem(raiz);
    // printf("\n");

    // printf("Removendo o nó 10\n");
    // raiz = removerNo(raiz, 10);
    // printf("Percurso em ordem após remover 10: ");
    // percursoEmOrdem(raiz);
    // printf("\n");

    return 0;
}
