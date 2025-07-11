#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX]; // matriz de adjacência
int visitado[MAX];
int n; // número de vértices

void dfs(int v) {
    visitado[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visitado[i]) {
            dfs(i);
        }
    }
}

int main() {
    int arestas, origem, destino;

    printf("Numero de vertices: ");
    scanf("%d", &n);

    printf("Numero de arestas: ");
    scanf("%d", &arestas);

    for (int i = 0; i < arestas; i++) {
        printf("Aresta %d (origem destino): ", i + 1);
        scanf("%d %d", &origem, &destino);
        adj[origem][destino] = 1;
        adj[destino][origem] = 1; // se for grafo não-direcionado
    }

    for (int i = 0; i < n; i++) visitado[i] = 0;

    printf("DFS a partir do vertice 0: ");
    dfs(0);
    printf("\n");

    return 0;
}
