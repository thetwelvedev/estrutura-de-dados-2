#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --- Função de Hash por Divisão ---
int calcularHashDivisao(int chave, int tamanhoTabela) {
    if (tamanhoTabela <= 0) {
        return -1; // Tamanho inválido
    }
    
    int hash_valor = chave % tamanhoTabela;
    
    // Garante que o hash seja positivo
    if (hash_valor < 0) {
        hash_valor += tamanhoTabela;
    }
    
    return hash_valor;
}

// --- Função de Hash por Multiplicação ---
#define A_CONSTANTE 0.6180339887 // Constante recomendada (fracionária do número áureo)

int calcularHashMultiplicacao(int chave, int tamanhoTabela) {
    if (tamanhoTabela <= 0) {
        return -1; // Tamanho inválido
    }

    double kA = (double)chave * A_CONSTANTE;
    double parteFracionaria = kA - floor(kA); // Pega a parte fracionária
    double resultadoMultiplicacao = parteFracionaria * tamanhoTabela;
    
    int hash_valor = (int)floor(resultadoMultiplicacao);
    
    return hash_valor;
}

// --- Função de Hash por Manipulação de Bits ---
int calcularHashBits(int chave, int tamanhoTabela) {
    if (tamanhoTabela <= 0) {
        return -1; // Tamanho inválido
    }

    // Mistura os bits da chave usando XOR e shifts
    chave = (chave >> 16) ^ chave;
    chave = chave * 0x85ebca6b; // Número primo grande
    chave = chave ^ (chave >> 13);
    chave = chave * 0xc2b2ae35; // Outro número primo grande
    chave = chave ^ (chave >> 16);

    // Garante que o valor esteja dentro do tamanho da tabela
    int hash_valor = chave % tamanhoTabela;
    if (hash_valor < 0) {
        hash_valor += tamanhoTabela;
    }

    return hash_valor;
}

// --- Função Principal (main) ---
int main() {
    int chaves[] = {42, 17, 99, 123, 7, 256}; // Array de 6 números
    int tamanhoTabela = 7; // Tamanho da tabela hash

    printf("=== Tabela Hash (Tamanho %d) ===\n", tamanhoTabela);
    printf("| Valor | Divisão | Multiplicação | Bits    |\n");
    printf("|-------|---------|---------------|---------|\n");

    for (int i = 0; i < 6; i++) {
        int chave = chaves[i];
        int hashDivisao = calcularHashDivisao(chave, tamanhoTabela);
        int hashMultiplicacao = calcularHashMultiplicacao(chave, tamanhoTabela);
        int hashBits = calcularHashBits(chave, tamanhoTabela);

        printf("| %-5d | %-7d | %-13d | %-7d |\n", 
               chave, hashDivisao, hashMultiplicacao, hashBits);
    }

    return 0;
}