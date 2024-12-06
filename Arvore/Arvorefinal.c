#include <stdio.h>
#include <stdlib.h>

// Estrutura da árvore
typedef struct cel
{
    int conteudo;
    struct cel *esquerda, *direita;
} Cel;

// Função para inserir um nó na árvore
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

// Função para imprimir a árvore em ordem (esq -> raiz -> dir)
void imprimir(Cel *raiz)
{
    if (raiz != NULL)
    {
        imprimir(raiz->esquerda);
        printf("%d\n", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

// Função para buscar a mãe de um nó
Cel *BuscarMae(Cel *raiz, int valor)
{
    if (raiz == NULL)
    {
        printf("Raiz nula!\n");
        return NULL;
    }

    if (valor == raiz->conteudo)
    {
        return NULL;
    }
    else if (valor < raiz->conteudo)
    {
        if (raiz->esquerda != NULL && raiz->esquerda->conteudo == valor)
        {
            return raiz;
        }
        return BuscarMae(raiz->esquerda, valor);
    }
    else if (valor > raiz->conteudo)
    {
        if (raiz->direita != NULL && raiz->direita->conteudo == valor)
        {
            return raiz;
        }
        return BuscarMae(raiz->direita, valor);
    }
    return NULL; // Retorna NULL caso não encontre a mãe
}

// Função para remover um nó e reorganizar a árvore (casos de remoção)
Cel *RemoverNo(Cel *raiz, int valor)
{
    if (raiz == NULL)
    {
        printf("Árvore vazia!\n");
        return NULL;
    }

    // Caso o valor a ser removido seja a raiz
    if (raiz->conteudo == valor)
    {
        // Caso 1: Não há subárvore à esquerda, então o nó da direita substitui a raiz
        if (raiz->esquerda == NULL)
        {
            Cel *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        // Caso 2: Não há subárvore à direita, então o nó da esquerda substitui a raiz
        else if (raiz->direita == NULL)
        {
            Cel *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 3: O nó tem ambos os filhos, precisamos encontrar o maior da subárvore esquerda
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
    else if (valor < raiz->conteudo)
    {
        raiz->esquerda = RemoverNo(raiz->esquerda, valor);
    }
    else if (valor > raiz->conteudo)
    {
        raiz->direita = RemoverNo(raiz->direita, valor);
    }

    return raiz;
}

// Função para buscar o maior nó à esquerda
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

int main()
{
    Cel *raiz = NULL;

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

    // Buscar a mãe de um nó
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

    // Remover o valor da árvore e reorganizar
    printf("\nRemovendo o valor %d da árvore...\n", valorBusca);
    raiz = RemoverNo(raiz, valorBusca);
    printf("Árvore após remoção:\n");
    imprimir(raiz);

    return 0;
}


// Cel *Remover(Cel *raiz, Cel *no)
// {
//     if (raiz == NULL)
//         return raiz;

//     if (no->conteudo < raiz->conteudo)
//         raiz->esquerda = Remover(raiz->esquerda, no);
//     else if (no->conteudo > raiz->conteudo)
//         raiz->direita = Remover(raiz->direita, no);
//     else
//     {
//         if (raiz->esquerda == NULL)
//         {
//             Cel *temp = raiz->direita;
//             free(raiz);
//             return temp;
//         }
//         else if (raiz->direita == NULL)
//         {
//             Cel *temp = raiz->esquerda;
//             free(raiz);
//             return temp;
//         }

//         Cel *temp = BuscarMaiorEsquerda(raiz);
//         raiz->conteudo = temp->conteudo;
//         raiz->esquerda = Remover(raiz->esquerda, temp);
//     }
//     return raiz;
// }
