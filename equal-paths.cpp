#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool oneChild(Node * root);
bool twoChild(Node * root);
bool isLeaf(Node * root);
void numVertex(Node* root, int& count);




bool equalPaths(Node * root)
{
    // Add your code below

    if(root == NULL){
        return true;
    }

    if(isLeaf(root)){
        return true;
    }

    if(oneChild(root)){
        if(root->right == NULL){
            return equalPaths(root->left);
        }
        else if(root->left == NULL){
            return equalPaths(root->right);
        }
        //return true;
    }

    if(twoChild(root)){
        int l = 0;
        int r = 0;

        numVertex(root->left, l);
        numVertex(root->right, r);

        if(root->left->left != NULL && root->left->right != NULL )
            if(isLeaf(root->left->left) && !(isLeaf(root->left->right))){
                return false;
            }
        if(abs(l-r) > 1){
            return false;
        }
        else{
            return true;
        }
    }
}

bool oneChild(Node* root){
    if(root -> right == NULL && root->left != NULL){
        return true;
    }
    else if(root->left == NULL && root->right != NULL){
        return true;
    }

    else{
        return false;
    }
}

bool twoChild(Node* root){
    if(root->left != NULL && root->right != NULL){
        return true;
    }

    else{
        return false;
    }
}

bool isLeaf(Node* root){
    if(root-> left == NULL && root-> right == NULL){
        return true;
    }
    else{
        return false;
    }
}

void numVertex(Node* root, int& count){
    if(root == NULL){
        return;
    }

    else{
        numVertex(root->left, count);
        numVertex(root->right, count);
        count++;
    }

}

