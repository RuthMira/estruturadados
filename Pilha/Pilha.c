#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no { 
    char* url;           
    struct no* prox; 
} no;

no *pi;

void criapilha(void) {
    pi = malloc(sizeof(no));  
    pi->prox = NULL; 
}

void empilha(const char* url) {
    no *nova = malloc(sizeof(no)); 
    nova->url = malloc(strlen(url) + 1);  
    strcpy(nova->url, url);  
    nova->prox = pi->prox;  
    pi->prox = nova; 
}

no* desempilha(void) {
    if (pi->prox == NULL) {  
        return NULL;
    }

    no *p = pi->prox; 
    pi->prox = p->prox; 
    return p; 
}

void liberaNo(no* p) {
    if (p != NULL) {
        free(p->url);  
        free(p);
    }
}

void exibirPilha(no* pi) {
    no* atual = pi->prox; 
    if (atual == NULL) {
        return;
    }
    
    printf("Elementos na pilha:\n");
    while (atual != NULL) {
        printf("URL: %s\n", atual->url);
        atual = atual->prox;
    }
}


int main() {
    criapilha();

    empilha("www.google.com");
    empilha("www.youtube.com");
    empilha("www.github.com");
    
    exibirPilha(pi);

    no* p = desempilha();
    printf("%s\n", p->url);
    
    liberaNo(p);
    
    exibirPilha(pi);
    
    
    return 0;
}
