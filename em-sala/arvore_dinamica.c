#include <stdio.h>
#include <stdlib.h>

typedef struct NoDinamico{
    int dado;
    struct NoDinamico *esquerda;
    struct NoDinamico *direita;
} NoDinamico;

NoDinamico* criarNoDinamico(int valor);
void inserirEsquerdaDinamico(NoDinamico* pai, int valor);
void inserirDireitaDinamico(NoDinamico* pai, int valor);
void percorrerPreOrdemDinamico(NoDinamico* raiz);
void percorrerInOrdemDinamico(NoDinamico* raiz);
void percorrerPosOrdemDinamico(NoDinamico* raiz);
void liberarArvoreDinamico(NoDinamico* raiz);

int main(void) {
    // Cria a raiz da árvore
    NoDinamico* raiz = criarNoDinamico(10);

    // Insere filhos à esquerda e direita da raiz
    inserirEsquerdaDinamico(raiz, 5);
    inserirDireitaDinamico(raiz, 15);

    // Insere mais alguns nós para testar
    inserirEsquerdaDinamico(raiz->esquerda, 3);
    inserirDireitaDinamico(raiz->esquerda, 7);
    inserirEsquerdaDinamico(raiz->direita, 12);
    inserirDireitaDinamico(raiz->direita, 18);

    printf("Percurso em pre-ordem: ");
    percorrerPreOrdemDinamico(raiz);
    printf("\n");

    printf("Percurso em in-ordem: ");
    percorrerInOrdemDinamico(raiz);
    printf("\n");

    printf("Percurso em pos-ordem: ");
    percorrerPosOrdemDinamico(raiz);
    printf("\n");

    // Libera a memória da árvore
    liberarArvoreDinamico(raiz);

    return 0;
}


// Cria um novo nó
NoDinamico* criarNoDinamico(int valor) {
    NoDinamico* novoNo = (NoDinamico*)malloc(sizeof(NoDinamico));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no");
        exit(EXIT_FAILURE);
}
    novoNo->dado = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
return novoNo;
}

// Insere um nó filho à esquerda
void inserirEsquerdaDinamico(NoDinamico* pai, int valor) {
    if (pai == NULL) {
        printf("Pai invalido.\n");
        return;
    }
    pai->esquerda = criarNoDinamico(valor);
}

// Insere um nó filho à direita
void inserirDireitaDinamico(NoDinamico* pai, int valor) {
    if (pai == NULL) {
        printf("Pai invalido.\n");
        return;
    }
    pai->direita = criarNoDinamico(valor);
}

// Percurso em pré-ordem (raiz, esquerda, direita)
void percorrerPreOrdemDinamico(NoDinamico* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        percorrerPreOrdemDinamico(raiz->esquerda);
        percorrerPreOrdemDinamico(raiz->direita);
    }
}

// Percurso em in-ordem (esquerda, raiz, direita)
void percorrerInOrdemDinamico(NoDinamico* raiz) {
    if (raiz != NULL) {
        percorrerInOrdemDinamico(raiz->esquerda);
        printf("%d ", raiz->dado);
        percorrerInOrdemDinamico(raiz->direita);
    }
}

// Percurso em pós-ordem (esquerda, direita, raiz)
void percorrerPosOrdemDinamico(NoDinamico* raiz) {
    if (raiz != NULL) {
        percorrerPosOrdemDinamico(raiz->esquerda);
        percorrerPosOrdemDinamico(raiz->direita);
        printf("%d ", raiz->dado);
    }
}

// Função para liberar a memória da árvore (importante para evitar vazamentos)
void liberarArvoreDinamico(NoDinamico* raiz) {
    if (raiz != NULL) {
        liberarArvoreDinamico(raiz->esquerda);
        liberarArvoreDinamico(raiz->direita);
        free(raiz);
    }
}
