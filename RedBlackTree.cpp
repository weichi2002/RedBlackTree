#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>

RedBlackTree::RedBlackTree(){
    root = nullptr;
    numItems = 0;
}

void RedBlackTree::sortTree(Node* &node){
   
    while (node->parent->color == COLOR_RED && node != root){

        Node* uncle;
        Node* parent = node->parent;
        Node* grandparent = node->parent->parent;
        // cout << "grandparent" << grandparent->data << endl;

        if (parent == grandparent->right) {//parent is right child

            uncle = grandparent->left; //left uncle

            if (uncle->color == COLOR_RED && uncle != nullptr) { //if uncle color is red, then just recolor
                grandparent->color = COLOR_RED;
                uncle->color = COLOR_BLACK;
                parent->color = COLOR_BLACK;
                node = grandparent;

            } 
            else {//uncle is black, rotate and recolor

                if (node == parent->left) {// RL case
                    node = parent;
                    RightRotate(node);
                }
                parent->color = COLOR_BLACK; //RR case
                grandparent->color = COLOR_RED;
                LeftRotate(grandparent);
            }

        } else { //right uncle

            uncle = grandparent->right; //this causes seg fault

            if (uncle->color == COLOR_RED) {//if uncle color is red, then just recolor

                uncle->color = COLOR_BLACK;
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;

            } else {//uncle is black, rotate and recolor

                if (node == parent->right) {//left right case, rotate left first then right
                    LeftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                swap(parent->color, grandparent->color); //left left case, rotate right
                RightRotate(grandparent);
            }
        }
  }
  root->color = COLOR_BLACK;
}

void RedBlackTree::RightRotate(Node* &node) {

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


 void RedBlackTree::LeftRotate(Node* &node) {
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



/*

Every node has a color either red or black.
The root of the tree is always black.
There are no two adjacent red nodes (A red node cannot have a red parent or red child).
Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
All leaf nodes are black nodes.

*/

void RedBlackTree::Insert(int num){

    if(Contains(num)){
        throw invalid_argument("Duplicate items are not allowed");
    }

    numItems++; //increase count
    
    Node* temp = new Node(num);

    //root case
    if(root == nullptr){
       root = temp;
       root->color = COLOR_BLACK;
       return;
    }

    //insert into BST tree
    Node* cur = root;

    while (cur != nullptr) {
        if (num < cur -> data) {
            if (cur -> left) {
                cur = cur -> left;
            } else {
                cur -> left = temp;
                temp->parent = cur;
                break;
            }
        } else {
            if (cur -> right) {
                cur = cur -> right;
            } else {
                cur -> right = temp;
                temp->parent = cur;
                break;
            }
        }
    }

    cout << "here" << endl;
    //If the parent of newNode is Black then exit from the operation.
    if(temp->parent->color == COLOR_BLACK) return;
    //if it is red, then fix the tree
    sortTree(temp);
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

    string tree = ToPostfixString();
    if(tree.find(to_string(num)) == string::npos){
        return false; //if the string is not found, return false
    } 
    else return true;
}


