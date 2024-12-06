#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// estrutura do meu nó m uma arvore
typedef struct cel
{
    int conteudo;
    struct cel *esquerda, *direita;
} Cel;



// inserindo um no na arvore
void insere(Cel **raiz, int valor)
{   
    if (*raiz == NULL)
    {
        Cel *novo;
        novo = malloc(sizeof(Cel));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        *raiz = novo;
    }
    else
    {
        // se a arvore já possui nos compara o valor do novo com a raiz valor<raiz se insere novo->esquerda
        if (valor < (*raiz)->conteudo)
        {
            insere(&((*raiz)->esquerda), valor);
        }
        // valor>raiz se insere novo->direita
        else if (valor > (*raiz)->conteudo)
        {
            insere(&((*raiz)->direita), valor);
        }
    }
}



// imprimir a arvore em em-ordem esq->raiz->dir
void imprimir(Cel *raiz)
{
    if (raiz != NULL)
    {
        imprimir(raiz->esquerda);
        printf("%d\n", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

//Busca na arvore por um no em especifico retornando o pai desta
Cel *BuscarMae(Cel *raiz, int valor)
{

    if (raiz == NULL)
    {
        printf("Raiz nula! :(");
        return NULL;
    }

    if (valor == raiz->conteudo)
    {
        return NULL;
    }
    else if (valor < raiz->conteudo)
    {
        if (raiz->esquerda->conteudo != valor)
        {
            BuscarMae(raiz->esquerda, valor);
        }
        else if (raiz->esquerda->conteudo == valor)
        {
            return raiz;
        }
    }
    else if (valor > raiz->conteudo)
    {
        if (raiz->direita->conteudo != valor)
        {
            BuscarMae(raiz->direita, valor);
        }
        else if (raiz->direita->conteudo == valor)
        {
            return raiz;
        }
    }
}



// remover um no e se necessario reorganizar a arvore (tres casos)
Cel *RemoverNo(Cel *raiz, int valor)
{
    if (raiz == NULL)
    {
        printf("Árvore vazia!\n");
        return NULL;
    }

    // Se o valor a ser removido é a raiz
    if (raiz->conteudo == valor)
    {
        // Encontra o nó pai do maior elemento na subárvore esquerda
        Cel *maiorEsqMae = BuscarMaiorEsquerda(raiz);

        if (maiorEsqMae != NULL)
        {
            // O maior elemento está na subárvore esquerda
            Cel *maiorEsq = maiorEsqMae->direita;

            // Troca os conteúdos
            raiz->conteudo = maiorEsq->conteudo;
            // Remove o nó encontrado da subárvore esquerda
            raiz->esquerda = RemoverNo(raiz->esquerda, maiorEsq->conteudo);
        }
        else
        {
            // Se não há elementos na subárvore esquerda, o nó da direita se torna a nova raiz
            Cel *temp = raiz->direita;
            free(raiz);
            return temp;
        }
    }
    else
    {
        // Continua com a lógica de remoção para outros nós da árvore
        Cel *mae = BuscarMae(raiz, valor);

        if (mae == NULL)
        {
            printf("Valor não encontrado na árvore!\n");
            return raiz;
        }

        // Identificando se o nó a ser removido está à esquerda ou à direita da mãe
        Cel *noRemover = (mae->esquerda && mae->esquerda->conteudo == valor) ? mae->esquerda : mae->direita;

        // Caso 1: Nó é uma folha
        if (noRemover->esquerda == NULL && noRemover->direita == NULL)
        {
            if (mae->esquerda == noRemover)
            {
                mae->esquerda = NULL;
            }
            else
            {
                mae->direita = NULL;
            }
            free(noRemover);
        }
        // Caso 2: Nó tem um filho
        else if (noRemover->esquerda == NULL || noRemover->direita == NULL)
        {
            Cel *filho = (noRemover->esquerda != NULL) ? noRemover->esquerda : noRemover->direita;
            if (mae->esquerda == noRemover)
            {
                mae->esquerda = filho;
            }
            else
            {
                mae->direita = filho;
            }
            free(noRemover);
        }
        // Caso 3: Nó tem dois filhos
        else
        {
            Cel *sucessor = noRemover->direita;
            while (sucessor->esquerda != NULL)
            {
                sucessor = sucessor->esquerda;
            }
            int temp = sucessor->conteudo;
            raiz->direita = RemoverNo(raiz->direita, sucessor->conteudo);
            noRemover->conteudo = temp;
        }
    }

    return raiz;
}


Cel *BuscarMaiorEsquerda(Cel *raiz)
{
    if (raiz == NULL || raiz->esquerda == NULL)
    {
        return NULL; // Se a raiz ou a subárvore esquerda forem nulas, não há maior elemento
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
    
    
    //Mostra o pai do no com o valor da busca. Agora caso ele nao tenhaum pai ou nao esteja na arvore entra no else e retona o valor da busca
    int valorBusca = 10;
    Cel *mae = BuscarMae(raiz, valorBusca);
    if (mae != NULL)
    {
        printf("\n\nO valor %d tem como mãe o nó com conteúdo %d.\n", valorBusca, mae->conteudo);
    }
    else
    {
        printf("\n\nO valor %d é a raiz da árvore ou não está presente na árvore.\n", valorBusca);
    }



    // remove o valor da busca e reorganiza a arvore
    printf("\nRemovendo o valor %d da árvore...\n", valorBusca);
    raiz = RemoverNo(raiz, valorBusca);
    printf("Árvore após a remoção:\n");
    imprimir(raiz);

    return 0;
}


Cel *Remover(Cel *raiz, Cel *no) {
    if (raiz == NULL)
        return raiz;

    if (no->conteudo < raiz->conteudo)
        raiz->esquerda = Remover(raiz->esquerda, no);
    else if (no->conteudo > raiz->conteudo)
        raiz->direita = Remover(raiz->direita, no);
    else {
        if (raiz->esquerda == NULL) {
            Cel *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Cel *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Cel *temp = BuscarMaiorEsquerda(raiz);
        raiz->conteudo = temp->conteudo;
        raiz->esquerda = Remover(raiz->esquerda, temp);
    }
    return raiz;
}
