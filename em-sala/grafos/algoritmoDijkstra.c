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
void imprimirDistancias(int inicioVertice, int* distancias, int numVertices) {
    printf("\n--- Distancias mais curtas a partir do vertice %d ---\n", inicioVertice);
    for (int i = 0; i < numVertices; i++) {
        printf("Vertice %d: ", i);
        if (distancias[i] == INT_MAX) {
            printf("Inatingivel\n");
        } else {
            printf("%d\n", distancias[i]);
        }
    }
}

// Imprime o caminho mais curto de um vértice inicial para um vértice final
void imprimirCaminho(int inicioVertice, int fimVertice, int* pais, int numVertices) {
    if (fimVertice == -1 || fimVertice == INT_MAX) { // Caso o destino seja inatingível
        printf("Caminho de %d para %d: Inatingivel\n", inicioVertice, fimVertice);
        return;
    }
    
    // Constrói o caminho de trás para frente usando o array 'pais'
    int caminho[numVertices];
    int indiceCaminho = 0;
    int atual = fimVertice;

    while (atual != -1 && indiceCaminho < numVertices) { // Evita loop infinito em caso de erro lógico
        caminho[indiceCaminho++] = atual;
        atual = pais[atual];
    }

    // Imprime o caminho na ordem correta (inverso do que foi construído)
    printf("Caminho de %d para %d: ", inicioVertice, fimVertice);
    if (indiceCaminho == 0 && inicioVertice != fimVertice) { // Se não encontrou caminho e não é o mesmo vértice
        printf("Nao encontrado (erro na reconstrucao ou destino inatingivel)\n");
        return;
    }

    for (int i = indiceCaminho - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}


// --- Implementação Principal do Algoritmo de Dijkstra ---

// Executa o algoritmo de Dijkstra a partir de um vértice inicial
void executarDijkstra(Grafo* grafo, int inicioVertice) {
    int numVertices = grafo->numVertices;
    int* distancias = (int*)malloc(numVertices * sizeof(int));      // Armazena as menores distâncias conhecidas
    int* visitado = (int*)malloc(numVertices * sizeof(int));       // Marca os vértices já processados
    int* pais = (int*)malloc(numVertices * sizeof(int));           // Armazena o predecessor no caminho mais curto

    if (distancias == NULL || visitado == NULL || pais == NULL) {
        perror("Erro ao alocar memoria para arrays do Dijkstra");
        exit(EXIT_FAILURE);
    }

    // Inicialização: todas as distâncias como infinito, nenhum visitado, nenhum pai
    for (int i = 0; i < numVertices; i++) {
        distancias[i] = INT_MAX;
        visitado[i] = 0;
        pais[i] = -1;
    }
    distancias[inicioVertice] = 0; // A distância do vértice inicial para si mesmo é 0

    // Loop principal: executa V-1 vezes para encontrar as distâncias mais curtas
    for (int contador = 0; contador < numVertices - 1; contador++) {
        // Seleciona o vértice não visitado com a menor distância
        int u = encontrarVerticeComMenorDistancia(distancias, visitado, numVertices);

        // Se nenhum vértice puder ser alcançado, ou todos foram visitados, sai do loop
        if (u == -1) {
            break;
        }

        // Marca o vértice selecionado como visitado
        visitado[u] = 1;

        // Percorre todos os vizinhos do vértice 'u'
        Aresta* arestaAtual = grafo->listasAdj[u];
        while (arestaAtual != NULL) {
            int v = arestaAtual->destino;
            int peso = arestaAtual->peso;

            // Relaxamento: Se 'v' ainda não foi visitado E
            // se um caminho mais curto para 'v' for encontrado através de 'u'
            if (!visitado[v] && distancias[u] != INT_MAX && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso; // Atualiza a distância de 'v'
                pais[v] = u;                          // Define 'u' como o pai de 'v' no caminho mais curto
            }
            arestaAtual = arestaAtual->proxima;
        }
    }

    // Imprime os resultados
    imprimirDistancias(inicioVertice, distancias, numVertices);

    printf("\n--- Reconstrucao dos Caminhos ---\n");
    for (int i = 0; i < numVertices; i++) {
        if (i == inicioVertice) {
            printf("Caminho de %d para %d: %d (Inicio)\n", inicioVertice, i, inicioVertice);
            continue;
        }
        imprimirCaminho(inicioVertice, i, pais, numVertices);
    }

    // Libera a memória alocada para os arrays temporários
    free(distancias);
    free(visitado);
    free(pais);
}

// --- Função Principal para Testar ---

int main() {
    // Mapeamento dos vértices do exemplo anterior para números inteiros:
    // A=0, B=1, C=2, D=3, E=4, F=5
    int numVertices = 6;
    Grafo* meuGrafo = criarGrafo(numVertices);

    // Adicionando as arestas e seus pesos ao grafo
    // Lembre-se: `adicionarAresta` já faz para ambas as direções para um grafo não direcionado
    adicionarAresta(meuGrafo, 0, 1, 4); // A (0) - B (1): 4
    adicionarAresta(meuGrafo, 0, 3, 1); // A (0) - D (3): 1
    adicionarAresta(meuGrafo, 1, 2, 2); // B (1) - C (2): 2
    adicionarAresta(meuGrafo, 1, 4, 5); // B (1) - E (4): 5
    adicionarAresta(meuGrafo, 2, 5, 3); // C (2) - F (5): 3
    adicionarAresta(meuGrafo, 3, 4, 1); // D (3) - E (4): 1
    adicionarAresta(meuGrafo, 4, 5, 1); // E (4) - F (5): 1

    printf("Preparando para executar o Algoritmo de Dijkstra...\n");
    executarDijkstra(meuGrafo, 0); // Executa Dijkstra a partir do vértice A (0)

    // Libera toda a memória alocada para o grafo no final
    liberarGrafo(meuGrafo);

    return 0;
}