#include <stdio.h>
#include <stdlib.h>

// Função para imprimir o vetor
void imprimirVetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// 1. Ordenação por Inserção (Insertion Sort)
void Insercao(int n, int v[]) {
    int i, j, x;
    for (j = 1; j < n; j++) {
        x = v[j];
        for (i = j - 1; i >= 0 && v[i] > x; i--)
            v[i + 1] = v[i];
        v[i + 1] = x;
    }
}

// 2. Ordenação por Seleção (Selection Sort)
void Selecao(int n, int v[]) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[min])
                min = j;
        }
        // Troca v[i] com v[min]
        temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

// 3. Ordenação Shell (Shell Sort)
void shellSort(int v[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
}

// 4. Função de Intercalação para Merge Sort
void Intercala(int p, int q, int r, int v[]) {
    int i, j, k, *w;
    w = (int *)malloc((r - p) * sizeof(int));
    i = p;
    j = q;
    k = 0;
    while (i < q && j < r) {
        if (v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }
    while (i < q)
        w[k++] = v[i++];
    while (j < r)
        w[k++] = v[j++];
    for (i = p; i < r; i++)
        v[i] = w[i - p];
    free(w);
}

// 5. Ordenação por Intercalação (Merge Sort)
void Mergesort(int p, int r, int v[]) {
    if (p < r - 1) {
        int q = (p + r) / 2;
        Mergesort(p, q, v);
        Mergesort(q, r, v);
        Intercala(p, q, r, v);
    }
}

// 6. Função auxiliar para separar os elementos no Quick Sort
int Separa(int p, int r, int v[]) {
    int c = v[r];
    int j = p;
    for (int k = p; k < r; k++) {
        if (v[k] <= c) {
            int t = v[j];
            v[j] = v[k];
            v[k] = t;
            j++;
        }
    }
    v[r] = v[j];
    v[j] = c;
    return j;
}

// 7. Ordenação Rápida (Quick Sort)
void Quicksort(int p, int r, int v[]) {
    if (p < r) {
        int j = Separa(p, r, v);
        Quicksort(p, j - 1, v);
        Quicksort(j + 1, r, v);
    }
}

// Função principal para testar os algoritmos de ordenação
int main() {
    int v1[] = {34, 7, 23, 32, 5, 62};
    int v2[] = {34, 7, 23, 32, 5, 62};
    int v3[] = {34, 7, 23, 32, 5, 62};
    int v4[] = {34, 7, 23, 32, 5, 62};
    int v5[] = {34, 7, 23, 32, 5, 62};
    int n = sizeof(v1) / sizeof(v1[0]);

    printf("Vetor original:\n");
    imprimirVetor(v1, n);

    // Testando Insertion Sort
    Insercao(n, v1);
    printf("Insertion Sort:\n");
    imprimirVetor(v1, n);

    // Testando Selection Sort
    Selecao(n, v2);
    printf("Selection Sort:\n");
    imprimirVetor(v2, n);

    // Testando Shell Sort
    shellSort(v3, n);
    printf("Shell Sort:\n");
    imprimirVetor(v3, n);

    // Testando Merge Sort
    Mergesort(0, n, v4);
    printf("Merge Sort:\n");
    imprimirVetor(v4, n);

    // Testando Quick Sort
    Quicksort(0, n - 1, v5);
    printf("Quick Sort:\n");
    imprimirVetor(v5, n);

    return 0;
}
