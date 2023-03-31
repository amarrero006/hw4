#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"
#include "print_bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;


protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
        Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
    bool leftHeavy(AVLNode<Key, Value>* root); // Done //
    bool rightHeavy(AVLNode<Key, Value>* root); // Done //
    bool leftLeft(AVLNode<Key, Value>* root); // Done //
    bool leftRight(AVLNode<Key, Value>* root); // Done //
    bool rightRight(AVLNode<Key, Value>* root); // Done //
    bool rightLeft(AVLNode<Key,Value>* root); // Done //
    void rotateLeft(AVLNode<Key, Value>* n1, AVLNode<Key,Value>*n2); //  Done //
    void rotateRight(AVLNode<Key, Value>* n1, AVLNode<Key,Value>*n2); // DONE  //
    int calculateBalance(AVLNode<Key, Value>* root); // DONE! //
    void update(AVLNode<Key, Value>*current); // Done //
    void performBalance(AVLNode<Key, Value>* root); // Done //
    void updateTree(AVLNode<Key, Value>* root);
    void updateRoot(AVLNode<Key,Value>* current);
    int whatBalance(AVLNode<Key, Value>* root);

protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

};

template<class Key, class Value>
int AVLTree<Key, Value>::whatBalance(AVLNode<Key, Value> *root) {
    return root->getBalance();
}


template<class Key, class Value>
void AVLTree<Key, Value>::updateTree(AVLNode<Key, Value>* root) {
    if(root == NULL){
        return;
    }
    updateTree(root->getLeft());
    updateTree(root->getRight());
    update(root);
    if(abs(root->getBalance()) > 1){
        performBalance(root);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::performBalance(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return;
    }
    if(leftHeavy(root)){
    
        if(leftRight(root)){
            rotateLeft(root->getLeft(), root->getLeft()->getRight());
            rotateRight(root, root->getLeft());
            //performBalance(root);
        }

       if(leftLeft(root)){
            rotateRight(root, root->getLeft());
        }
    }


    else if(rightHeavy(root)){

       if(rightLeft(root)){
            rotateRight(root->getRight(), root->getRight()->getLeft());
            //performBalance(root);
            rotateLeft(root, root->getRight());
            
        }
       if(rightRight(root)){
            rotateLeft(root, root->getRight());
        }
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::update(AVLNode<Key, Value> *current) {
    current->setBalance(calculateBalance(current));
}

template<class Key, class Value>
bool AVLTree<Key, Value>::leftHeavy(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return false;
    }
    if(calculateBalance(root) < -1){
        return true;
    }
    else{
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::rightHeavy(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return false;
    }
    if(calculateBalance(root) > 1){
        return true;
    }
    else{
        return false;
    }
}


template<class Key, class Value>
bool AVLTree<Key, Value>::leftLeft(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return false;
    }
    if(leftHeavy(root)  && root->getLeft()->getLeft()!=NULL){
        return true;
    }
    else{
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::leftRight(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return false;
    }
    if(leftHeavy(root) && root->getLeft()->getRight()!=NULL){
        return true;
    }
    else{
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::rightRight(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return false;
    }
    if(rightHeavy(root) && root->getRight()->getRight()!=NULL){
        return true;
    }
    else{
        return false;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::rightLeft(AVLNode<Key, Value> *root) {
    if(root == NULL){
        return false;
    }
    if(rightHeavy(root) && root->getRight()->getLeft()!=NULL){
        return true;
    }
    else{
        return false;
    }
}


template<class Key, class Value>
int AVLTree<Key, Value>::calculateBalance(AVLNode<Key, Value>* root){
    return (this->getHeight(root->getRight()) - this->getHeight(root->getLeft()));
}

template<class Key, class Value>
void AVLTree<Key, Value>::updateRoot(AVLNode<Key,Value>* current){
    this->root_ = static_cast<Node<Key,Value>*>(current);
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2) {

    if(n1 == this->root_){
        updateRoot(n2);
    }
    n2->setParent(n1->getParent());
    n1->setLeft(n2->getRight());
    if(n1->getLeft()!= NULL){
        n1->getLeft()->setParent(n1);
    }
    n2->setRight(n1);

    if(n1->getParent()!= NULL) {
        if (this->isLeftChild(n1)) {
            n1->getParent()->setLeft(n2);
        } else if (this->isRightChild(n1)) {
            n1->getParent()->setRight(n2);
        }
    }

    n1->setParent(n2);
    update(n1);
    update(n2);

}
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2) {
    if(n1 == this->root_){
        updateRoot(n2);
    }
    n2->setParent(n1->getParent());
    n1->setRight(n2->getLeft());
    if(n1->getRight()!= NULL){
        n1->getRight()->setParent(n1);
    }
    n2->setLeft(n1);
    if(n1->getParent()!= NULL) {
        if (this->isLeftChild(n1)) {
            n1->getParent()->setLeft(n2);
        } else if (this->isRightChild(n1)) {
            n1->getParent()->setRight(n2);
        }
    }

    n1->setParent(n2);
    update(n1);
    update(n2);

}
/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    if(this->empty()){
        AVLNode<Key, Value> *addition = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        this->root_ = addition;
        this-> manyNodes++;

        return;
    }

    if(this->find(new_item.first) != this->end()){
        this->find(new_item.first).current_->setValue(new_item.second);
        return;
    }


    AVLNode<Key, Value> *addition = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    BinarySearchTree<Key, Value>::recursiveInsert(this->root_, addition);
    
    AVLNode<Key, Value>* temp = reinterpret_cast<AVLNode<Key, Value>*>(this->root_);
    updateTree(temp);
    AVLNode<Key, Value>* temp2 = reinterpret_cast<AVLNode<Key, Value>*>(this->root_);
    updateTree(temp2);
    //std::cout <<"ROOT = " << this->root_->getKey() <<" " << std::endl; 

    
    //if(this->root_->getRight() != NULL){
    //AVLNode<char, int>* temp2 = static_cast<AVLNode<char, int>*>(this->root_);
    //std::cout <<"Root->right<< " << (temp2->getRight())->getKey() <<  "= RIGHT HEAVY? : " << rightHeavy(temp2->getRight())<< std::endl << "is RIGHTRIGHT?" << rightRight(temp2->getRight())<< std::endl;
    //std::cout<<"Is RIGHTLEFT? : " << rightLeft(temp2->getRight()) << std:: endl;
    //}
 

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
   updateTree(static_cast<AVLNode<Key, Value>*>(this->root_));
    BinarySearchTree<Key, Value>::remove(key);
   
    updateTree(static_cast<AVLNode<Key, Value>*>(this->root_));
    //updateTree(static_cast<AVLNode<Key, Value>*>(this->root_));

    
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
