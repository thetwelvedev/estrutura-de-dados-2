#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para os nós da lista encadeada
typedef struct No {
    int chave;
    struct No* proximo;
} No;

// Estrutura para a tabela hash
typedef struct {
    No** tabela;
    int tamanho;
} TabelaHash;

// --- Função para criar um novo nó ---
No* criarNo(int chave) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->chave = chave;
    novo->proximo = NULL;
    return novo;
}

// --- Função para inicializar a tabela hash ---
TabelaHash* inicializarTabela(int tamanho) {
    TabelaHash* th = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (th == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    
    th->tamanho = tamanho;
    th->tabela = (No**)malloc(tamanho * sizeof(No*));
    if (th->tabela == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    
    for (int i = 0; i < tamanho; i++) {
        th->tabela[i] = NULL;
    }
    
    return th;
}

// --- Função de Hash por Divisão ---
int calcularHashDivisao(int chave, int tamanhoTabela) {
    if (tamanhoTabela <= 0) {
        return -1;
    }
    
    int hash_valor = chave % tamanhoTabela;
    
    if (hash_valor < 0) {
        hash_valor += tamanhoTabela;
    }
    
    return hash_valor;
}

// --- Função para inserir na tabela hash ---
void inserir(TabelaHash* th, int chave) {
    int indice = calcularHashDivisao(chave, th->tamanho);
    No* novo = criarNo(chave);
    
    // Inserção no início da lista
    novo->proximo = th->tabela[indice];
    th->tabela[indice] = novo;
}

// --- Função para imprimir a tabela hash ---
void imprimirTabela(TabelaHash* th) {
    printf("\n=== Tabela Hash com Encadeamento (Tamanho %d) ===\n", th->tamanho);
    for (int i = 0; i < th->tamanho; i++) {
        printf("[%d]: ", i);
        No* atual = th->tabela[i];
        while (atual != NULL) {
            printf("%d -> ", atual->chave);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

// --- Função para liberar a memória ---
void liberarTabela(TabelaHash* th) {
    for (int i = 0; i < th->tamanho; i++) {
        No* atual = th->tabela[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(th->tabela);
    free(th);
}

// --- Função Principal (main) ---
int main() {
    int chaves[] = {42, 17, 99, 123, 7, 256, 42, 17}; // Array com possíveis colisões
    int num_chaves = sizeof(chaves) / sizeof(chaves[0]);
    int tamanhoTabela = 7;

    // Inicializa a tabela hash
    TabelaHash* th = inicializarTabela(tamanhoTabela);

    // Insere todas as chaves
    for (int i = 0; i < num_chaves; i++) {
        inserir(th, chaves[i]);
    }

    // Imprime a tabela hash
    imprimirTabela(th);

    // Libera a memória
    liberarTabela(th);

    return 0;
}