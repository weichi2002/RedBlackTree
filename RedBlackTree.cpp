#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>


RedBlackTree::RedBlackTree(){
    root = nullptr;
    numItems = 0;
}

void RedBlackTree::destroyRecursive(Node* node){

    if(node == nullptr) return;
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
}

RedBlackTree::~RedBlackTree(){
    destroyRecursive(this->root);
    numItems = 0;
<<<<<<< HEAD
=======
    // cout << "===============DESTRUCTOR =======================" << endl;
>>>>>>> 0efcc1ee163b727c7e58267bda10f81302aabd15
}

Node* RedBlackTree::copyHelper(const Node* other, Node* prev){

    if (other == nullptr) return nullptr;
    Node* temp = new Node(other->data);
    temp->color = other->color;
    temp->parent = prev;
    temp->left = copyHelper(other->left, temp);
    temp->right = copyHelper(other->right, temp);
    return temp;
}

RedBlackTree::RedBlackTree(const RedBlackTree &other){
    root = copyHelper(other.root, nullptr); //I think the erorr is here for the copy constructor
    numItems = other.numItems;
}

void RedBlackTree::InsertFix(Node* node){

    while (node->parent->color == COLOR_RED){
        // cout << "Fixing Node :" << node->data << endl;
        Node* uncle;
        Node* parent = node->parent;
        Node* grandparent = node->parent->parent;

        if (parent == grandparent->right) {//parent is right child
            uncle = grandparent->left; //left uncle
            if (uncle != nullptr && uncle->color == COLOR_RED ) { //if uncle color is red, then just recolor
                // cout << "LEFT RED UNCLE" << endl;
                grandparent->color = COLOR_RED;
                uncle->color = COLOR_BLACK;
                parent->color = COLOR_BLACK;
                node = grandparent;
            } 
            else {//uncle is black, rotate and recolor

                if (node == parent->left) {// RL case
                    // cout << "RIGHT LEFT CASE" << endl;
                    RightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }else{
                    // cout << "RIGHT RIGHT CASE" << endl;
                }
                swap(parent->color, grandparent->color); //RR case
                LeftRotate(grandparent);
            }
        } else { //right uncle
            uncle = grandparent->right; 
            if (uncle != nullptr && uncle->color == COLOR_RED) {//if uncle color is red, then just recolor
                // cout << "RIGHT RED UNCLE" << endl;
                uncle->color = COLOR_BLACK;
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;

            } else {//uncle is black, rotate and recolor
                if (node == parent->right) {//left right case, rotate left first then right
                    // cout << "LEFT RIGHT CASE" << endl;
                    LeftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }else{
                    // cout << "LEFT LEFT CASE" << endl;
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

    if (node->right != nullptr){
        node->right->parent = node;
    }
 
    temp->parent = node->parent;
 
    if (node->parent == nullptr){
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
                cur -> left = insert;
                insert->parent = cur;
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

void RedBlackTree::Insert(int num){//My insert runs at an average of 3e-05 second 

    if(Contains(num)){
       throw invalid_argument("Duplicae items are not allowed");
    }
    // cout << endl << "Inserting " << num << endl;
    numItems++; //increase count
    Node* temp = new Node(num);

    //root case
    if(root == nullptr){
       root = temp;
       root->color = COLOR_BLACK;
       return;
    }

    bstInsert(temp);
    //If the parent of newNode is Black then exit from the operation
    //if the parent is red, then fix the tree
    InsertFix(temp);
}


Node* RedBlackTree::Successor(Node* node) {
    Node *temp = node;

    while (temp->left != nullptr){
        temp = temp->left;//get the smallest left child
    }
    return temp;
}

Node* RedBlackTree::BSTreplace(Node* node) {

    if (node->left != nullptr && node->right != nullptr){//two children
        return Successor(node->right);
    }
    if (node->left == nullptr && node->right == nullptr){//leaf case
        return nullptr;
    }

    if (node->left != nullptr){//single child
        return node->left;
    }else{
        return node->right;
    }
}

Node* RedBlackTree::FindSibling(Node* node){

    if(node->parent == nullptr) return nullptr;

    Node* parent = node->parent;

    if(node == parent->left){

        return parent->right;

    }else{
        return parent->left;
    }

}

void RedBlackTree::FixDoubleBlack(Node* node){

    // cout << "DoubleBlack: " << endl;
    if(node == root) return; //root case
   
    Node* sibling = FindSibling(node);
    Node* parent = node->parent;

    if(sibling == nullptr){//No sibling
        FixDoubleBlack(parent);

    }else{

        if(sibling->color == COLOR_RED){//Red sibling
            // cout << "Red Siblings" << endl;
            parent->color = COLOR_RED;
            sibling->color = COLOR_BLACK;

            if(sibling == parent->left)
                RightRotate(parent);

            else
                LeftRotate(parent);
            
            FixDoubleBlack(node);

        }else{
            if((sibling->right != nullptr && sibling->right->color == COLOR_RED)
            || (sibling->left != nullptr && sibling->left->color == COLOR_RED)){
                // cout << "Sibling has a red child" << endl;

                if(sibling->left != nullptr && sibling->left->color == COLOR_RED){

                    if(sibling == parent->left){
                        // cout << "Left left" << endl;
                        sibling->left->color = parent->color;
                        sibling->color = parent->color;
                        RightRotate(parent);

                    }else{
                        // cout << "Right left" << endl;
                        sibling->left->color = parent->color;
                        RightRotate(sibling);
                        LeftRotate(parent);
                    }
                } else {

                    if (sibling== parent->left) {
                        // cout << " Left Right" << endl;
                        sibling->right->color = parent->color;
                        LeftRotate(sibling);
                        RightRotate(parent);
                    } else {
                        // cout << " Right Right" << endl;
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        LeftRotate(parent);
                    }

                }
                parent->color = COLOR_BLACK;

            } else {
                // cout << "Two Black children" << endl;
                sibling->color = COLOR_RED;
                if (parent->color == COLOR_BLACK){
                    FixDoubleBlack(parent);
                }else{
                    parent->color = COLOR_BLACK;
                    // cout << "here" << endl;
                }
            }
        }
    }

}

void RedBlackTree::RemoveHelper(Node* tbd){//tbd: to be deleted

    Node* replace = BSTreplace(tbd);

    bool doubleBlack = ((replace == nullptr or replace->color == COLOR_BLACK) and (tbd->color == COLOR_BLACK));
    Node* parent = tbd->parent;

    if(replace == nullptr){
        // cout << "Leaf case" << endl;
        if(tbd == root){
            // cout << "Delete root" << endl;
            root = nullptr;
        }
        else{
            if(doubleBlack){
                FixDoubleBlack(tbd);
            }else{
                if(FindSibling(tbd) != nullptr){
                    FindSibling(tbd)->color = COLOR_RED;
                }
            }

            if(tbd == parent->left){
                parent->left = nullptr;
            }else{
                parent->right = nullptr;
            }
        }
        delete tbd;
        return;
    }

    // cout << "Replace is: " << replace->data << endl;

    if(!tbd->left || !tbd->right){
        // cout << "One child" << endl;
        if(tbd == root){
            root = replace; 
            delete tbd;
        }else{
            if(tbd == parent->left){
                parent->left = replace;
            }else{
                parent->right = replace;
            }
            delete tbd;
            replace->parent = parent;
            if(doubleBlack){
                FixDoubleBlack(replace);
            }else{
                replace->color = COLOR_BLACK;
            }
        }
        return;
    }

    // cout << "Two children" << endl;
    int temp;
    temp = replace->data;
    replace->data = tbd->data;
    tbd->data = temp;
    RemoveHelper(replace);
}

void RedBlackTree::Remove(int num){//My remove runs at an average of 3e-06 second

    // cout << endl << "Removing " << num << endl;
    if(!Contains(num)){
        throw invalid_argument("Node is not found");
    }
    
    numItems--; 
    Node* cur = root;
    while(cur!= nullptr){
        if(cur->data == num){
            break;
        }
        if(cur->data > num){
            cur = cur->left;
        }else{
            cur = cur->right;
        }
    }
    RemoveHelper(cur);
}


void RedBlackTree::inorder(Node* root, string& s){
    if (!root) return; //if root is null, return

    inorder(root -> left, s);
    s += " ";
    s += (root->color == COLOR_BLACK)? "B": "R"; 
    s += to_string(root->data);
    s += " ";
    inorder(root -> right, s);
}

string RedBlackTree::ToInfixStringPrivate(Node* root){
    if(!root) return "";
    string s;
    inorder(root, s);
    return s;
}

void RedBlackTree::preorder(Node* root, string& s){
    if (!root) return;

    s += " ";
    s += (root->color == COLOR_BLACK)? "B": "R"; 
    s += to_string(root->data);
    s += " ";
    preorder(root -> left, s);
    preorder(root -> right, s);

}

string RedBlackTree::ToPrefixStringPrivate(Node* root){
    if(!root) return "";

    string s;
    preorder(root, s);
    return s;
}

void RedBlackTree::postorder(Node* root, string& s){
    if (!root) return; 

    postorder(root -> left, s);
    postorder(root -> right, s);
    s += " ";
    s += (root->color == COLOR_BLACK)? "B": "R"; 
    s += to_string(root->data);
    s += " ";
}

string RedBlackTree::ToPostfixStringPrivate(Node* root){
    if(!root) return "";
    string s;
    postorder(root, s); 
    return s;
}

int RedBlackTree::size() const {
    return numItems;
}

int RedBlackTree::GetMax() const{
    if(numItems == 0) throw invalid_argument("RedBlackTree is empty");

    Node* cur = root;
    while(cur->right != nullptr){
        cur = cur->right;
    }
    return cur->data;
}

int RedBlackTree::GetMin() const{
    if(numItems == 0) throw invalid_argument("RedBlackTree is empty");

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
