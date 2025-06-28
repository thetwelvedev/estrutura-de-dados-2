#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int data;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode* root = NULL;

RBNode* create_node(int data) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

// Rotação à esquerda
void rotate_left(RBNode** root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Rotação à direita
void rotate_right(RBNode** root, RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Corrigir após inserção
void fix_insert(RBNode** root, RBNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_right(root, z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_left(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Inserção na árvore Rubro-Negra
void rb_insert(int data) {
    RBNode* z = create_node(data);
    RBNode* y = NULL;
    RBNode* x = root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (!y)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else y->right = z;

    fix_insert(&root, z);
}
void preorder(RBNode* node) {
    if (node) {
        printf("%d (%s)\n", node->data, node->color == RED ? "RED" : "BLACK");
        preorder(node->left);
        preorder(node->right);
    }
}

int main() {
    int valores[] = {20, 15, 25, 10, 5, 1, 30, 40};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        rb_insert(valores[i]);
    }

    printf("Pré-ordem da Árvore Rubro-Negra:\n");
    preorder(root);

    return 0;
}
