#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
  new->root = NULL;
  new->current = NULL;
  new->lower_than = lower_than;
  return new;
}
void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(tree == NULL) return;

  if(tree->root == NULL){
    TreeNode *nodo = createTreeNode(key, value);
    tree->root = nodo;
    tree->current = nodo;
    return;
  }

  TreeNode *aux = tree->root;
  while(aux != NULL){
    if(is_equal(tree, key, aux->pair->key)){
      return;
    }

    if(tree->lower_than(key, aux->pair->key)){
      if(aux->left == NULL){
        TreeNode *nodo = createTreeNode(key, value);
        nodo->parent = aux;
        aux->left = nodo;
        tree->current = nodo;
        return;
      }
      else{
        aux = aux->left;
      }
    }
    else {
      if(aux->right == NULL){
        TreeNode *nodo = createTreeNode(key, value);
        nodo->parent = aux;
        aux->right = nodo;
        tree->current = nodo;
        return;
      }
      else{
        aux = aux->right;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
  while(x->left != NULL){
    x = x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(tree == NULL || node == NULL) return;
  
  if(node->left == NULL && node->right == NULL){
    if(node->parent == NULL){
      tree->root = NULL;
    }
    else if(node->parent->left == node){
      node->parent->left = NULL;
    }
    else{
      node->parent->right = NULL;
    }
  }
  free(node);


  // Verifica si el nodo tiene solo un hijo izquierdo
  if(node->right == NULL){
      // Reemplaza el nodo con su hijo izquierdo
      if(node->parent == NULL){
          tree->root = node->left; // Nodo raíz
      }
      else{
          if(node->parent->left == node){
              node->parent->left = node->left; // Nodo izquierdo del padre
          }
          else{
              node->parent->right = node->left; // Nodo derecho del padre
          }
      }
      free(node); // Libera la memoria ocupada por el nodo
  }
  else{
      // Verifica si el nodo tiene solo un hijo derecho
      if(node->left == NULL){
          // Reemplaza el nodo con su hijo derecho
          if(node->parent == NULL){
              tree->root = node->right; // Nodo raíz
          }
          else{
              if(node->parent->left == node){
                  node->parent->left = node->right; // Nodo izquierdo del padre
              }
              else{
                  node->parent->right = node->right; // Nodo derecho del padre
              }
            
          }
          free(node); // Libera la memoria ocupada por el nodo
      }
  }
  
}

void eraseTreeMap(TreeMap * tree, void* key){
  if (tree == NULL || tree->root == NULL) return;

  if (searchTreeMap(tree, key) == NULL) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);
}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode * aux = tree->root;  
  while(aux!=NULL){
    if(is_equal(tree, key, aux->pair->key)){
      tree->current = aux;
      return aux->pair;
    }
    if(tree->lower_than(key, aux->pair->key) ==1){
      aux = aux->left;
    }
    else{
      aux = aux->right;
    }
  
  }
  return NULL; 
}


Pair * upperBound(TreeMap * tree, void* key) {
  return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode * aux = minimum(tree->root);
  tree->current = aux;
  return aux->pair;

}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
