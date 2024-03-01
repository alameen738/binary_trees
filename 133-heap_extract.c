#include <stdlib.h>

typedef struct heap_node {
    int data;
    struct heap_node *left;
    struct heap_node *right;
} heap_t;

int height(heap_t *root) {
    if (root == NULL)
        return 0;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(heap_t **root) {
    heap_t *current = *root;
    heap_t *largest = current;
    
    while (current != NULL) {
        largest = current;
        
        if (current->left != NULL && current->left->data > largest->data) {
            largest = current->left;
        }
        
        if (current->right != NULL && current->right->data > largest->data) {
            largest = current->right;
        }
        
        if (largest != current) {
            swap(&(current->data), &(largest->data));
            current = largest;
        } else {
            break;
        }
    }
}

int heap_extract(heap_t **root) {
    if (*root == NULL)
        return 0;

    int extracted_value = (*root)->data;

    int h = height(*root);
    int last_level_order_index = (1 << (h - 1)) - 1;
    heap_t *last_node = *root;

    for (int i = 0; i < last_level_order_index; i++) {
        if (last_node->left != NULL) {
            last_node = last_node->left;
        } else {
            last_node = last_node->right;
        }
    }

    swap(&((*root)->data), &(last_node->data));
    free(last_node);

    heapify_down(root);

    return extracted_value;
}
