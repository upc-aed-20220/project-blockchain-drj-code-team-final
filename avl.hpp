#include "nodeA.hpp"
#include "string"
#include <math.h>
#include <cstdlib>

using namespace std;

template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;

public:
    AVLTree() : root(nullptr),contNodos(0) {}
    void insert(T value){
        insert(this->root, value);
    }

    bool find(T value){
        return find(this->root, value);
    }

    int height(){
        return height(this->root);
    }

    T minValue(){
        return minValue(this->root);
    }

    T maxValue(){
        return maxValue(this->root);
    }

    bool isBalanced(){
        return isBalanced(this->root);
    }

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    void insert(NodeBT<T> *&node, T value);
    bool find(NodeBT<T> *node, T value);
    int height(NodeBT<T> *node);
    bool isBalanced(NodeBT<T> *node);
    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);
   
    int balancingFactor(NodeBT<T> *node);
    void updateHeight(NodeBT<T> *node);
    void balance(NodeBT<T> *&node);
    void left_rota(NodeBT<T> *&node);
    void right_rota(NodeBT<T> *&node);
};

template <typename T>
bool AVLTree<T>::find(NodeBT<T> *node, T value)
{
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}

template <typename T>
void AVLTree<T>::insert(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        node = new NodeBT<T>(value);
    else if (value < node->data)
        insert(node->left, value);
    else
        insert(node->right, value);    

    //actualizar la altura para luego verificar nodos criticos
    updateHeight(node);  
    balance(node);           
}

template <typename T>
int AVLTree<T>::height(NodeBT<T> *node)
{
    if (node == nullptr) return -1;
    else return node->height;
}

template <typename T>
bool AVLTree<T>::isBalanced(NodeBT<T> *node){
    if (abs(balancingFactor(node)) > 1) return false;//height(node->left) - height(node->right)
    else return true;
}

template <typename T>
void AVLTree<T>::balance(NodeBT<T> *&node){
    if (isBalanced(node) == true) return;
    else{// esta sobrecargado hacia uno de los lados

        if (balancingFactor(node) > 1){//sobrecargado a al isq
            if (balancingFactor(node->left) < 0){//rotacion doble
                left_rota(node->left);
                right_rota(node);
            }
            else right_rota(node);// rotacion simple
        }
        else {//sobrecargado a la der
            if (balancingFactor(node->right) > 0){//rotacion doble
                right_rota(node->right);
                left_rota(node);
            }
            else left_rota(node);// rotacion simple
        }
    }
}

template <typename T>    
void AVLTree<T>::left_rota(NodeBT<T> *&node){
    auto temp = node->right;
    node->right = temp->left;
    temp->left = node;
    updateHeight(node);
    node = temp;
    updateHeight(node);
}

template <typename T>   
void AVLTree<T>::right_rota(NodeBT<T> *&node){
    auto temp = node->left;
    node->left = temp->right;
    temp->right = node;
    updateHeight(node);
    node = temp;
    updateHeight(node);
}

template <typename T>
T AVLTree<T>::minValue(NodeBT<T> *node){
 NodeBT<T>* temp = node;
    while(temp->left != nullptr){
		 temp = temp->left;}
 return temp->data;
}

template <typename T>
T AVLTree<T>::maxValue(NodeBT<T> *node){
 NodeBT<T>* temp = node;
	while(temp->right != nullptr){
		temp = temp->right;}
 return temp->data;
}

template <typename T>
int AVLTree<T>::balancingFactor(NodeBT<T> *node){
    return height(node->left) - height(node->right);
}

template <typename T>
void AVLTree<T>::updateHeight(NodeBT<T> *node)
{    
    node->height = max(height(node->left), height(node->right)) + 1;
}

