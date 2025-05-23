#include <stdio.h>
#include <stdlib.h>

// Estruturas de dados
typedef struct NoABB {
    int dado;
    struct NoABB *esquerda;
    struct NoABB *direita;
} NoABB;

typedef struct NoAVL {
    int dado;
    int altura;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
} NoAVL;

// Protótipos para ABB
NoABB* criarNoABB(int valor);
NoABB* inserirABB(NoABB* raiz, int valor);
NoABB* removerABB(NoABB* raiz, int chave);
NoABB* encontrarMinimoABB(NoABB* no);
void liberarArvoreABB(NoABB* raiz);
void preOrdemABB(NoABB* raiz);
void inOrdemABB(NoABB* raiz);
void posOrdemABB(NoABB* raiz);
int buscarABB(NoABB* raiz, int valor, int* contador);

// Protótipos para AVL
NoAVL* criarNoAVL(int valor);
int alturaAVL(NoAVL* no);
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
int buscarAVL(NoAVL* raiz, int valor, int* contador);

// Funções auxiliares
void imprimirResultadoBusca(int encontrado, int contador);

int main(void) {
    // Criar e popular árvores
    NoABB* raizABB = NULL;
    NoAVL* raizAVL = NULL;
    
    int valores[] = {10, 20, 30, 40, 50, 60, 70, 80, 85, 75, 65, 55, 45, 35, 25};
    int n = sizeof(valores)/sizeof(valores[0]);
    
    for (int i = 0; i < n; i++) {
        printf("Inserindo %d...\n", valores[i]);
        raizABB = inserirABB(raizABB, valores[i]);
        raizAVL = inserirAVL(raizAVL, valores[i]);
        
        printf("ABB apos insercao: ");
        inOrdemABB(raizABB);
        printf("\n");
        
        printf("AVL apos insercao: ");
        inOrdemAVL(raizAVL);
        printf("\n\n");
    }
    
    printf("PERCURSOS:\n");
    
    printf("ABB - Pre-ordem: ");
    preOrdemABB(raizABB);
    printf("\n");
    
    printf("AVL - Pre-ordem: ");
    preOrdemAVL(raizAVL);
    printf("\n\n");
    
    printf("ABB - In-ordem: ");
    inOrdemABB(raizABB);
    printf("\n");
    
    printf("AVL - In-ordem: ");
    inOrdemAVL(raizAVL);
    printf("\n\n");
    
    printf("ABB - Pos-ordem: ");
    posOrdemABB(raizABB);
    printf("\n");
    
    printf("AVL - Pos-ordem: ");
    posOrdemAVL(raizAVL);
    printf("\n\n");
    
    printf("BUSCAS:\n");
    int alvo = 60;
    int contadorABB = 0, contadorAVL = 0;
    
    printf("Buscando %d na ABB...\n", alvo);
    int encontradoABB = buscarABB(raizABB, alvo, &contadorABB);
    imprimirResultadoBusca(encontradoABB, contadorABB);
    
    printf("Buscando %d na AVL...\n", alvo);
    int encontradoAVL = buscarAVL(raizAVL, alvo, &contadorAVL);
    imprimirResultadoBusca(encontradoAVL, contadorAVL);
    
    // Busca por elemento não existente
    alvo = 99;
    contadorABB = 0;
    contadorAVL = 0;
    
    printf("\nBuscando %d na ABB...\n", alvo);
    encontradoABB = buscarABB(raizABB, alvo, &contadorABB);
    imprimirResultadoBusca(encontradoABB, contadorABB);
    
    printf("Buscando %d na AVL...\n", alvo);
    encontradoAVL = buscarAVL(raizAVL, alvo, &contadorAVL);
    imprimirResultadoBusca(encontradoAVL, contadorAVL);
    
    // Liberar memória
    liberarArvoreABB(raizABB);
    liberarArvoreAVL(raizAVL);
    
    return 0;
}

// Implementação das funções para ABB
NoABB* criarNoABB(int valor) {
    NoABB* novoNo = (NoABB*)malloc(sizeof(NoABB));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

NoABB* inserirABB(NoABB* raiz, int valor) {
    if (raiz == NULL) {
        return criarNoABB(valor);
    }
    
    if (valor < raiz->dado) {
        raiz->esquerda = inserirABB(raiz->esquerda, valor);
    } else if (valor > raiz->dado) {
        raiz->direita = inserirABB(raiz->direita, valor);
    }
    
    return raiz;
}

NoABB* removerABB(NoABB* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }
    
    if (chave < raiz->dado) {
        raiz->esquerda = removerABB(raiz->esquerda, chave);
    } else if (chave > raiz->dado) {
        raiz->direita = removerABB(raiz->direita, chave);
    } else {
        if (raiz->esquerda == NULL) {
            NoABB* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoABB* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        NoABB* temp = encontrarMinimoABB(raiz->direita);
        raiz->dado = temp->dado;
        raiz->direita = removerABB(raiz->direita, temp->dado);
    }
    
    return raiz;
}

NoABB* encontrarMinimoABB(NoABB* no) {
    NoABB* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

void liberarArvoreABB(NoABB* raiz) {
    if (raiz != NULL) {
        liberarArvoreABB(raiz->esquerda);
        liberarArvoreABB(raiz->direita);
        free(raiz);
    }
}

void preOrdemABB(NoABB* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        preOrdemABB(raiz->esquerda);
        preOrdemABB(raiz->direita);
    }
}

void inOrdemABB(NoABB* raiz) {
    if (raiz != NULL) {
        inOrdemABB(raiz->esquerda);
        printf("%d ", raiz->dado);
        inOrdemABB(raiz->direita);
    }
}

void posOrdemABB(NoABB* raiz) {
    if (raiz != NULL) {
        posOrdemABB(raiz->esquerda);
        posOrdemABB(raiz->direita);
        printf("%d ", raiz->dado);
    }
}

int buscarABB(NoABB* raiz, int valor, int* contador) {
    (*contador)++;
    if (raiz == NULL) {
        return 0;
    }
    
    if (valor == raiz->dado) {
        return 1;
    } else if (valor < raiz->dado) {
        return buscarABB(raiz->esquerda, valor, contador);
    } else {
        return buscarABB(raiz->direita, valor, contador);
    }
}

// Implementação das funções para AVL
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

int alturaAVL(NoAVL* no) {
    return no ? no->altura : 0;
}

int max_value(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(NoAVL* no) {
    return no ? alturaAVL(no->esquerda) - alturaAVL(no->direita) : 0;
}

NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max_value(alturaAVL(y->esquerda), alturaAVL(y->direita)) + 1;
    x->altura = max_value(alturaAVL(x->esquerda), alturaAVL(x->direita)) + 1;

    return x;
}

NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max_value(alturaAVL(x->esquerda), alturaAVL(x->direita)) + 1;
    y->altura = max_value(alturaAVL(y->esquerda), alturaAVL(y->direita)) + 1;

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

    no->altura = 1 + max_value(alturaAVL(no->esquerda), alturaAVL(no->direita));
    return balancear(no);
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

    raiz->altura = 1 + max_value(alturaAVL(raiz->esquerda), alturaAVL(raiz->direita));
    return balancear(raiz);
}

NoAVL* encontrarMinAVL(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
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

int buscarAVL(NoAVL* raiz, int valor, int* contador) {
    (*contador)++;
    if (raiz == NULL) {
        return 0;
    }
    
    if (valor == raiz->dado) {
        return 1;
    } else if (valor < raiz->dado) {
        return buscarAVL(raiz->esquerda, valor, contador);
    } else {
        return buscarAVL(raiz->direita, valor, contador);
    }
}

// Função auxiliar para imprimir resultados de busca
void imprimirResultadoBusca(int encontrado, int contador) {
    if (encontrado) {
        printf("Elemento encontrado! Operacoes realizadas: %d\n", contador);
    } else {
        printf("Elemento nao encontrado. Operacoes realizadas: %d\n", contador);
    }
}