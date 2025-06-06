/*Nome: Leonardo Vinícius Lima Castro
Matrícula: 2022009946*/
#include <stdio.h> // Para entrada e saída (printf)
#include <stdlib.h> // Para funções gerais (como malloc, se necessário, mas não neste exemplo)

#define MAX_TAM 100 //Tive qey implementar pois tava com probleam na inserção já que acessava espaços não alocados

// --- Funções Auxiliares Comuns ---
void trocar(int *a, int *b);
int obterPai(int i);
int obterFilhoEsquerdo(int i);
int obterFilhoDireito(int i);
void imprimirVetor(int arr[], int n, const char *mensagem);

// --- Implementação para HEAP MÁXIMA ---
void maxHeapificarParaBaixo(int arr[], int tamanho, int idx);
void construirMaxHeap(int arr[], int tamanho);
void minHeapificarParaBaixo(int arr[], int tamanho, int idx);
void construirMinHeap(int arr[], int tamanho);

//Cabeçalho dos desafios
void maxHeapificarParaCima(int arr[], int i);
void inserirMaxHeap(int arr[], int *tamanho, int valor);
void minHeapificarParaCima(int arr[], int i);
void inserirMinHeap(int arr[], int *tamanho, int valor);
int extrairMaxHeap(int arr[], int *tamanho);
int extrairMinHeap(int arr[], int *tamanho);
void heapSort(int arr[], int tamanho);

// --- Função Principal (Main) para Teste ---
int main() {
    // Exemplo para Heap Máxima
    int vetor_max[MAX_TAM] = {4, 10, 3, 5, 1, 8, 12};
    int tamanho_max = 7;

    imprimirVetor(vetor_max, tamanho_max, "Vetor Original (para Max Heap)");
    construirMaxHeap(vetor_max, tamanho_max);
    imprimirVetor(vetor_max, tamanho_max, "Max Heap Construida");

    printf("\n"); // Adiciona uma linha em branco para melhor visualização

    // Exemplo para Heap Mínima
    int vetor_min[MAX_TAM] = {4, 10, 3, 5, 1, 8, 12};
    int tamanho_min = 7;

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

    printf("\n"); // Adiciona uma linha em branco para melhor visualização

    //Teste do desafio 2
    //Remoção dos elementos - 2 de cada
    printf("Elemento removido: %d\n", extrairMaxHeap(vetor_max, &tamanho_max));
    imprimirVetor(vetor_max, tamanho_max, "Max Heap com remocao de 1 dos elementos");
    printf("Elemento removido: %d\n", extrairMaxHeap(vetor_max, &tamanho_max));
    imprimirVetor(vetor_max, tamanho_max, "Max Heap com remocao de 2 dos elementos");

    printf("Elemento removido: %d\n", extrairMinHeap(vetor_min, &tamanho_min));
    imprimirVetor(vetor_min, tamanho_min, "Min Heap com remocao de 1 dos elementos");
    printf("Elemento removido: %d\n", extrairMinHeap(vetor_min, &tamanho_min));
    imprimirVetor(vetor_min, tamanho_min, "Min Heap com remocao de 2 dos elementos");

    printf("\n"); // Adiciona uma linha em branco para melhor visualização

    //Teste do desafio 3
    int vetor[] = {7, 2, 9, 1, 5, 3, 8, 4, 6};
    int tamanho = sizeof(vetor)/sizeof(vetor[0]);
    imprimirVetor(vetor, tamanho, "Vetor Original");

    heapSort(vetor, tamanho);
    imprimirVetor(vetor, tamanho, "Vetor Ordenado");

    return 0; // Indica que o programa terminou com sucesso
}

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

// Função para construir uma heap máxima a partir de um vetor desordenado.
// Ela itera de trás para frente, aplicando maxHeapificarParaBaixo nos nós não-folha.
void construirMaxHeap(int arr[], int tamanho) {
    // Começa do último nó não-folha e vai até a raiz (índice 0)
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        maxHeapificarParaBaixo(arr, tamanho, i);
    }
}
// --- Implementação para HEAP MÍNIMA ---


// Função para construir uma heap mínima a partir de um vetor desordenado.
// Ela itera de trás para frente, aplicando minHeapificarParaBaixo nos nós não-folha.
void construirMinHeap(int arr[], int tamanho) {
    // Começa do último nó não-folha e vai até a raiz (índice 0)
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        minHeapificarParaBaixo(arr, tamanho, i);
    }
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

//Desafio 2: Extração de Elemento (Remoção da Raiz) em Heap (Max e Min)

int extrairMaxHeap(int arr[], int *tamanho){
    if(*tamanho == 0){//Verifica se tá vazio o vetor
        return -1;
    }
    int valor_raiz = arr[0]; //Salva o valor da raiz
    arr[0] = arr[*tamanho - 1]; //O último elemento vai para raiz
    (*tamanho)--;//Como ouve a remoção do elemento, então diminui o tamanho do vetor
    maxHeapificarParaBaixo(arr, *tamanho, 0);//Vai realizar a correção das posições a partir da raiz, já que último elemento foi para raiz
    return valor_raiz; //Retorna o elemento da raiz
}

int extrairMinHeap(int arr[], int *tamanho){
    if(*tamanho == 0){//Verifica se tá vazio o vetor
        return -1;
    }
    int valor_raiz = arr[0]; //Salva o valor da raiz
    arr[0] = arr[*tamanho - 1]; //O último elemento vai para raiz
    (*tamanho)--;//Diminui o tamanho do vetor por conta remoção do elemento da raiz
    minHeapificarParaBaixo(arr, *tamanho, 0);//Vai realizar a correção das posições a partir da raiz, já que último elemento foi para raiz
    return valor_raiz; //Retorna o elemento retirado
}

//Desafio 3: Implementando Heap Sort (Ordenação com Heap)  
void heapSort(int arr[], int tamanho){
    construirMaxHeap(arr, tamanho); //Faz construção do Max Heap
    for (int i = tamanho - 1; i >= 1; i--) {
        trocar(&arr[0], &arr[i]); //Troca a raiz, que é o maior elemento com último ainda não ordenado
        maxHeapificarParaBaixo(arr, i, 0); //Aplica o Max Heap em cada subarray não ordenado
    }
}
//Desafio 4 (Opcional - Mais Avançado): Heap Genérica ou Heapify Melhorado

//2. heapify Iterativo (Sem Recursão):
void maxHeapificarParaBaixo(int arr[], int tamanho, int idx) {
    int maior, filhoEsquerdo, filhoDireito;//Declaro as variaveis pois elas vão ser utilizadas e modificadas no loop
    while (1){//Vai rodar até ter as propriedades serem satisfeitas
        maior = idx; // Assumimos que a raiz atual é o maior
        filhoEsquerdo = obterFilhoEsquerdo(idx);
        filhoDireito = obterFilhoDireito(idx);

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
            idx = maior; //Como ouve a troca com o filho, o indice vai para o filho, onde no loop vaio comparar com os seus filhos se tiver 
        } else{
            break; //Quando não tem mais comparações finaliza a processo e processo foi concluído, pois aqui o maior vai continuar sendo o índide atual
        }
    }
}

void minHeapificarParaBaixo(int arr[], int tamanho, int idx) {
    int menor, filhoEsquerdo, filhoDireito;
    while(1){//Vai rodar até ter as propriedades serem satisfeitas
        menor = idx; // Assumimos que a raiz atual é o menor
        filhoEsquerdo = obterFilhoEsquerdo(idx);
        filhoDireito = obterFilhoDireito(idx);
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
            idx = menor;//Depois da troca ser realizadas vamos partir do nó que o valor foi trocado
        }else {
            break; //Não tem mais trocas para realizar e finaliza o processo;
        }
    }

}