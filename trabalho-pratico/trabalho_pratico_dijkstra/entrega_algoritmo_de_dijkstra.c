#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para INT_MAX, que representa o "infinito"

// --- Definição das Estruturas de Dados ---

// Representa uma aresta ou um vizinho em um grafo
typedef struct Aresta {
    int destino;        // Vértice de destino da aresta
    int peso;           // Peso ou custo da aresta
    struct Aresta* proxima; // Ponteiro para a próxima aresta na lista de adjacência
} Aresta;

// Representa um grafo usando listas de adjacência
typedef struct Grafo {
    int numVertices;    // Número total de vértices no grafo
    Aresta** listasAdj; // Array de ponteiros para as listas de adjacência de cada vértice
} Grafo;

// --- Funções de Manipulação do Grafo ---

// Cria uma nova aresta/nó para a lista de adjacência
Aresta* criarAresta(int destino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    if (novaAresta == NULL) {
        perror("Erro ao alocar memoria para aresta");
        exit(EXIT_FAILURE);
    }
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = NULL;
    return novaAresta;
}

// Cria e inicializa um novo grafo com o número especificado de vértices
Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        perror("Erro ao alocar memoria para grafo");
        exit(EXIT_FAILURE);
    }
    grafo->numVertices = vertices;
    grafo->listasAdj = (Aresta**)malloc(vertices * sizeof(Aresta*));
    if (grafo->listasAdj == NULL) {
        perror("Erro ao alocar memoria para listas de adjacencia");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++) {
        grafo->listasAdj[i] = NULL; // Inicializa todas as listas de adjacência como vazias
    }
    return grafo;
}

// Adiciona uma aresta entre dois vértices com um dado peso.
// Assume que o grafo é não direcionado, adicionando arestas em ambas as direções.
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    // Adiciona a aresta de origem para destino
    Aresta* novaArestaOrigem = criarAresta(destino, peso);
    novaArestaOrigem->proxima = grafo->listasAdj[origem];
    grafo->listasAdj[origem] = novaArestaOrigem;

    // Adiciona a aresta de destino para origem (para grafos não direcionados)
    Aresta* novaArestaDestino = criarAresta(origem, peso);
    novaArestaDestino->proxima = grafo->listasAdj[destino];
    grafo->listasAdj[destino] = novaArestaDestino;
}

// Libera toda a memória alocada para o grafo
void liberarGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        Aresta* atual = grafo->listasAdj[i];
        while (atual != NULL) {
            Aresta* proxima = atual->proxima;
            free(atual);
            atual = proxima;
        }
    }
    free(grafo->listasAdj);
    free(grafo);
}

// --- Funções Auxiliares do Dijkstra ---

// Encontra o vértice não visitado com a menor distância atual
int encontrarVerticeComMenorDistancia(int* distancias, int* visitado, int numVertices) {
    int menorDistancia = INT_MAX;
    int indiceMenor = -1;

    for (int v = 0; v < numVertices; v++) {
        // Verifica se o vértice não foi visitado e se sua distância é a menor encontrada até agora
        if (!visitado[v] && distancias[v] <= menorDistancia) {
            menorDistancia = distancias[v];
            indiceMenor = v;
        }
    }
    return indiceMenor;
}

// Imprime as distâncias mais curtas do vértice de partida para todos os outros vértices
void imprimirDistancias(int inicioVertice, int* distancias, char* nomes[], int numVertices) {
    printf("\n--- Distancias mais curtas a partir de %s ---\n", nomes[inicioVertice]);
    for (int i = 0; i < numVertices; i++) {
        if (distancias[i] == INT_MAX)
            printf("%s: Inatingivel\n", nomes[i]);
        else
            printf("%s: %d minutos\n", nomes[i], distancias[i]);
    }
}

// Imprime o caminho mais curto de um vértice inicial para um vértice final
void imprimirCaminho(int inicioVertice, int fimVertice, int* pais, char* nomes[]) {
    if (fimVertice == -1 || fimVertice == INT_MAX) {
        printf("Caminho de %s para %s: Inatingivel\n", nomes[inicioVertice], nomes[fimVertice]);
        return;
    }

    int caminho[100];
    int indiceCaminho = 0;
    int atual = fimVertice;

    while (atual != -1 && indiceCaminho < 100) {
        caminho[indiceCaminho++] = atual;
        atual = pais[atual];
    }

    printf("O caminho percorrido e: ");
    for (int i = indiceCaminho - 1; i >= 0; i--) {
        printf("%s", nomes[caminho[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// --- Implementação Principal do Algoritmo de Dijkstra ---

// Executa o algoritmo de Dijkstra a partir de um vértice inicial
void executarDijkstra(Grafo* grafo, int inicioVertice, int* distancias, int* pais) {
    int numVertices = grafo->numVertices;
    int* visitado = (int*)malloc(numVertices * sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memoria para array de visitados");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numVertices; i++) {
        distancias[i] = INT_MAX;
        visitado[i] = 0;
        pais[i] = -1;
    }
    distancias[inicioVertice] = 0;

    for (int contador = 0; contador < numVertices - 1; contador++) {
        int u = encontrarVerticeComMenorDistancia(distancias, visitado, numVertices);
        if (u == -1) break;

        visitado[u] = 1;
        Aresta* arestaAtual = grafo->listasAdj[u];
        while (arestaAtual != NULL) {
            int v = arestaAtual->destino;
            int peso = arestaAtual->peso;

            if (!visitado[v] && distancias[u] != INT_MAX && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                pais[v] = u;
            }
            arestaAtual = arestaAtual->proxima;
        }
    }

    free(visitado);
}

int main() {
    int numVertices = 8;
    Grafo* grafo = criarGrafo(numVertices);

    // Mapeamento dos vértices para nomes de bairros
    char* nomes[] = {
        "Centro", "Mecejana", "Cauame", "Asa_Branca",
        "Carana", "Cidade_Satelite", "Canarinho", "Pintolandia"
    };

    // Adicionando as arestas com seus pesos
    adicionarAresta(grafo, 0, 1, 4);
    adicionarAresta(grafo, 0, 2, 3);
    adicionarAresta(grafo, 1, 3, 5);
    adicionarAresta(grafo, 2, 3, 2);
    adicionarAresta(grafo, 3, 4, 4);
    adicionarAresta(grafo, 4, 5, 6);
    adicionarAresta(grafo, 5, 6, 3);
    adicionarAresta(grafo, 6, 7, 1);
    adicionarAresta(grafo, 1, 4, 2);
    adicionarAresta(grafo, 2, 5, 7);
    adicionarAresta(grafo, 0, 6, 10);
    adicionarAresta(grafo, 0, 7, 12);

    // Executa Dijkstra a partir do vértice "Centro" (0)
    int distancias[numVertices];
    int pais[numVertices];
    int inicio = 0;

    executarDijkstra(grafo, inicio, distancias, pais);
    imprimirDistancias(inicio, distancias, nomes, numVertices);

    // Interação com o usuário
    int destino;
    do {
        printf("\nDigite o numero do bairro de destino (0 a 7) ou -1 para sair:\n");
        for (int i = 0; i < numVertices; i++) {
            printf("%d - %s\n", i, nomes[i]);
        }
        printf("Destino: ");
        scanf("%d", &destino);

        if (destino == -1) break;

        if (destino < 0 || destino >= numVertices) {
            printf("Destino invalido.\n");
            continue;
        }

        if (distancias[destino] == INT_MAX) {
            printf("A distancia de %s para %s e: Inatingivel\n", nomes[inicio], nomes[destino]);
        } else {
            printf("A distancia mais curta de %s para %s e: %d minutos.\n", nomes[inicio], nomes[destino], distancias[destino]);
            imprimirCaminho(inicio, destino, pais, nomes);
        }

    } while (destino != -1);

    liberarGrafo(grafo);
    return 0;
}
