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

//Funções - MaxHeapifyUp, MinHeapifyUp, removeMaxHeap, removeMinHeap
//Funções - MaxHeapifyDown, MinHeapifyDown, buildMaxHeap, buildMinHeap, insertMaxHeap, insertMinHeap
//Funções - heapSort

int main(){

}

