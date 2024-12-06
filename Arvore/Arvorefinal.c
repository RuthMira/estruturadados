#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó em uma árvore binária
typedef struct cel
{
    int conteudo;
    struct cel *esquerda;
    struct cel *direita;
} Cel;

// Função para inserir um nó na árvore binária
void insere(Cel **raiz, int valor)
{
    if (*raiz == NULL)
    {
        Cel *novo = malloc(sizeof(Cel));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        *raiz = novo;
    }
    else
    {
        if (valor < (*raiz)->conteudo)
        {
            insere(&((*raiz)->esquerda), valor);
        }
        else if (valor > (*raiz)->conteudo)
        {
            insere(&((*raiz)->direita), valor);
        }
    }
}

// Função para imprimir a árvore em ordem (esquerda -> raiz -> direita)
void imprimir(Cel *raiz)
{
    if (raiz != NULL)
    {
        imprimir(raiz->esquerda);
        printf("%d\n", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

// Função para buscar o "pai" de um nó específico
Cel *BuscarMae(Cel *raiz, int valor)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    // O nó raiz não possui pai
    if (valor == raiz->conteudo)
    {
        return NULL;
    }

    // Busca na subárvore esquerda
    if (valor < raiz->conteudo)
    {
        if (raiz->esquerda != NULL && raiz->esquerda->conteudo == valor)
        {
            return raiz;
        }
        return BuscarMae(raiz->esquerda, valor);
    }

    // Busca na subárvore direita
    if (valor > raiz->conteudo)
    {
        if (raiz->direita != NULL && raiz->direita->conteudo == valor)
        {
            return raiz;
        }
        return BuscarMae(raiz->direita, valor);
    }

    return NULL;
}

// Função auxiliar para buscar o maior nó na subárvore esquerda
Cel *BuscarMaiorEsquerda(Cel *raiz)
{
    if (raiz == NULL || raiz->esquerda == NULL)
    {
        return NULL;
    }

    Cel *atual = raiz->esquerda;
    Cel *mae = raiz;

    while (atual->direita != NULL)
    {
        mae = atual;
        atual = atual->direita;
    }

    return mae;
}

// Função para remover um nó da árvore
Cel *RemoverNo(Cel *raiz, int valor)
{
    if (raiz == NULL)
    {
        printf("Árvore vazia ou valor não encontrado!\n");
        return NULL;
    }

    if (valor < raiz->conteudo)
    {
        raiz->esquerda = RemoverNo(raiz->esquerda, valor);
    }
    else if (valor > raiz->conteudo)
    {
        raiz->direita = RemoverNo(raiz->direita, valor);
    }
    else
    {
        // Nó encontrado
        if (raiz->esquerda == NULL && raiz->direita == NULL)
        {
            free(raiz);
            return NULL;
        }
        else if (raiz->esquerda == NULL)
        {
            Cel *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            Cel *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        else
        {
            Cel *maiorEsqMae = BuscarMaiorEsquerda(raiz);
            if (maiorEsqMae != NULL)
            {
                Cel *maiorEsq = maiorEsqMae->direita;
                raiz->conteudo = maiorEsq->conteudo;
                raiz->esquerda = RemoverNo(raiz->esquerda, maiorEsq->conteudo);
            }
        }
    }

    return raiz;
}

// Função principal para testar a árvore
int main()
{
    Cel *raiz = NULL;

    // Inserindo elementos na árvore
    insere(&raiz, 10);
    insere(&raiz, 5);
    insere(&raiz, 6);
    insere(&raiz, 15);
    insere(&raiz, 3);
    insere(&raiz, 7);
    insere(&raiz, 12);
    insere(&raiz, 17);
    insere(&raiz, 2);

    printf("Árvore original:\n");
    imprimir(raiz);

    // Buscar mãe de um nó
    int valorBusca = 10;
    Cel *mae = BuscarMae(raiz, valorBusca);
    if (mae != NULL)
    {
        printf("\nO valor %d tem como mãe o nó com conteúdo %d.\n", valorBusca, mae->conteudo);
    }
    else
    {
        printf("\nO valor %d é a raiz da árvore ou não está presente.\n", valorBusca);
    }

    // Remover um nó
    printf("\nRemovendo o valor %d da árvore...\n", valorBusca);
    raiz = RemoverNo(raiz, valorBusca);
    printf("Árvore após a remoção:\n");
    imprimir(raiz);

    return 0;
}
