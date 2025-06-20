#include <stdio.h>
//Funções - swap, getFather, GetLeftChild, GetRightChild, printVector
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getFather(int idx){
    return (idx - 1) / 2;
}

int GetLeftChild(int idx){
    return 2 * idx + 1;
}

int GetRightChild(int idx){
    return 2 * idx + 2;
}

void printVector(int arr[], int n, const char *message) {
    printf("%s: [", message);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
//Funções - MaxHeapifyUp, MinHeapifyUp, insertMaxHeap, insertMinHeap
void maxHeapifyUp(int arr[], int idx){
    if(idx == 0){ // Está na raiz não tem mais o que comparar
        return;
    }
    if(arr[idx] > arr[getFather(idx)]){//Haverá troca caso o filho seja maior que o pai
        swap(&arr[idx], &arr[getFather(idx)]);
        maxHeapifyUp(arr, getFather(idx));
    }
}

void MinHeapifyUp(int arr[], int idx){
    if(idx == 0){ // Está na raiz não tem mais o que comparar
        return;
    }
    if(arr[idx] < arr[getFather(idx)]){//Haverá troca caso o filho seja maior que o pai
        swap(&arr[idx], &arr[getFather(idx)]);
        MinHeapifyUp(arr, getFather(idx));
    }
}

void insertMaxHeap(int arr[], int *lenght, int value){
    (*lenght)++; //Aumenta o tamanho do vetor
    int new_idx = *lenght - 1;
    arr[new_idx] = value;
    maxHeapifyUp(arr, new_idx);
}

void insertMinHeap(int arr[], int *lenght, int value){
    (*lenght)++; //Aumenta o tamanho do vetor
    int new_idx = *lenght - 1;
    arr[new_idx] = value;
    minHeapifyUp(arr, new_idx);
}

//Funções - MaxHeapifyDown, MinHeapifyDown, buildMaxHeap, buildMinHeap, removeMaxHeap, removeMinHeap
void MaxHeapifyDown(int arr[], int lenght, int idx){
    int max = idx;
    int leftChild = GetLeftChild(idx);
    int rightChild = GetRightChild(idx);
    if(leftChild < lenght && arr[leftChild] > arr[max]){// Se tá dentro do escopo do array e se filho e maior que pai
        max = leftChild;
    }

    if(rightChild < lenght && arr[rightChild] > arr[max]){
        max = rightChild;
    }
    if(idx != max){ //Siginifica que houve a troca
        swap(&arr[idx], &arr[max]); //Faz a troca real
        MaxHeapifyDown(arr, lenght, max); //Como o max atualmente é a posição do filho então continua a partir de vai recusivamente
    }
}

void minHeapifyDown(int arr[], int lenght, int idx){
    int min = idx;
    int leftChild = GetLeftChild(idx);
    int rightChild = GetRightChild(idx);
    if(leftChild < lenght && arr[leftChild] < arr[min]){// Se tá dentro do escopo do array e se filho e maior que pai
        min = leftChild;
    }

    if(rightChild < lenght && arr[rightChild] < arr[min]){
        min = rightChild;
    }
    if(idx != min){ //Siginifica que houve a troca
        swap(&arr[idx], &arr[min]); //Faz a troca real
        minHeapifyDown(arr, lenght, min); //Como o min atualmente é a posição do filho então continua a partir de vai recusivamente
    }
}

void buildMaxHeap(int arr[], int length){
    for(int i = (length/2) - 1; i >= 0; i--){ //Começa do meio do array , do último nó não-folha e vai até a raiz
        MaxHeapifyDown(arr, length, i);
    }
}

void buildMinHeap(int arr[], int length){
    for(int i = (length/2) - 1; i >= 0; i--){ //Começa do meio do array , do último nó não-folha e vai até a raiz
        MinHeapifyDown(arr, length, i);
    }
}

int removeMaxHeap(int arr[], int *length){
    if(*length == 0){//Verifica se tá vazio o vetor
        return -1;
    }
    int root_value = arr[0]; //Salvar o valor para remover
    arr[0] = arr[*length - 1];//Trocar o valor do último com o removido para fazer reordenação
    (*length)--; //Diminuir o tamanho do array
    MaxHeapifyDown(arr, *length, 0);//Vai reordenar a partir da raiz
    return  root_value;
}

int removeMinHeap(int arr[], int *length){
    if(*length == 0){//Verifica se tá vazio o vetor
        return -1;
    }
    int root_value = arr[0]; //Salvar o valor para remover
    arr[0] = arr[*length - 1];//Trocar o valor do último com o removido para fazer reordenação
    (*length)--; //Diminuir o tamanho do array
    MinHeapifyDown(arr, *length, 0);//Vai reordenar a partir da raiz
    return  root_value;
}

//Funções - heapSort
void heapSort(int arr[], int length){
    buildMaxHeap(arr, length); //Faz construção do Max Heap
    for (int i = length - 1; i >= 1; i--) {
        swap(&arr[0], &arr[i]); //Troca a raiz, que é o maior elemento com último ainda não ordenado
        MaxHeapifyDown(arr, i, 0); //Aplica o Max Heap em cada subarray não ordenado
    }
}

int main(){

}

