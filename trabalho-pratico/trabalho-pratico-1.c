/*Algoritmo para Construção de Árvore Binária a partir de Expressões Aritméticas
- Analisar Expressão: Ler a expressão aritmética e identificar números, operadores e parênteses.
- Construir Árvore: Organizar a árvore respeitando a precedência matemática.
- Implementar Percurso: Garantir que a avaliação da expressão seja correta ao percorrer a árvore.
O algoritmo deve reconhecer como a precedência de operações modifica a estrutura da árvore. Por exemplo:
• A expressão 2 * 4 + 3resultará em uma estrutura arbórea que reflete a multiplicação sendo avaliada antes da adição.
• A expressão 2 * (4 + 3)produzirá uma árvore onde a adição dentro dos parênteses é priorizada na estrutura.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct NoDinamico {
    char dado;
    struct NoDinamico *esquerda;
    struct NoDinamico *direita;
} NoDinamico;

NoDinamico* criarNoDinamico(char valor);
void liberarArvoreDinamico(NoDinamico* raiz);
void imprimirArvoreFormatada(NoDinamico* raiz);
NoDinamico* construirArvoreExpressao(const char* expressao, int inicio, int fim);
int alturaArvore(NoDinamico* raiz);
void preencherMatrizEConexoes(char** matriz, NoDinamico* no, int nivel, int pos, int espacamento, int altura);

int main(void) {
    char expressao[100];
    
    printf("Digite a expressao matematica (ex: (6-1)/(4+2)): ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = '\0';
    
    NoDinamico* raiz = construirArvoreExpressao(expressao, 0, strlen(expressao) - 1);
    
    printf("\nArvore da expressao:\n");
    imprimirArvoreFormatada(raiz);
    
    liberarArvoreDinamico(raiz);
    return 0;
}

NoDinamico* criarNoDinamico(char valor) {
    NoDinamico* novoNo = (NoDinamico*)malloc(sizeof(NoDinamico));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

void liberarArvoreDinamico(NoDinamico* raiz) {
    if (raiz != NULL) {
        liberarArvoreDinamico(raiz->esquerda);
        liberarArvoreDinamico(raiz->direita);
        free(raiz);
    }
}

int alturaArvore(NoDinamico* raiz) {
    if (raiz == NULL) return 0;
    int alturaEsq = alturaArvore(raiz->esquerda);
    int alturaDir = alturaArvore(raiz->direita);
    return (alturaEsq > alturaDir) ? alturaEsq + 1 : alturaDir + 1;
}

void preencherConexoes(char** matriz, int linha, int posPai, int posFilho, char conexao) {
    int passo = posFilho > posPai ? 1 : -1;
    for (int i = posPai + passo; i != posFilho; i += passo) {
        matriz[linha][i] = conexao;
    }
}

void preencherMatrizEConexoes(char** matriz, NoDinamico* no, int nivel, int pos, int espacamento, int altura) {
    if (no == NULL) return;

    int linhaNo = nivel * 2;
    matriz[linhaNo][pos] = no->dado;

    if (no->esquerda != NULL) {
        int posEsq = pos - espacamento;
        matriz[linhaNo + 1][pos - espacamento/2] = '/';
        preencherMatrizEConexoes(matriz, no->esquerda, nivel + 1, posEsq, espacamento/2, altura);
    }
    
    if (no->direita != NULL) {
        int posDir = pos + espacamento;
        matriz[linhaNo + 1][pos + espacamento/2] = '\\';
        preencherMatrizEConexoes(matriz, no->direita, nivel + 1, posDir, espacamento/2, altura);
    }
}

void imprimirArvoreFormatada(NoDinamico* raiz) {
    if (raiz == NULL) return;

    int h = alturaArvore(raiz);
    int linhas = h * 2 - 1;
    int colunas = (1 << h) * 2 - 1;

    char** matriz = (char**)malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (char*)malloc(colunas * sizeof(char));
        memset(matriz[i], ' ', colunas);
    }

    preencherMatrizEConexoes(matriz, raiz, 0, colunas / 2, (colunas + 1) / 4, h);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
        free(matriz[i]);
    }
    free(matriz);
}

int encontrarOperador(const char* expressao, int inicio, int fim) {
    int parenteses = 0;
    int posOperador = -1;
    int menorPrecedencia = 4;

    for (int i = fim; i >= inicio; i--) {
        char c = expressao[i];
        if (c == ')') parenteses++;
        else if (c == '(') parenteses--;
        else if (parenteses == 0) {
            int precedencia;
            if (c == '+' || c == '-') precedencia = 2;
            else if (c == '*' || c == '/') precedencia = 3;
            else continue;

            if (precedencia < menorPrecedencia) {
                menorPrecedencia = precedencia;
                posOperador = i;
            }
        }
    }
    return posOperador;
}

NoDinamico* construirArvoreExpressao(const char* expressao, int inicio, int fim) {
    while (inicio <= fim) {
        if (expressao[inicio] == '(' && expressao[fim] == ')') {
            int parenteses = 1;
            int i;
            for (i = inicio + 1; i <= fim; i++) {
                if (expressao[i] == '(') parenteses++;
                else if (expressao[i] == ')') parenteses--;
                if (parenteses == 0) break;
            }
            if (i == fim) {
                inicio++;
                fim--;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    int pos = encontrarOperador(expressao, inicio, fim);
    if (pos != -1) {
        NoDinamico* no = criarNoDinamico(expressao[pos]);
        no->esquerda = construirArvoreExpressao(expressao, inicio, pos - 1);
        no->direita = construirArvoreExpressao(expressao, pos + 1, fim);
        return no;
    }

    return criarNoDinamico(expressao[inicio]);
}