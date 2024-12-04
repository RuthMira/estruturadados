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
    no *nova;
    nova = malloc(sizeof(no)); 
    nova->url = malloc(strlen(url) + 1);  
    strcpy(nova->url, url);  
    nova->prox = pi->prox;  
    pi->prox = nova; 
}

char* desempilha(void) {
    if (pi->prox == NULL) {  
        return NULL;
    }

    no *p = pi->prox; 
    char* url = p->url;  
    pi->prox = p->prox; 
    free(p); 
    return url; 
}


void liberaPilha(void) {
    no *p = pi->prox;
    while (p != NULL) {
        no *temp = p;
        p = p->prox;
        free(temp->url);  
        free(temp); 
    }
    free(pi);
}

int main() {
    criapilha();

    empilha("www.google.com");
    empilha("www.youtube.com");
    empilha("www.github.com");

    char* url = desempilha();
    if (url != NULL) {
        printf("%s\n", url);
    }

    
    char* url1 = desempilha();
    if (url1 != NULL) {
        printf("%s\n", url1);
    }
    
    char* url2 = desempilha();
    if (url2 != NULL) {
        printf("%s\n", url2);
    }


    liberaPilha();

    return 0;
}

liberar pilha esta destruindo a pilha , so limpar a temp
chamada na main usando uma nova variavel em vez de retornar a tem 
