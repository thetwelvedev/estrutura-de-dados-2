#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct TreeNodeVector {
    int data;
    bool exists; // Flag para indicar se o nó existe
} TreeNodeVector;

// Vetor que representa a árvore
TreeNodeVector arvore[MAX_NODES];

//Protótipos
void inicializarArvoreVetor();
void adicionarFilhoEsquerdoVetor(int indicePai, int valor);
void adicionarFilhoDireitoVetor(int indicePai, int valor);
int obterValorNoVetor(int indice);


int main(void) {
    // Inicializa a árvore (define todos os nós como inexistentes e cria a raiz)
    inicializarArvoreVetor();

    // Adiciona filhos à raiz (índice 0)
    adicionarFilhoEsquerdoVetor(0, 5);
    adicionarFilhoDireitoVetor(0, 15);

    // Adiciona mais alguns nós para testar
    adicionarFilhoEsquerdoVetor(1, 3);  // Filho esquerdo do nó no índice 1
    adicionarFilhoDireitoVetor(1, 7);   // Filho direito do nó no índice 1
    adicionarFilhoEsquerdoVetor(2, 12); // Filho esquerdo do nó no índice 2
    adicionarFilhoDireitoVetor(2, 18);  // Filho direito do nó no índice 2

    // Exibe valores de alguns nós
    printf("Raiz: %d\n", obterValorNoVetor(0));
    printf("Filho esquerdo da raiz: %d\n", obterValorNoVetor(1));
    printf("Filho direito da raiz: %d\n", obterValorNoVetor(2));
    printf("Filho esquerdo do no 1: %d\n", obterValorNoVetor(3));
    printf("Filho direito do no 1: %d\n", obterValorNoVetor(4));
    printf("Filho esquerdo do no 2: %d\n", obterValorNoVetor(5));
    printf("Filho direito do no 2: %d\n", obterValorNoVetor(6));

    return 0;
}



// Inicializa a árvore
void inicializarArvoreVetor() {
    for (int i = 0; i < MAX_NODES; i++) {
        arvore[i].exists = false;
    }

    // Adicionando a raiz
    int valorRaiz = 10;
    arvore[0].data = valorRaiz;
    arvore[0].exists = true;
}

// Adiciona um nó filho à esquerda
void adicionarFilhoEsquerdoVetor(int indicePai, int valor) {
    int indiceEsquerdo = 2 * indicePai + 1;
    if (indiceEsquerdo < MAX_NODES) {
        arvore[indiceEsquerdo].data = valor;
        arvore[indiceEsquerdo].exists = true;
    } else {
        printf("Limite da árvore atingido (esquerda).\n");
    }
}

// Adiciona um nó filho à direita
void adicionarFilhoDireitoVetor(int indicePai, int valor) {
    int indiceDireito = 2 * indicePai + 2;
    if (indiceDireito < MAX_NODES) {
        arvore[indiceDireito].data = valor;
        arvore[indiceDireito].exists = true;
    } else {
        printf("Limite da árvore atingido (direita).\n");
    }
}

// Obtém o valor de um nó no vetor
int obterValorNoVetor(int indice) {
    if (indice < MAX_NODES && arvore[indice].exists) {
        return arvore[indice].data;
    } else {
        printf("Índice inválido ou nó inexistente.\n");
        return -1; // Valor de erro
    }
}


