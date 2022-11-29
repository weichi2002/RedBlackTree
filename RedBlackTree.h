#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define COLOR_RED 1
#define COLOR_BLACK 0

#include <vector>
#include <string>

using namespace std;

/*
Property #1: Red - Black Tree must be a Binary Search Tree, no duplicates are allowed.
Property #2: The ROOT node must be colored BLACK.
Property #3: The children of Red colored node must be colored BLACK. (There should not be two consecutive RED nodes).
Property #4: In all the paths of the tree, there should be same number of BLACK colored nodes.
Property #5: Every new node must be inserted with RED color.
Property #6: Every leaf (e.i. NULL node) must be colored BLACK.
Nullptr is black
*/


struct Node{
    int data;
    unsigned short color; //red is 1, black is 0
    Node *left, *right, *parent;

    Node(int data){
       this->data = data;
       left = right = parent = nullptr;
       this->color = COLOR_RED;
    }

};

class RedBlackTree{

    public: 
        RedBlackTree();
        ~RedBlackTree();
        RedBlackTree(const RedBlackTree &copy); //copy constructor

        void Insert(int num);
        void Remove(int num);
        bool Contains(int num);
        int GetMin() const;
        int GetMax() const;
        int size() const;

        string ToInfixString() {return ToInfixStringPrivate(root);};
        string ToPrefixString() {return ToPrefixStringPrivate(root);};
        string ToPostfixString() { return ToPostfixStringPrivate(root);};
        

    private:
        unsigned long long int numItems;
        Node *root;

        //to string helper functions
        string ToPrefixStringPrivate(Node* root); //preorder
        string ToPostfixStringPrivate(Node* root); //inorder
        string ToInfixStringPrivate(Node* root); //postorder
        void inorder(Node* root, string& s);
        void preorder(Node* root, string& s);
        void postorder(Node* root, string& s);

        //insert helper functions
        void InsertFix(Node* node);
        void RightRotate(Node* node);
        void LeftRotate(Node* node);
        void bstInsert(Node* node);

        //delete helper functions
        void destroyRecursive(Node* node);
        Node* copyHelper(const Node* copy, Node* prev);

        //delete helper functions
        void RemoveHelper(Node* node);
        Node* BSTreplace(Node* node);
        Node* Successor(Node* node);
        Node* FindSibling(Node* node);
        void FixDoubleBlack(Node* node);
               
        
};
#endif