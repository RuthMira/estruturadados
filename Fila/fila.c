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
        return NULL; // Fila vazia
    }

    No* temp = *frente; 
    *frente = (*frente)->proximo; 

    if (*frente == NULL) { 
        *final = NULL;
    }

    return temp; 
}

void liberaNo(No* temp) {
    if (temp != NULL) {
        free(temp);
    }
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

int main() {
    No* frente = NULL;
    No* final = NULL;

    enfileirar(&frente, &final, 1, "João");
    enfileirar(&frente, &final, 2, "Maria");
    enfileirar(&frente, &final, 3, "Carlos");

    exibirFila(frente);
    
    No* temp = desenfileirar(&frente, &final); 
    printf("Desenfileirado: ID=%d, Nome=%s\n", temp->id, temp->nome);

    liberaNo(temp);
    
    exibirFila(frente);

    return 0;
}
