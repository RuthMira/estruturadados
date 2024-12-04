#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int id;
    char nome[50];
    struct No* proximo;
} No;

void enfileirar(No** frente, No** final, int id, const char* nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->id = id;
    snprintf(novoNo->nome, sizeof(novoNo->nome), "%s", nome);
    novoNo->proximo = NULL;

    if (*final == NULL) {
        *frente = novoNo;
        *final = novoNo;
    } else {
        (*final)->proximo = novoNo;
        *final = novoNo;
    }
}

No* desenfileirar(No** frente, No** final) {
    if (*frente == NULL) {
        return NULL; 
    }

    No* temp = *frente;
    *frente = (*frente)->proximo;

    if (*frente == NULL) {
        *final = NULL;
    }
    
    return temp; 
}

void exibirFila(No* frente) {
    if (frente == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    No* atual = frente;
    while (atual != NULL) {
        printf("ID=%d, Nome=%s\n", atual->id, atual->nome);
        atual = atual->proximo;
    }
}

void liberarFila(No* frente) {
    while (frente != NULL) {
        No* temp = frente;
        frente = frente->proximo;
        free(temp);
    }
}

int main() {
    No* frente = NULL;
    No* final = NULL;

    enfileirar(&frente, &final, 1, "João");
    enfileirar(&frente, &final, 2, "Maria");
    enfileirar(&frente, &final, 3, "Carlos");

    printf("Estado inicial da fila:\n");
    exibirFila(frente);
    
    printf("\nDesenfileirando um elemento:\n");
    No* removido = desenfileirar(&frente, &final);
    if (removido != NULL) {
        printf("Desenfileirado: ID=%d, Nome=%s\n", removido->id, removido->nome);
        free(removido);
    }
    
    printf("Estado inicial da fila:\n");
    exibirFila(frente);

    liberarFila(frente); 
    
    printf("Estado inicial da fila:\n");
    exibirFila(frente);
    
    return 0;
}


liberar fila precisa so limpar a memoria do temp
mani o desinfilerar mosttar o conteudo do temp , que aind aano limpei
