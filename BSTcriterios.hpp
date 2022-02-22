#include "string"
#include <math.h>
#include <iostream>
#include "transaccion.hpp"
using namespace std;

template <typename N>
struct NodeBTFiltro {
    transaccion data;
    NodeBTFiltro<N>* left;
    NodeBTFiltro<N>* right;

    NodeBTFiltro() {
        left = right = nullptr;
    }

    NodeBTFiltro(N value) {
        data = value;
        left = right = nullptr;
    }

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};

//template <typename T, typename C>  //T: BlockChain - C: criterio(string "CantTran", string "usuario", string "MontoTotal" )
template <typename T>
class BSTreeFiltro {
    private:
        NodeBTFiltro<T>* root;    
        int contNodos;
    public:
        BSTreeFiltro(): root(nullptr),contNodos(0) {}

        //T& retornar_root(){
        //    return root->data;
        //}

        T& operator[](int pos) {
		    return root->data;
	    }

        void insertMonto(transaccion trans, double monto){
            contNodos++;
            insertMonto(root,trans,monto);
        }
        
        //void insert(T blockChain, C criterio){
        //      contNodos++;
        //      if (criterio == "CantTran") insertCantTran(root, blockChain);
        // }

        void insertReceptor(transaccion trans, string receptor){
            contNodos++;
            insertReceptor(root,trans,receptor);
        }

        void insertUsuario(transaccion trans, string usuario){
            contNodos++;
            insertUsuario(root,trans,usuario);
        }
        	
        void filtroRangoMontos(double montoIni, double montoFin){
            filtroRangoMontos(root, montoIni, montoFin);
        }	

        void filtroUsuario(string usuario){
            filtroUsuario(root, usuario);
        }

        void filtroReceptor(string receptor){
            filtroReceptor(root, receptor);
        }

        int size(){
            return contNodos;
        }

        void clear(){
            contNodos=0;
            root->killSelf();
            root = nullptr;
        }
        
        ~BSTreeFiltro(){
            clear();
        } //Destructor del arbol

        private:
        //INSERTAR MONTOS

        void insertMonto(NodeBTFiltro<T>* &node, transaccion transaccion, double criterio){
	    	if(node == nullptr)
	    		node = new NodeBTFiltro<T>(transaccion);
	    	else if(criterio < node->data.monto)
	    		insertMonto(node->left, transaccion, criterio);
	    	else if(criterio >= node->data.monto)
	    		insertMonto(node->right, transaccion, criterio);
	    }

        //void inserCantTran(NodeBTFiltro<T>*& node, T BlockChain){
        //    if (node == nullptr)
        //        node = new NodeBTFiltro<T>(BlockChain);
        //    else if (BlockChain < node.data)
        //       inserCantTran(node->left, BlockChain);
        //    else if (BlockChain >= node.data)
        //        inserCantTran(node->right, BlockChain);
        //}

        //INSERTAR USUARIOS

        void insertUsuario(NodeBTFiltro<T>* &node, transaccion transaccion, string criterio){
	    	if(node == nullptr)
	    		node = new NodeBTFiltro<T>(transaccion);
	    	else if(criterio < node->data.emisor)
	    		insertUsuario(node->left, transaccion, criterio);
	    	else if(criterio >= node->data.emisor)
	    		insertUsuario(node->right, transaccion, criterio);
	    }

        //INSERTAR RECEPTOR

        void insertReceptor(NodeBTFiltro<T>* &node, transaccion transaccion, string criterio){
	    	if(node == nullptr)
	    		node = new NodeBTFiltro<T>(transaccion);
	    	else if(criterio < node->data.receptor)
	    		insertReceptor(node->left, transaccion, criterio);
	    	else if(criterio >= node->data.receptor)
	    		insertReceptor(node->right, transaccion, criterio);
	    }

        //FILTRO RANGO DE PRECIOS

        void filtroRangoMontos(NodeBTFiltro<T>* node, double montoIni, double montoFin){
	        if(node == nullptr)
                return;
            else if(montoIni <= node->data.monto && node->data.monto <= montoFin){
                cout << node->data;
                filtroRangoMontos(node->right,montoIni,montoFin);
                filtroRangoMontos(node->left,montoIni,montoFin);
            }
	        else if(montoFin < node->data.monto)
	            filtroRangoMontos(node->left,montoIni,montoFin);
	        else if(montoIni > node->data.monto)
	            filtroRangoMontos(node->right,montoIni,montoFin);
            return;
	    }
        

        //FILTRO USUARIO

        void filtroUsuario(NodeBTFiltro<T>* node, string usuario){
	        if(node == nullptr)
                return;
	        else if(usuario < node->data.emisor)
	            filtroUsuario(node->left, usuario);
	        else if(usuario > node->data.emisor)
	            filtroUsuario(node->right, usuario);
	        else if(usuario == node->data.emisor){
                cout << node->data;
                filtroUsuario(node->right, usuario);
            }
            return;
	    }

        //FILTRO RECEPTOR

        void filtroReceptor(NodeBTFiltro<T>* node, string recep){
	        if(node == nullptr)
                return;
	        else if(recep < node->data.receptor)
	            filtroReceptor(node->left, recep);
	        else if(recep > node->data.receptor)
	            filtroReceptor(node->right, recep);
	        else if(recep == node->data.receptor){
                cout << node->data;
                filtroReceptor(node->right, recep);
            }
            return;
	    }


}; 