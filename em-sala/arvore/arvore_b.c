#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Grau mínimo (mínimo 2)

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode* children[2 * T];
    int n;
    bool leaf;
} BTreeNode;

BTreeNode* create_node(bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    return node;
}

// Busca uma chave na árvore
void btree_search(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) i++;

    if (i < root->n && k == root->keys[i]) {
        printf("Chave %d encontrada.\n", k);
        return;
    }

    if (root->leaf) {
        printf("Chave %d não encontrada.\n", k);
        return;
    }

    btree_search(root->children[i], k);
}

// Divide um filho
void split_child(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = create_node(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->leaf)
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];

    y->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

// Insere uma chave em nó não cheio
void insert_non_full(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i]) i--;
        i++;
        if (x->children[i]->n == 2 * T - 1) {
            split_child(x, i, x->children[i]);
            if (k > x->keys[i]) i++;
        }
        insert_non_full(x->children[i], k);
    }
}

// Insere na árvore B
BTreeNode* btree_insert(BTreeNode* root, int k) {
    if (root->n == 2 * T - 1) {
        BTreeNode* s = create_node(false);
        s->children[0] = root;
        split_child(s, 0, root);
        insert_non_full(s, k);
        return s;
    } else {
        insert_non_full(root, k);
        return root;
    }
}
int main() {
    BTreeNode* root = create_node(true);  // Árvore B começa vazia

    int valores[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        root = btree_insert(root, valores[i]);
    }

    printf("Buscando chave 6:\n");
    btree_search(root, 6); // Deve encontrar

    printf("Buscando chave 99:\n");
    btree_search(root, 99); // Não deve encontrar

    return 0;
}
