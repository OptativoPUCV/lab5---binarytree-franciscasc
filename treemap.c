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
    aux = tree->root;
    tree->current = aux;
  }
  
  if(tree->current != NULL){
    if(searchTreeMap(tree, key) != NULL) return;
    
        TreeNode * nuevo = createTreeNode(key, value);
        nuevo->parent = tree->current;
        if(tree->lower_than(tree->current->pair->key, key) == 1){
          tree->current->right->right = nuevo;
          nuevo->parent = tree->current->right;
          tree->current = tree->current->right->right;
        }
        else{
          tree->current->left->left = nuevo;
          nuevo->parent = tree->current->left;
          tree->current = tree->current->left->left;
        }
  }
  return;
}
  /*if(tree->root == NULL){
    TreeNode * nuevo = createTreeNode(key, value);
    tree->root = nuevo;
    tree->current = tree->root;
    return;
  }

  if(searchTreeMap(tree,key) == NULL){
    TreeNode *nNodo = createTreeNode(key, value);
    nNodo->parent = tree->current;
    if(tree->lower_than(tree->current->pair->key, key) == 0){
      tree->current->left->left = nNodo;
      nNodo->parent = tree->current->left;
      tree->current = tree->current->left->left;
    }  
    else{
      tree->current->right->right = nNodo;
      nNodo->parent = tree->current->right;
      tree->current = tree->current->right->right;
    }
  }
  else{
    return;
  }*/


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
  /*if(node->parent->right == NULL && node->parent->left == NULL){
    node->parent = NULL;
  }
  if(){
    
  }*/
  
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
  /*TreeNode * ub_node;
  ub_node = tree->current;
  if(searchTreeMap(tree, key) != NULL){
    if(tree->lower_than(key, ub_node->pair->key) == 1){
      
    }
  }*/
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
      tree->current->parent = tree->current;
    }
    else{
      return tree->current->pair;
    }
  
  return tree->current->pair;
}
