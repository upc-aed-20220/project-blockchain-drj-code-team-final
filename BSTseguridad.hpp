#include "string"
#include <math.h>
#include "nodeBT.hpp"
using namespace std;

template <typename T>
class BSTree {
    private:
        NodeBT<T>* root;    
        int contNodos;
    public:
        BSTree(): root(nullptr),contNodos(0) {}

		void insert(T value){
            contNodos++;
            insert(root, value);
        }
        	
		bool find(T value){
            return find(root, value);
        }	

        T& findBlockChain(T value){
            return findBlockChain(root, value);
        }
        
        void display(){
            display(root);
        }

        string displayInOrder(){
            string arreglo = "";
            arreglo += displayInOrder(root);
            return arreglo;
        }

        string displayPreOrder(){
            string arreglo = "";
            arreglo += displayPreOrder(root);
            return arreglo;
        }
        
        string displayPosOrder(){
            string arreglo = "";
            arreglo += displayPosOrder(root);
            return arreglo;
        }
        
        T minValue(){
            NodeBT<T>* temp = this->root;
		    while(temp->left != nullptr)
		    	temp = temp->left;
		    return temp->data;
        } 

        T maxValue(){//obtener el maximo valor del arbol
            NodeBT<T>* temp = this->root;
		    while(temp->right != nullptr)
		    	temp = temp->right;
		    return temp->data;
        } 
        
        bool isBalanced(){//verificar si el arbol esta balanceado
            return isBalanced(root);
        } 

        int height(){
            return height(root);    
        }
        
        void remove(T value){
            remove(root, nullptr,value);
        } 

        T successor(T value){
            T result = value;
            successor(value,this->root,result);
            return result;
        }

        T predecessor(T value){
            T result = value;
            predecessor(value,this->root,result);
            return result;
        }    
            
        int size(){
            return contNodos;
        }

        bool isFull(){
            return isFull(root); 
        }     

        void clear(){
            contNodos=0;
            root->KillSelf();
            root = nullptr;
        }
        
        void buildFromOrderedArray(T *array, int n){
            buildFromOrderedArray(array,n,0,n-1,root);
        } 
        
        string displayBFS(){
            string array = "";
            for(int i=0; i<=height();i++)
                array += displayBFS(root, i);
            return array;
        }

        string displayDFS(){
            string arreglo = "";
            arreglo += displayPreOrder(root);
            return arreglo;
        }
        
        ~BSTree(){
            clear();
        } //Destructor del arbol

        private:
        T minValue(NodeBT<T>* node){//hecho por el profesor
            NodeBT<T>* temp = node;
		    while(temp->left != nullptr)
		    	temp = temp->left;
		    return temp->data;
        }
        
        NodeBT<T>* padreDelMinValue(NodeBT<T>* node){
            if (node->left != nullptr)
		        while(node->left->left != nullptr)
		    	    node = node->left;
		    return node;
        } 
        
        void insert(NodeBT<T>* &node, T value){
	    	if(node == nullptr)
	    		node = new NodeBT<T>(value);
	    	else if(value < node->data)
	    		insert(node->left, value);
	    	else if(value > node->data)
	    		insert(node->right, value);
	    	else node->data = value;
	    }

        bool find(NodeBT<T>* node, T value){
	        if(node == nullptr)
	            return false;
	        else if(value < node->data)
	            return find(node->left, value);
	        else if(value > node->data)
	            return find(node->right, value);
	        else return true;
	    }

        T& findBlockChain(NodeBT<T>* node, T value){
	        if(node == nullptr)
	            return false;
	        else if(value < node->data)
	            return find(node->left, value);
	        else if(value > node->data)
	            return find(node->right, value);
	        else return true;
	    }

        bool isFull(NodeBT<T>* node){
            bool full = true;
            if(node->left != nullptr){
                full == isFull(node->left);
            }
            if(full == false) return false;
            
            if(node->right != nullptr){
                full == isFull(node->right);
            }
            if(full == false) return false;

            if(node->left == nullptr && node->right != nullptr || node->left != nullptr && node->right == nullptr) return false; 
            else return true;
	    }

        void display(NodeBT<T>* node){
            if(node == nullptr) return;
            displayInOrder(node->left);
            cout << node->data;
            displayInOrder(node->right);
        }

        string displayPosOrder(NodeBT<T>* node){
            string array;
            if(node == nullptr) return "";
            array += displayPosOrder(node->left);
            array += displayPosOrder(node->right);
            array += to_string(node->data) + " ";
            return array;
        }

        string displayInOrder(NodeBT<T>* node){
            string array;
            if(node == nullptr) return "";
            array += displayInOrder(node->left);
            array += to_string(node->data) + " ";
            array += displayInOrder(node->right);
            return array;
        }
        
        string displayPreOrder(NodeBT<T>* node){
            string array;
            if(node == nullptr) return "";
            array += to_string(node->data) + " ";
            array += displayPreOrder(node->left);
            array += displayPreOrder(node->right);
            return array;
        }
        
        string displayBFS(NodeBT<T>* node, int i){
            string array;

            if(node == nullptr) return "";
            if(profundidad(node) == i) array += to_string(node->data) + " ";

            array += displayBFS(node->left, i);
            array += displayBFS(node->right, i);
            return array;
        }

        void successor(T value,NodeBT<T>* node,T& result){
            if(node == nullptr) return;
            if(value > node->data)
                successor(value,node->right,result);
            else if(value < node->data){
                result = node->data;
                successor(value,node->left,result);
            }
            else if(node->right != nullptr)
                result = minValue(node->right);
        }
        
        void predecessor(T value,NodeBT<T>* node,T& result){
            if(node == nullptr) return;
            if(value < node->data)
                predecessor(value,node->left,result);
            else if(value > node->data){
                result = node->data;
                predecessor(value,node->right,result);
            }
            else if(node->right != nullptr)
              result = minValue(node->left);
        }

        int profundidad(NodeBT<T>* node){
            int profundidad = 0;
            NodeBT<T>* temp = root;
            while(temp != nullptr){
                if(temp==node) return profundidad;
                if(node->data < temp->data){
                    temp = temp->left;
                    profundidad++;
                }
                else if(node->data > temp->data){
                    temp = temp->right;
                    profundidad++;
                }
            }
        }

        int height(NodeBT<T>* node){
           int altura_i=0;
           int altura_d=0;
            if(node == nullptr) return 0; 
            altura_i += height(node->left);
            altura_d += height(node->right);
            if(node->left==nullptr && node->right == nullptr) return 0;
            if(altura_i>altura_d) return (altura_i + 1);  
            if(altura_i<altura_d) return (altura_d + 1);  
            if(altura_i == altura_d) return (altura_i + 1);  
        }

        bool isBalanced(NodeBT<T>* &node){

            bool balanceado = true;
            if (node->left != nullptr && balanceado == true){
                balanceado = isBalanced(node->left);
            }
            if (node->right != nullptr && balanceado == true){
                balanceado = isBalanced(node->right);
            }
            
            if (balanceado == false) return false;

            int alturaIzq=0;
            if(node->left == nullptr) alturaIzq = -1;
            else alturaIzq = height(node->left);
            
          int alturaDer = 0;
            if(node->right == nullptr) alturaDer = -1;
          else alturaDer = height(node->right);
            
            if(abs(alturaIzq - alturaDer) > 1) return false;
            else return true;
            
        } 

        void remove(NodeBT<T>* node, NodeBT<T>* padre, T value){  
            if (node == nullptr) throw("No existe el valor a eliminar\n");
            
            if ( value > node->data) remove(node->right, node, value);
            else if (value < node->data) remove(node->left, node, value);
            else{
                if (node->left && node->right){
                    // Hallar el minimo valor del sub-arbol derecho
                    // Asignas el nuevo valor
                    NodeBT<T>* aux = padreDelMinValue(node->right);
                     T auxData = node->data;
                    if (aux->left == nullptr){
                        node->data = aux->data;
                        aux->data = auxData;
                        remove(aux, node, auxData);// eliminas el minValor
                    }
                    else{
                        node->data = aux->left->data;
                        aux->left->data = auxData;
                        remove(aux->left, aux, auxData);// eliminas el minValor
                    }
                }
                else if (node->left){
                    //enlazar padre con nieto
                    if (padre->left->data == node->data) padre->left = node->left;// posible error
                    else padre->right = node->left;
                    destruirNodo(node);// eliminas el nodo que quedó aislado        
                }
                else if (node->right){
                    //enlazar padre con nieto
                    if (padre->left->data == node->data) padre->left = node->right;// posible error
                    else padre->right = node->right;                  
                    destruirNodo(node);// eliminas el nodo que quedó aislado        
                }
                else{
                    if (padre->left->data == node->data) padre->left = nullptr;// posible error
                    else padre->right = nullptr;
                }
                    
            }
            
        }

        void buildFromOrderedArray(T *array, int n, int izq, int der, NodeBT<T>*& nodo){// dado un array ordenado construir un arbol binario balanceado
            if(n == 0) return;
            else if(n != 1){
                int p = n/2 + izq;
                nodo = new NodeBT<T>(array[p]);
                int nI = p - izq;
                int nD = der - p;
                buildFromOrderedArray(array, nI, izq, p - 1, nodo->left);
                buildFromOrderedArray(array, nD, p + 1, der, nodo->right);
            }
            else if (n == 1){
                nodo = new NodeBT<T>(array[izq]);//puede ser izq o der, ambos apuntan al mismo index
            }
            
        }

        void destruirNodo(NodeBT<T>* node){
            node->left = nullptr;
            node->right = nullptr;
            delete node;
        }


}; 