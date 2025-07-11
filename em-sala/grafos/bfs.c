#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
int visitado[MAX];
int fila[MAX];
int n, frente = 0, tras = 0;

void enqueue(int v) {
    fila[tras++] = v;
}

int dequeue() {
    return fila[frente++];
}

int isEmpty() {
    return frente == tras;
}

void bfs(int inicio) {
    visitado[inicio] = 1;
    enqueue(inicio);

    while (!isEmpty()) {
        int v = dequeue();
        printf("%d ", v);

        for (int i = 0; i < n; i++) {
            if (adj[v][i] && !visitado[i]) {
                visitado[i] = 1;
                enqueue(i);
            }
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
        adj[destino][origem] = 1;
    }

    for (int i = 0; i < n; i++) visitado[i] = 0;

    printf("BFS a partir do vertice 0: ");
    bfs(0);
    printf("\n");

    return 0;
}
