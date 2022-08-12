#include <iostream>

using namespace std;
 
class Node {
public:
    Node* lchild;
    int data;
    Node* rchild;
    int height;
};
 
class AVL{
public:
    Node* root;
 
    AVL(){ root = nullptr; }
 
    // Helper methods for inserting
    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    Node* LL_Rotation(Node* p);
    Node* RR_Rotation(Node* p);
    Node* LR_Rotation(Node* p);
    Node* RL_Rotation(Node* p);
 
    // Insert
    Node* rInsert(Node* p, int key);
 
    // Traversal
    void Inorder(Node* p);
    void Inorder(){ Inorder(root); }
    Node* getRoot(){ return root; }
};
 
int AVL::NodeHeight(Node *p) {
    int hl;
    int hr;
 
    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;
 
    return hl > hr ? hl + 1 : hr + 1;
}
 
int AVL::BalanceFactor(Node *p) {
    int hl;
    int hr;
 
    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;
 
    return hl - hr;
}
 
Node* AVL::LL_Rotation(Node *p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;
 
    pl->rchild = p;
    p->lchild = plr;
 
    // Update height
    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);
 
    // Update root
    if (root == p){
        root = pl;
    }
    return pl;
}
 
Node* AVL::RR_Rotation(Node *p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;
 
    pr->lchild = p;
    p->rchild = prl;
 
    // Update height
    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);
 
    // Update root
    if (root == p){
        root = pr;
    }
    return pr;
}
 
Node* AVL::LR_Rotation(Node *p) {
    return nullptr;
}
 
Node* AVL::RL_Rotation(Node *p) {
    return nullptr;
}
 
Node* AVL::rInsert(Node *p, int key) {
    Node* t;
    if (p == nullptr){
        t = new Node;
        t->data = key;
        t->lchild = nullptr;
        t->rchild = nullptr;
        t->height = 1;  // Starting height from 1 onwards instead of 0
        return t;
    }
 
    if (key < p->data){
        p->lchild = rInsert(p->lchild, key);
    } 
    else if (key > p->data){
        p->rchild = rInsert(p->rchild, key);
    }
 
    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LL_Rotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){
        return LR_Rotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){
        return RR_Rotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){
        return RL_Rotation(p);
    }
 
    return p;
}
 
void AVL::Inorder(Node *p) {
    if (p){
        Inorder(p->lchild);
        cout << p->data << ", " << flush;
        Inorder(p->rchild);
    }
}
 
int main() {
    AVL tll;
    AVL trr;
 
    // LL Rotation
    tll.root = tll.rInsert(tll.root, 30);
    tll.root = tll.rInsert(tll.root, 20);
    tll.root = tll.rInsert(tll.root, 10);
    tll.Inorder();
    cout << endl;
 
    // RR Rotation
    trr.root = trr.rInsert(trr.root, 10);
    trr.root = trr.rInsert(trr.root, 20);
    trr.root = trr.rInsert(trr.root, 30); 
    trr.Inorder();
    cout << endl;
 
    return 0;
}

