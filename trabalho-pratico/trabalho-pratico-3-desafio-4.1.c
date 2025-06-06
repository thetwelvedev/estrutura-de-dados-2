/*Nome: Leonardo Vinícius Lima Castro
Matrícula: 2022009946*/
//Desafio 4 (Opcional - Mais Avançado): Heap Genérica ou Heapify Melhorado
//1. Heap Genérica (Usando void* e Ponteiros para Funções):

#include <stdio.h>
#include <stdlib.h>

// Estrutura da heap genérica
typedef struct {
    void **dados; // array de ponteiros para os elementos
    int tamanho;
    int capacidade;
    int (*comparar)(const void *, const void *);
} Heap;

// Função para trocar dois elementos
void trocar(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

// Funções auxiliares
int obterPai(int i) { return (i - 1) / 2; }
int obterFilhoEsquerdo(int i) { return 2 * i + 1; }
int obterFilhoDireito(int i) { return 2 * i + 2; }

// Função de heapificar para cima
void heapificarParaCima(Heap *heap, int i) {
    while (i > 0 && heap->comparar(heap->dados[i], heap->dados[obterPai(i)]) > 0) {
        trocar(&heap->dados[i], &heap->dados[obterPai(i)]);
        i = obterPai(i);
    }
}

// Função de heapificar para baixo
void heapificarParaBaixo(Heap *heap, int i) {
    int maior = i;
    int esq = obterFilhoEsquerdo(i);
    int dir = obterFilhoDireito(i);

    if (esq < heap->tamanho && heap->comparar(heap->dados[esq], heap->dados[maior]) > 0) {
        maior = esq;
    }

    if (dir < heap->tamanho && heap->comparar(heap->dados[dir], heap->dados[maior]) > 0) {
        maior = dir;
    }

    if (maior != i) {
        trocar(&heap->dados[i], &heap->dados[maior]);
        heapificarParaBaixo(heap, maior);
    }
}

// Inserção na heap
void inserirHeap(Heap *heap, void *elemento) {
    if (heap->tamanho >= heap->capacidade) {
        heap->capacidade *= 2;
        heap->dados = realloc(heap->dados, heap->capacidade * sizeof(void *));
    }
    heap->dados[heap->tamanho] = elemento;
    heapificarParaCima(heap, heap->tamanho);
    heap->tamanho++;
}

// Remoção da raiz
void *extrairRaiz(Heap *heap) {
    if (heap->tamanho == 0) return NULL;

    void *raiz = heap->dados[0];
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;
    heapificarParaBaixo(heap, 0);
    return raiz;
}

// Criar heap com função de comparação
Heap *criarHeap(int capacidade, int (*comparar)(const void *, const void *)) {
    Heap *heap = malloc(sizeof(Heap));
    heap->dados = malloc(capacidade * sizeof(void *));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    heap->comparar = comparar;
    return heap;
}

// Liberar memória da heap
void destruirHeap(Heap *heap) {
    free(heap->dados);
    free(heap);
}

// Função de comparação para inteiros (heap máxima)
int compararInt(const void *a, const void *b) {
    int intA = *(int *)a;
    int intB = *(int *)b;
    return intA - intB;
}

// Função principal (teste)
int main() {
    Heap *heap = criarHeap(10, compararInt);

    // Inserir alguns inteiros
    int *valores[5];
    for (int i = 0; i < 5; i++) {
        valores[i] = malloc(sizeof(int));
        *valores[i] = i * 10;  // 0, 10, 20, 30, 40
        inserirHeap(heap, valores[i]);
    }

    // Remover e imprimir elementos
    printf("Elementos removidos (em ordem decrescente):\n");
    for (int i = 0; i < 5; i++) {
        int *removido = (int *)extrairRaiz(heap);
        printf("%d\n", *removido);
        free(removido); // liberar memória
    }

    destruirHeap(heap);
    return 0;
}
