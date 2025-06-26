#include <stdio.h>

#define MAXN 100
int arr[MAXN];         // Array original
int tree[4 * MAXN];    // Árvore de Segmentos
int lazy[4 * MAXN];    // Array Lazy

// Função para construir a árvore
void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid);
        build(2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Propagar atualizações pendentes (Lazy)
void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {// Verifica se tem atualização pendente
        // Aplica o valor pendente ao nó atual
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end) {
            // Propaga para os filhos
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
        lazy[node] = 0; // Limpa o valor lazy
    }
}

// Atualização de intervalo [l, r] somando val
void update_range(int node, int start, int end, int l, int r, int val) {
    push_down(node, start, end); // Garante que não há atualização pendente

    if (r < start || end < l) return; // Fora do intervalo

    if (l <= start && end <= r) {
        lazy[node] += val;
        push_down(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_range(2 * node + 1, start, mid, l, r, val);
    update_range(2 * node + 2, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Consulta de soma no intervalo [l, r]
int query_range(int node, int start, int end, int l, int r) {
    push_down(node, start, end); // Garante que os valores estão atualizados

    if (r < start || end < l) return 0; // Fora do intervalo

    if (l <= start && end <= r) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    int left_sum = query_range(2 * node, start, mid, l, r);
    int right_sum = query_range(2 * node + 1, mid + 1, end, l, r);
    return left_sum + right_sum;
}

int main() {
    int n = 6;

    // Inicializa o array de entrada
    int input[] = {1, 3, 5, 2, 4, 6};
    for (int i = 0; i < n; i++) {
        arr[i] = input[i];
    }

    // Construção da árvore
    build(0, 0, n - 1);

    // Consulta inicial [1, 3]
    printf("Soma de [1, 3] = %d\n", query_range(1, 0, n - 1, 1, 3)); // Esperado: 3 + 5 + 2 = 10

    // Atualiza intervalo [1, 4] somando 2
    update_range(1, 0, n - 1, 1, 4, 2);

    // Consulta após atualização [1, 3]
    printf("Soma de [1, 3] após update = %d\n", query_range(1, 0, n - 1, 1, 3)); // Esperado: 5 + 7 + 4 = 16

    // Consulta total [0, 5]
    printf("Soma total [0, 5] = %d\n", query_range(1, 0, n - 1, 0, 5)); // Esperado: 1 + 5 + 7 + 4 + 6 + 6 = 29

    return 0;
}
