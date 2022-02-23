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

        void filtroMontosMenores(double monto){
            filtroMontosMenores(root, monto);
        }	

        void filtroMontosMayores(double monto){
            filtroMontosMayores(root, monto);
        }	

        void filtroUsuarioIgualA(string usuario){
            filtroUsuarioIgualA(root, usuario);
        }

        void filtroUsuarioIniciaCon(string usuario){
            filtroUsuarioIniciaCon(root, usuario);
        }

        void filtroReceptorIgualA(string usuario){
            filtroReceptorIgualA(root, usuario);
        }

        void filtroReceptorIniciaCon(string receptor){
            filtroReceptorIniciaCon(root, receptor);
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

        //FILTRO MONTOS MENORES

        void filtroMontosMenores(NodeBTFiltro<T>* node, double mont){
	        if(node == nullptr)
                return;
	        else if(mont >= node->data.monto){
                cout << node->data;
                filtroMontosMenores(node->right,mont);
                filtroMontosMenores(node->left,mont);
            }
	        else if(mont < node->data.monto)
	            filtroMontosMenores(node->left,mont);
            return;
	    }

        //FILTRO MONTOS MAYORES

        void filtroMontosMayores(NodeBTFiltro<T>* node, double mont){
	        if(node == nullptr)
                return;
	        else if(mont > node->data.monto)
	            filtroMontosMayores(node->right,mont);
	        else if(mont <= node->data.monto){
                cout << node->data;
                filtroMontosMayores(node->right,mont);
                filtroMontosMayores(node->left,mont);
            }
            return;
	    }
        
        //FILTRO USUARIO IGUAL A

        void filtroUsuarioIgualA(NodeBTFiltro<T>* node, string usuario){
	        if(node == nullptr)
                return;
	        else if(usuario < node->data.emisor)
	            filtroUsuarioIgualA(node->left, usuario);
	        else if(usuario > node->data.emisor)
	            filtroUsuarioIgualA(node->right, usuario);
	        else if(usuario == node->data.emisor){
                cout << node->data;
                filtroUsuarioIgualA(node->right, usuario);
            }
            return;
	    }

        //FILTRO USUARIO INICIA CON

        void filtroUsuarioIniciaCon(NodeBTFiltro<T>* node, string usuario){
	        if(node == nullptr) return;

            int tam = usuario.size();
            string iniciaCon = (node->data.emisor).substr(0,tam);

            if(usuario == iniciaCon){
                cout << node->data;
                filtroUsuarioIniciaCon(node->right, usuario);
                filtroUsuarioIniciaCon(node->left, usuario);
            }
	        else if(usuario < iniciaCon)
	            filtroUsuarioIniciaCon(node->left, usuario);
	        else if(usuario > iniciaCon)
	            filtroUsuarioIniciaCon(node->right, usuario);
            return;
	    }

        //FILTRO RECEPTOR IGUAL A

        void filtroReceptorIgualA(NodeBTFiltro<T>* node, string recep){
	        if(node == nullptr)
                return;
	        else if(recep < node->data.receptor)
	            filtroReceptorIgualA(node->left, recep);
	        else if(recep > node->data.receptor)
	            filtroReceptorIgualA(node->right, recep);
	        else if(recep == node->data.receptor){
                cout << node->data;
                filtroReceptorIgualA(node->right, recep);
            }
            return;
	    }

        //FILTRO RECEPTOR INICIA CON

        void filtroReceptorIniciaCon(NodeBTFiltro<T>* node, string recep){
	        if(node == nullptr) return;

            int tam = recep.size();
            string iniciaCon = (node->data.receptor).substr(0,tam);

	        if(recep < iniciaCon)
	            filtroReceptorIniciaCon(node->left, recep);
	        else if(recep > iniciaCon)
	            filtroReceptorIniciaCon(node->right, recep);
	        else if(recep == iniciaCon){
                cout << node->data;
                filtroReceptorIniciaCon(node->right, recep);
            }
            return;
	    }


}; 