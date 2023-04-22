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
    TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));
    if(new == NULL) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(tree->root == NULL){
    TreeNode *aux = createTreeNode(key, value);
    tree->root = aux;
  }
  
  if(tree->root != NULL){
    if(searchTreeMap(tree, key) != NULL) return;
    
    TreeNode * nuevo = createTreeNode(key, value);
    nuevo->parent = tree->root;
    if(tree->lower_than(tree->root->pair->key, key) == 1){
      tree->root->right->right = nuevo;
      nuevo->parent = tree->root->right;
      tree->current = tree->root->right->right;
    }
    else{
      tree->root->left->left = nuevo;
      nuevo->parent = tree->root->left;
      tree->current = tree->root->left->left;
    }
  }
}

TreeNode * minimum(TreeNode * x){
  if(x->left == NULL) return x;
  else{
    while(x->left != NULL){
      x = x->left;
    }
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(searchTreeMap(tree, tree->current->pair->key) != NULL){
    TreeNode *aux;
    if(tree->current->left == NULL && tree->current->right == NULL){
      aux = tree->current;
      tree->current = tree->current->parent;
      tree->current->right = NULL;
      tree->current->left = NULL;
      aux->parent = NULL;
    }
    
    /*tree->current = tree->root;
    aux = tree->current;
    if(aux != NULL) {
      //nodo sin hijo
      if(node->left == NULL && node->right == NULL){
        if(node->parent == NULL){
          aux = NULL;
        }
        else{
          if(node->parent->left != NULL)
            node->parent->left = NULL;
          else{
            node->parent->right = NULL;
          }
        }
      }

      //nodo con un hijo
      if(node->left == NULL || node->right == NULL){
        aux = tree->current;
        if(node->right != NULL){
          aux = aux->right;
          node->parent = aux->parent;
          if(aux->parent->left == NULL)
            aux->parent->right = aux;
          else{
            aux->parent->left = aux;
          }
          aux->left = NULL;
          aux->right = NULL;
        }
        if(node->left != NULL){
          aux = aux->left;
          node->parent = aux->parent;
          if(aux->parent->right == NULL)
            aux->parent->left = aux;
          else{
            aux->parent->right = aux;
          }
          aux->left = NULL;
          aux->right = NULL;
        }
      }
    }
    //nodo con dos hijos
    if(aux->left != NULL){
      aux = aux->left;
    }
    else{
      aux = aux->right;
    }*/
  }
  return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * aux;
    tree->current = tree->root;
    aux = tree->current;
    while(aux != NULL){
      if(is_equal(tree, aux->pair->key, key) == 1) 
          return aux->pair;
      if(tree->lower_than(aux->pair->key, key) == 1){
          aux = tree->current->right;
          tree->current = aux;
      }
      else{
          aux = tree->current->left;
          tree->current = aux;
      }
      tree->current = aux;
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode * ub_node;
    tree->current = tree->root;
    ub_node = tree->current;
    //if(ub_node == NULL) return NULL;
    while(ub_node != NULL){
      if(tree->lower_than(key, tree->current->pair->key) == 0){
          ub_node = tree->current->right;
          tree->current = ub_node;
      }
      else{
          ub_node = tree->current->left;
          tree->current = ub_node;
      }
      //ub_node = tree->current;
    }
  return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  tree->current = tree->root;
  if(tree->current == NULL) return NULL;
  while(tree->current->left != NULL){
    tree->current = tree->current->left;
  }
  return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  while(tree->current != NULL){
    if(tree->current->right != NULL ){
      tree->current = tree->current->right;
      return tree->current->pair;
    }
  
    if(tree->current->left != NULL){
      tree->current = tree->current->left;
      return tree->current->pair;
    }
  }

   if(tree->lower_than(tree->current, tree->current->pair->key) == 1){
      tree->root->parent = tree->current;
    }
    else{
      return tree->root->pair;
    }
  return tree->root->pair;
}
