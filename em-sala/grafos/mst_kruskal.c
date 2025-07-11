#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int origem, destino, peso;
} Aresta;

int pai[MAX];

int encontrar(int x) {
    if (pai[x] == x) return x;
    return pai[x] = encontrar(pai[x]);
}

void unir(int x, int y) {
    pai[encontrar(x)] = encontrar(y);
}

int comparar(const void *a, const void *b) {
    Aresta *A = (Aresta *)a;
    Aresta *B = (Aresta *)b;
    return A->peso - B->peso;
}

int main() {
    int n, m;
    Aresta arestas[MAX];

    printf("Numero de vertices: ");
    scanf("%d", &n);

    printf("Numero de arestas: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        printf("Aresta %d (origem destino peso): ", i + 1);
        scanf("%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].peso);
    }

    for (int i = 0; i < n; i++) pai[i] = i;

    qsort(arestas, m, sizeof(Aresta), comparar);

    printf("Arestas da Arvore Geradora Minima:\n");

    int total = 0;
    for (int i = 0; i < m; i++) {
        if (encontrar(arestas[i].origem) != encontrar(arestas[i].destino)) {
            unir(arestas[i].origem, arestas[i].destino);
            printf("%d - %d (peso %d)\n", arestas[i].origem, arestas[i].destino, arestas[i].peso);
            total += arestas[i].peso;
        }
    }

    printf("Peso total da AGM: %d\n", total);
    return 0;
}
