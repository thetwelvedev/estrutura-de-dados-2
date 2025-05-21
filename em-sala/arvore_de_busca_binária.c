#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int dado;
    struct No *esquerda;
    struct No *direita;
} No;

No* criarNo(int valor);
No *inserirABB(No *raiz, int valor);
No* removerABB(No* raiz, int chave);
No* encontrarMinimo(No* no);
void liberarArvore(No* raiz);
void preOrdem(No* raiz);
void inOrdem(No* raiz);
void posOrdem(No* raiz);

int main(void) {
    No *raiz = NULL;

    // Inserção de elementos na árvore
    raiz = inserirABB(raiz, 50);
    raiz = inserirABB(raiz, 30);
    raiz = inserirABB(raiz, 70);
    raiz = inserirABB(raiz, 20);
    raiz = inserirABB(raiz, 40);
    raiz = inserirABB(raiz, 60);
    raiz = inserirABB(raiz, 80);

    printf("Percurso em pre-ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Percurso em in-ordem: ");
    inOrdem(raiz);
    printf("\n");

    printf("Percurso em pos-ordem: ");
    posOrdem(raiz);
    printf("\n");

    // Remoção de um elemento
    printf("\nRemovendo o valor 70...\n");
    raiz = removerABB(raiz, 70);

    printf("Percurso em in-ordem apos remocao: ");
    inOrdem(raiz);
    printf("\n");

    // Libera a memória alocada pela árvore
    liberarArvore(raiz);

    return 0;
}


// Cria um novo nó
No* criarNo(int valor){
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
return novoNo;
}

// Insere um novo valor na ABB
No *inserirABB(No *raiz, int valor)
{
    // Caso base: árvore vazia, cria um novo nó
    if (raiz == NULL){
        return criarNo(valor);
    }
    // Se o valor for menor que o valor do nó atual, insere na subárvore esquerda
    if (valor < raiz->dado){
        raiz->esquerda = inserirABB(raiz->esquerda, valor);
    }
    // Se o valor for maior que o valor do nó atual, insere na subárvore direita
    else if (valor > raiz->dado){
        raiz->direita = inserirABB(raiz->direita, valor);
    }
    // Se o valor já existir, podemos ignorar a inserção (para evitar duplicados)
    // ou implementar uma lógica específica para duplicados.
    return raiz; // Retorna o ponteiro da raiz (que pode ter mudado)
}

// Remove um nó com um determinado valor da ABB
No* removerABB(No* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    // Percorre a árvore para encontrar o nó a ser removido
    if (chave < raiz->dado) {
        raiz->esquerda = removerABB(raiz->esquerda, chave);
    } else if (chave > raiz->dado) {
        raiz->direita = removerABB(raiz->direita, chave);
    }
    // Nó encontrado
    else {
        // Caso 1: Nó folha
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho (direita)
        else if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }
        // Caso 2: Nó com um filho (esquerda)
        else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            // Encontra o sucessor (menor nó na subárvore direita)
            No* sucessor = encontrarMinimo(raiz->direita);
            // Copia o valor do sucessor para o nó atual
            raiz->dado = sucessor->dado;
            // Remove o sucessor da subárvore direita
            raiz->direita = removerABB(raiz->direita, sucessor->dado);
        }
    }

    return raiz; // Retorna o ponteiro da raiz (que pode ter mudado)
}

// Encontra o nó com o menor valor em uma subárvore (usado para o sucessor)
No* encontrarMinimo(No* no) {
    No* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Liberar memória da árvore inteira
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

//Ordens de percurso
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void inOrdem(No* raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        inOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->dado);
    }
}
