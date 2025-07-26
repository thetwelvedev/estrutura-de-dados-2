#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 4 // Número de vértices/cidades

// Função para calcular o custo total de um caminho
int calcularCusto(int grafo[V][V], int caminho[]) {
    int custo = 0;
    for (int i = 0; i < V - 1; i++) {
        custo += grafo[caminho[i]][caminho[i + 1]];
    }
    custo += grafo[caminho[V - 1]][caminho[0]]; // Volta para a cidade inicial
    return custo;
}

// Função para trocar dois elementos de um array
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função recursiva para gerar todas as permutações possíveis
void encontrarCaminhoMaisCurto(int grafo[V][V], int caminho[], int inicio, int tamanho, int *custoMinimo, int melhorCaminho[]) {
    if (inicio == tamanho - 1) {
        int custoAtual = calcularCusto(grafo, caminho);
        if (custoAtual < *custoMinimo) {
            *custoMinimo = custoAtual;
            for (int i = 0; i < V; i++) {
                melhorCaminho[i] = caminho[i];
            }
        }
        return;
    }

    for (int i = inicio; i < tamanho; i++) {
        trocar(&caminho[inicio], &caminho[i]);
        encontrarCaminhoMaisCurto(grafo, caminho, inicio + 1, tamanho, custoMinimo, melhorCaminho);
        trocar(&caminho[inicio], &caminho[i]); // Backtrack
    }
}

int main() {
    // Matriz de adjacência representando o grafo das cidades e distâncias
    int grafo[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int caminho[V];
    for (int i = 0; i < V; i++) {
        caminho[i] = i; // Inicializa o caminho com a ordem padrão 0, 1, 2, 3
    }

    int custoMinimo = INT_MAX;
    int melhorCaminho[V];

    encontrarCaminhoMaisCurto(grafo, caminho, 0, V, &custoMinimo, melhorCaminho);

    printf("Caminho mais curto encontrado:\n");
    for (int i = 0; i < V; i++) {
        printf("%d -> ", melhorCaminho[i]);
    }
    printf("%d\n", melhorCaminho[0]); // Volta para o início

    printf("Custo total: %d\n", custoMinimo);

    return 0;
}