#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó AVL
typedef struct NoAVL {
    int dado;
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
} NoAVL;

// Protótipos
NoAVL* criarNoAVL(int valor);
int altura(NoAVL* no);
int max_value(int a, int b);
int fatorBalanceamento(NoAVL* no);
NoAVL* rotacaoDireita(NoAVL* y);
NoAVL* rotacaoEsquerda(NoAVL* x);
NoAVL* balancear(NoAVL* no);
NoAVL* inserirAVL(NoAVL* no, int valor);
NoAVL* removerAVL(NoAVL* raiz, int valor);
NoAVL* encontrarMinAVL(NoAVL* no);
void liberarArvoreAVL(NoAVL* raiz);
void preOrdemAVL(NoAVL* raiz);
void inOrdemAVL(NoAVL* raiz);
void posOrdemAVL(NoAVL* raiz);

int main(void) {
    NoAVL* raiz = NULL;

    raiz = inserirAVL(raiz, 50);
    raiz = inserirAVL(raiz, 30);
    raiz = inserirAVL(raiz, 70);
    raiz = inserirAVL(raiz, 20);
    raiz = inserirAVL(raiz, 40);
    raiz = inserirAVL(raiz, 60);
    raiz = inserirAVL(raiz, 80);

    printf("Percurso em pre-ordem: ");
    preOrdemAVL(raiz);
    printf("\n");

    printf("Percurso em in-ordem: ");
    inOrdemAVL(raiz);
    printf("\n");

    printf("Percurso em pos-ordem: ");
    posOrdemAVL(raiz);
    printf("\n");

    printf("\nRemovendo o valor 70...\n");
    raiz = removerAVL(raiz, 70);

    printf("Percurso em in-ordem apos remocao: ");
    inOrdemAVL(raiz);
    printf("\n");

    liberarArvoreAVL(raiz);

    return 0;
}

NoAVL* criarNoAVL(int valor) {
    NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));
    if (!novo) {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    novo->dado = valor;
    novo->altura = 1;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

int altura(NoAVL* no) {
    return no ? no->altura : 0;
}

int max_value(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(NoAVL* no) {
    return no ? altura(no->esquerda) - altura(no->direita) : 0;
}

NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max_value(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max_value(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max_value(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max_value(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

NoAVL* balancear(NoAVL* no) {
    int fb = fatorBalanceamento(no);

    // Caso esquerda pesada
    if (fb > 1) {
        if (fatorBalanceamento(no->esquerda) < 0)
            no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso direita pesada
    if (fb < -1) {
        if (fatorBalanceamento(no->direita) > 0)
            no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

NoAVL* inserirAVL(NoAVL* no, int valor) {
    if (!no) return criarNoAVL(valor);

    if (valor < no->dado)
        no->esquerda = inserirAVL(no->esquerda, valor);
    else if (valor > no->dado)
        no->direita = inserirAVL(no->direita, valor);
    else
        return no; // Ignora duplicados

    no->altura = 1 + max_value(altura(no->esquerda), altura(no->direita));
    return balancear(no);
}

NoAVL* encontrarMinAVL(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

NoAVL* removerAVL(NoAVL* raiz, int valor) {
    if (!raiz) return raiz;

    if (valor < raiz->dado)
        raiz->esquerda = removerAVL(raiz->esquerda, valor);
    else if (valor > raiz->dado)
        raiz->direita = removerAVL(raiz->direita, valor);
    else {
        if (!raiz->esquerda || !raiz->direita) {
            NoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            free(raiz);
            return temp;
        } else {
            NoAVL* temp = encontrarMinAVL(raiz->direita);
            raiz->dado = temp->dado;
            raiz->direita = removerAVL(raiz->direita, temp->dado);
        }
    }

    raiz->altura = 1 + max_value(altura(raiz->esquerda), altura(raiz->direita));
    return balancear(raiz);
}

void liberarArvoreAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        liberarArvoreAVL(raiz->esquerda);
        liberarArvoreAVL(raiz->direita);
        free(raiz);
    }
}

void preOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        preOrdemAVL(raiz->esquerda);
        preOrdemAVL(raiz->direita);
    }
}

void inOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        inOrdemAVL(raiz->esquerda);
        printf("%d ", raiz->dado);
        inOrdemAVL(raiz->direita);
    }
}

void posOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        posOrdemAVL(raiz->esquerda);
        posOrdemAVL(raiz->direita);
        printf("%d ", raiz->dado);
    }
}
