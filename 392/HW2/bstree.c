/*******************************************************************************
 * Name        : bstree.c
 * Author      : Yash Yagnik
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_node(void* data, size_t data_size, tree_t* tree, int (*cmpr)(void*, void*)){
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = malloc(data_size);
    node_t* current = tree->root;
   
    char* my_data = (char*)(node->data);
    char* new_data = (char*)data;

    for (size_t i = 0; i < data_size; ++i) {
        my_data[i] = new_data[i];
    }

    node->left = NULL;
    node->right = NULL;
    
    if (tree->root == NULL){
        tree->root = node;
    }
    else{
        while (1){
            if (cmpr(data, current->data) < 0){
                if (current->left == NULL){
                    current->left = node;
                    break;
                }
                else{
                    current = current->left;
                }
                
            }
            else if (cmpr(data, current->data) >= 0){
                if (current->right == NULL){
                    current->right = node;
                    break;
                }
                else{
                    current = current->right;
                }
            }

        }
    }

}

void print_tree(node_t* root, void(*fun)(void*)){
    if (root != NULL){
        print_tree(root->left, fun);
        fun(root->data);
        print_tree(root->right, fun);
    }   
}

void destroy_helper(node_t* node) {
    if (node != NULL) {
        destroy_helper(node->left);
        destroy_helper(node->right);
        free(node->data);
        free(node);
    }
}

void destroy(tree_t* tree){
    destroy_helper(tree->root);
    tree->root = NULL;
}