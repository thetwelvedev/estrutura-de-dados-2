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
        return -1;
    }
    if(arr[idx] > arr[getFather(idx)]){//Haverá troca caso o filho seja maior que o pai
        swap(&arr[idx], arr[getFather(idx)]);
        maxHeapifyUp(arr, arr[getFather(idx)]);
    }
}

void MinHeapifyUp(int arr[], int idx){
    if(idx == 0){ // Está na raiz não tem mais o que comparar
        return -1;
    }
    if(arr[idx] < arr[getFather(idx)]){//Haverá troca caso o filho seja maior que o pai
        swap(&arr[idx], arr[getFather(idx)]);
        MinHeapifyUp(arr, arr[getFather(idx)]);
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

//Funções - MaxHeapifyDown, MinHeapifyDown, buildMaxHeap, buildMinHeap,removeMaxHeap, removeMinHeap
//Funções - heapSort

int main(){

}

