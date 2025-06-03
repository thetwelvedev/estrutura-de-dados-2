/*Nome: Leonardo Vinícius Lima Castro
Matrícula: 2022009946*/
#include <stdio.h> // Para entrada e saída (printf)
#include <stdlib.h> // Para funções gerais (como malloc, se necessário, mas não neste exemplo)

// --- Funções Auxiliares Comuns ---

// Troca os valores de duas variáveis inteiras
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Retorna o índice do nó pai para um array 0-indexado
int obterPai(int i) {
    return (i - 1) / 2;
}

// Retorna o índice do filho esquerdo para um array 0-indexado
int obterFilhoEsquerdo(int i) {
    return 2 * i + 1;
}

// Retorna o índice do filho direito para um array 0-indexado
int obterFilhoDireito(int i) {
    return 2 * i + 2;
}

// Função para imprimir o vetor (para visualização)
void imprimirVetor(int arr[], int n, const char *mensagem) {
    printf("%s: [", mensagem);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// --- Implementação para HEAP MÁXIMA ---

// Função para "heapificar" uma subárvore para manter a propriedade de heap máxima.
// Ela garante que o nó no índice 'idx' e seus descendentes formem uma max-heap.
void maxHeapificarParaBaixo(int arr[], int tamanho, int idx) {
    int maior = idx; // Assumimos que a raiz atual é o maior
    int filhoEsquerdo = obterFilhoEsquerdo(idx);
    int filhoDireito = obterFilhoDireito(idx);

    // Se o filho esquerdo existe e é maior que o "maior" atual
    if (filhoEsquerdo < tamanho && arr[filhoEsquerdo] > arr[maior]) {
        maior = filhoEsquerdo;
    }

    // Se o filho direito existe e é maior que o "maior" atual (incluindo o filho esquerdo, se for o caso)
    if (filhoDireito < tamanho && arr[filhoDireito] > arr[maior]) {
        maior = filhoDireito;
    }

    // Se o "maior" não é a raiz atual (significa que um filho é maior)
    if (maior != idx) {
        trocar(&arr[idx], &arr[maior]); // Troca o pai com o maior filho
        // Chama recursivamente para a subárvore afetada para manter a propriedade
        maxHeapificarParaBaixo(arr, tamanho, maior);
    }
}

// Função para construir uma heap máxima a partir de um vetor desordenado.
// Ela itera de trás para frente, aplicando maxHeapificarParaBaixo nos nós não-folha.
void construirMaxHeap(int arr[], int tamanho) {
    // Começa do último nó não-folha e vai até a raiz (índice 0)
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        maxHeapificarParaBaixo(arr, tamanho, i);
    }
}
// --- Implementação para HEAP MÍNIMA ---

// Função para "heapificar" uma subárvore para manter a propriedade de heap mínima.
// Ela garante que o nó no índice 'idx' e seus descendentes formem uma min-heap.
void minHeapificarParaBaixo(int arr[], int tamanho, int idx) {
    int menor = idx; // Assumimos que a raiz atual é o menor
    int filhoEsquerdo = obterFilhoEsquerdo(idx);
    int filhoDireito = obterFilhoDireito(idx);

    // Se o filho esquerdo existe e é menor que o "menor" atual
    if (filhoEsquerdo < tamanho && arr[filhoEsquerdo] < arr[menor]) {
        menor = filhoEsquerdo;
    }

    // Se o filho direito existe e é menor que o "menor" atual (incluindo o filho esquerdo, se for o caso)
    if (filhoDireito < tamanho && arr[filhoDireito] < arr[menor]) {
        menor = filhoDireito;
    }

    // Se o "menor" não é a raiz atual (significa que um filho é menor)
    if (menor != idx) {
        trocar(&arr[idx], &arr[menor]); // Troca o pai com o menor filho
        // Chama recursivamente para a subárvore afetada para manter a propriedade
        minHeapificarParaBaixo(arr, tamanho, menor);
    }
}

// Função para construir uma heap mínima a partir de um vetor desordenado.
// Ela itera de trás para frente, aplicando minHeapificarParaBaixo nos nós não-folha.
void construirMinHeap(int arr[], int tamanho) {
    // Começa do último nó não-folha e vai até a raiz (índice 0)
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        minHeapificarParaBaixo(arr, tamanho, i);
    }
}

//Cabeçalho dos desafios
void maxHeapificarParaCima(int arr[], int i);
void inserirMaxHeap(int arr[], int *tamanho, int valor);
void minHeapificarParaCima(int arr[], int i);
void inserirMinHeap(int arr[], int *tamanho, int valor);

// --- Função Principal (Main) para Teste ---
int main() {
    // Exemplo para Heap Máxima
    int vetor_max[] = {4, 10, 3, 5, 1, 8, 12};
    int tamanho_max = sizeof(vetor_max) / sizeof(vetor_max[0]);

    imprimirVetor(vetor_max, tamanho_max, "Vetor Original (para Max Heap)");
    construirMaxHeap(vetor_max, tamanho_max);
    imprimirVetor(vetor_max, tamanho_max, "Max Heap Construida");

    printf("\n"); // Adiciona uma linha em branco para melhor visualização

    // Exemplo para Heap Mínima
    int vetor_min[] = {4, 10, 3, 5, 1, 8, 12};
    int tamanho_min = sizeof(vetor_min) / sizeof(vetor_min[0]);

    imprimirVetor(vetor_min, tamanho_min, "Vetor Original (para Min Heap)");
    construirMinHeap(vetor_min, tamanho_min);
    imprimirVetor(vetor_min, tamanho_min, "Min Heap Construida");

    printf("\n"); // Adiciona uma linha em branco para melhor visualização

    //Teste do desafio 1
    //Maxheap -> elementos 14, 30, 17
    inserirMaxHeap(vetor_max, &tamanho_max, 14);
    inserirMaxHeap(vetor_max, &tamanho_max, 30);
    inserirMaxHeap(vetor_max, &tamanho_max, 17);
    imprimirVetor(vetor_max, tamanho_max, "Max Heap com insercao dos elementos 14, 30, 17");

    //Minheap -> elementos 7, 32, 13
    inserirMinHeap(vetor_min, &tamanho_min, 7);
    inserirMinHeap(vetor_min, &tamanho_min, 32);
    inserirMinHeap(vetor_min, &tamanho_min, 13);
    imprimirVetor(vetor_min, tamanho_min, "Min Heap com insercao dos elementos 7, 32, 13");

    return 0; // Indica que o programa terminou com sucesso
}

//Desafio 1: Inserção de Elemento em Heap (Max e Min)
void maxHeapificarParaCima(int arr[], int i){
    if(i == 0){
        return; //caso for raiz não precisa continuar 
    }
    if(arr[i] > arr[obterPai(i)]){ //Aqui ele compara com o pai
        trocar(&arr[i], &arr[obterPai(i)]); //Efetua a troca
        maxHeapificarParaCima(arr, obterPai(i));//Continua recursivamente com pai por conta da troca de posição
    }
}

void inserirMaxHeap(int arr[], int *tamanho, int valor){
    (*tamanho)++; //Incrementa pois ao adicionar um novo elemento o vetor aumenta
    int novo_index = *tamanho - 1; //Como o tamanho começa do 1 e index do 0, tem colocar o -1
    arr[novo_index] = valor; //Aqui é atribuido um valor já com nova posição do array
    maxHeapificarParaCima(arr, novo_index); //Aplica essa função para posicinar corretamente no array
}

void minHeapificarParaCima(int arr[], int i){
    if(i == 0){
        return; //caso for raiz não precisa continuar 
    }
    if(arr[i] < arr[obterPai(i)]){//Comparo se o filho menor que o pai
        trocar(&arr[i], &arr[obterPai(i)]);//faz troca passando os endereços
        minHeapificarParaCima(arr, obterPai(i));//Chama recursivamente
    }
}

void inserirMinHeap(int arr[], int *tamanho, int valor){
    (*tamanho)++;//Atualizo o tamanho do vetor pois vou adicionar um novo elemento
    int novo_index = *tamanho - 1; //Aqui faço a atribuição do tamanho a essa variável que vai armazenar o valor do meu indice novo
    arr[novo_index] = valor;//Armazeno o valor na variável
    minHeapificarParaCima(arr, novo_index);//Chamo função para arrumar a posição dos elementos
}