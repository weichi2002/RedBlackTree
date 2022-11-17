#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>


RedBlackTree::RedBlackTree(){
    root = nullptr;
    numItems = 0;
}

void RedBlackTree::destroyRecursive(Node* node){
    if(node != nullptr){
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }

}

RedBlackTree::~RedBlackTree(){
    destroyRecursive(root);
}

void RedBlackTree::fixTree(Node* node){
   
    while (node->parent->color == COLOR_RED){

        cout << "Fixing Node :" << node->data << endl;
        Node* uncle;
        Node* parent = node->parent;
        Node* grandparent = node->parent->parent;
        // cout << "grandparent" << grandparent->data << endl;
        // cout << "parent" << parent->data << endl;
        // cout << "grandparent->right" << grandparent->right->data << endl;

        if (parent == grandparent->right) {//parent is right child

            uncle = grandparent->left; //left uncle

            if (uncle != nullptr && uncle->color == COLOR_RED ) { //if uncle color is red, then just recolor
                cout << "LEFT RED UNCLE" << endl;
                cout << "grandparent color" << grandparent->color << endl;
                grandparent->color = COLOR_RED;
                cout << "uncle color " << uncle->color << endl;

                uncle->color = COLOR_BLACK;
                cout << "parent color " << parent->color << endl;
                parent->color = COLOR_BLACK;
                cout << "here" << endl;
                node = grandparent;
            } 
            else {//uncle is black, rotate and recolor

                if (node == parent->left) {// RL case
                    cout << "RIGHT LEFT CASE" << endl;
                    RightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }else{
                    cout << "RIGHT RIGHT CASE" << endl;
                }
                swap(parent->color, grandparent->color); //RR case
                LeftRotate(grandparent);
            }

        } else { //right uncle

            uncle = grandparent->right; 

            if (uncle != nullptr && uncle->color == COLOR_RED) {//if uncle color is red, then just recolor
                cout << "RIGHT RED UNCLE" << endl;
                uncle->color = COLOR_BLACK;
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;

            } else {//uncle is black, rotate and recolor

                if (node == parent->right) {//left right case, rotate left first then right
                cout << "LEFT RIGHT CASE" << endl;
                    LeftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }else{
                    cout << "LEFT LEFT CASE" << endl;
                }
                swap(parent->color, grandparent->color); //left left case, rotate right
                RightRotate(grandparent);
            }
        }
        if(node == root){//if node is root, then stop
            break;
        }
  }
  root->color = COLOR_BLACK;  
}

void RedBlackTree::RightRotate(Node* node) {

    Node* temp = node->left;
    node->left = temp->right;

    if(node->left != nullptr){
        node->left->parent = node;
    }
    temp->parent = node->parent;
    
    if (node->parent == nullptr){
        root = temp;
    }
    else if(node == node->parent->left){
       node->parent->left = temp;
    }
    else{
        node->parent->right = temp;
    }

    temp->right = node;
    node->parent = temp;
 
    
}


 void RedBlackTree::LeftRotate(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;

    if (node->right != NULL){
        node->right->parent = node;
    }
 
    temp->parent = node->parent;
 
    if (node->parent == NULL){
        root = temp;

    }else if (node == node->parent->left){
        node->parent->left = temp;

    }else{
        node->parent->right = temp;
    }

    temp->left = node;
    node->parent = temp;
}

void RedBlackTree::bstInsert(Node* insert){

    Node* cur = root;
    while (cur != nullptr) {
        if (insert->data < cur -> data) {
            if (cur -> left != nullptr) {
                cur = cur -> left;
            } else {
                // cout << "here" << insert-> data << endl;
                cur -> left = insert;
                insert->parent = cur;
                // cout << "parent" << insert->parent->data << endl;

                // cout << "grandparent" << insert->parent->parent->data << endl;
                break;
            }
        } else {
            if (cur -> right != nullptr) {
                cur = cur -> right;
            } else {
                cur -> right = insert;
                insert->parent = cur;
                break;
            }
        }
    }
}

void RedBlackTree::Insert(int num){

    // if(Contains(num)){
    //     throw invalid_argument("Duplicate items are not allowed");
    // }
    cout << endl << "Inserting " << num << endl;
    numItems++; //increase count
    Node* temp = new Node(num);

    //root case
    if(root == nullptr){
       root = temp;
       root->color = COLOR_BLACK;
       return;
    }

    //insert into BST tree
    bstInsert(temp);

    //If the parent of newNode is Black then exit from the operation
    //if the parent is red, then fix the tree
    fixTree(temp);
    //fix double red
}


void RedBlackTree::inorder(Node* root, string& s){
    if (!root) return; //if root is null, return

    inorder(root -> left, s);
    s += " ";
    s += (root->color == COLOR_BLACK)? "B": "R"; //determine which color to add
    s += to_string(root->data);
    s += " ";
    inorder(root -> right, s);
}

string RedBlackTree::ToInfixStringPrivate(Node* root){
    if(!root) return "";
    string s;
    inorder(root, s); //calls helper function
    return s;
}

void RedBlackTree::preorder(Node* root, string& s){
    if (!root) return; //if root is null, return

    // cout << "here" << endl;
    s += " ";
    s += (root->color == COLOR_BLACK)? "B": "R"; //determine which color to add
    s += to_string(root->data);
    s += " ";
    preorder(root -> left, s);
    preorder(root -> right, s);

}

string RedBlackTree::ToPrefixStringPrivate(Node* root){
    if(!root) return "";

    string s;
    preorder(root, s); //calls helper function
    return s;
}

void RedBlackTree::postorder(Node* root, string& s){
    if (!root) return; //if root is null, return

    postorder(root -> left, s);
    postorder(root -> right, s);
    s += " ";
    s += (root->color == COLOR_BLACK)? "B": "R"; //determine which color to add
    s += to_string(root->data);
    s += " ";
}

string RedBlackTree::ToPostfixStringPrivate(Node* root){
    if(!root) return "";
    string s;
    postorder(root, s); //calls helper function
    return s;
}

int RedBlackTree::size() const {
    return numItems;
}

int RedBlackTree::GetMax() const{

    Node* cur = root;
    while(cur->right != nullptr){
        cur = cur->right;
    }
    return cur->data;
}

int RedBlackTree::GetMin() const{

    Node* cur = root;
    while(cur->left != nullptr){
        cur = cur->left;
    }
    return cur->data;
}

bool RedBlackTree::Contains(int num){

    //use bst search to find duplicates
    Node* cur = root;
    while (cur != nullptr) {

        if(cur->data == num){//
            return true;
        }

        if (num < cur -> data) {
            if (cur -> left != nullptr) {
                cur = cur -> left;
            }else{
                break;
            }
        } else {
            if (cur -> right != nullptr) {
                cur = cur -> right;
            }else{
                break;
            }
        }
    }
    return false;

}


