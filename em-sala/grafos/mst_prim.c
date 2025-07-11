#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int n; // número de vértices
int adj[MAX][MAX]; // matriz de adjacência

void prim() {
    int custoTotal = 0;
    int selecionado[MAX] = {0};
    int noSelecionado = 0;

    selecionado[0] = 1; // começa pelo vértice 0

    printf("Arestas da Arvore Geradora Minima (Prim):\n");

    while (noSelecionado < n - 1) {
        int minimo = INF;
        int x = -1, y = -1;

        for (int i = 0; i < n; i++) {
            if (selecionado[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selecionado[j] && adj[i][j]) {
                        if (adj[i][j] < minimo) {
                            minimo = adj[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        if (x != -1 && y != -1) {
            printf("%d - %d (peso %d)\n", x, y, adj[x][y]);
            custoTotal += adj[x][y];
            selecionado[y] = 1;
            noSelecionado++;
        }
    }

    printf("Peso total da AGM: %d\n", custoTotal);
}

int main() {
    int arestas, origem, destino, peso;

    printf("Numero de vertices: ");
    scanf("%d", &n);

    // Inicializa a matriz com 0 (ou INF se preferir)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Numero de arestas: ");
    scanf("%d", &arestas);

    for (int i = 0; i < arestas; i++) {
        printf("Aresta %d (origem destino peso): ", i + 1);
        scanf("%d %d %d", &origem, &destino, &peso);
        adj[origem][destino] = peso;
        adj[destino][origem] = peso; // grafo não-direcionado
    }

    prim();

    return 0;
}
