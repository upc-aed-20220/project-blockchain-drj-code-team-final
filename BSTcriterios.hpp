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
        void insertMonto(NodeBTFiltro<T>* &node, transaccion transaccion, double criterio){ // ---> Log n
	    	if(node == nullptr) // ---> 1
	    		node = new NodeBTFiltro<T>(transaccion); // ---> 2
	    	else if(criterio < node->data.monto) // ---> 3
	    		insertMonto(node->left, transaccion, criterio); // ---> Log n
	    	else if(criterio >= node->data.monto) // ---> 3
	    		insertMonto(node->right, transaccion, criterio);// ---> Log n
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
        void insertUsuario(NodeBTFiltro<T>* &node, transaccion transaccion, string criterio){ // ---> Log n
	    	if(node == nullptr) // ---> 1
	    		node = new NodeBTFiltro<T>(transaccion); // ---> 2
	    	else if(criterio < node->data.emisor) // ---> 3
	    		insertUsuario(node->left, transaccion, criterio); // ---> Log n
	    	else if(criterio >= node->data.emisor)// ---> 3
	    		insertUsuario(node->right, transaccion, criterio);// ---> Log n
	    }
        //INSERTAR RECEPTOR
        void insertReceptor(NodeBTFiltro<T>* &node, transaccion transaccion, string criterio){ // ---> Log n
	    	if(node == nullptr) // ---> 1
	    		node = new NodeBTFiltro<T>(transaccion); // ---> 2
	    	else if(criterio < node->data.receptor) // ---> 3
	    		insertReceptor(node->left, transaccion, criterio);// ---> Log n
	    	else if(criterio >= node->data.receptor) // ---> 3
	    		insertReceptor(node->right, transaccion, criterio);// ---> Log n
	    }
        //FILTRO RANGO DE PRECIOS
        void filtroRangoMontos(NodeBTFiltro<T>* node, double montoIni, double montoFin){ // ---> Log n
	        if(node == nullptr) return; // ---> 2
            else if(montoIni <= node->data.monto && node->data.monto <= montoFin){ // ---> 7 + ...
                cout << node->data; // ---> 2
                filtroRangoMontos(node->right,montoIni,montoFin); // ---> Log n
                filtroRangoMontos(node->left,montoIni,montoFin); // ---> Log n
            }
	        else if(montoFin < node->data.monto) // ---> 3
	            filtroRangoMontos(node->left,montoIni,montoFin);// ---> Log n
	        else if(montoIni > node->data.monto) // ---> 3
	            filtroRangoMontos(node->right,montoIni,montoFin);// ---> Log n
            return;// ---> 1
	    }
        //FILTRO MONTOS MENORES
        void filtroMontosMenores(NodeBTFiltro<T>* node, double mont){ // ---> Log n
	        if(node == nullptr) return; // --->2
	        else if(mont >= node->data.monto){// ---> 3
                cout << node->data;// ---> 2
                filtroMontosMenores(node->right,mont);// ---> Log n
                filtroMontosMenores(node->left,mont);// ---> Log n
            }
	        else if(mont < node->data.monto)// ---> 3
	            filtroMontosMenores(node->left,mont);// ---> Log n
            return;// ---> 1
        }
        //FILTRO MONTOS MAYORES
        void filtroMontosMayores(NodeBTFiltro<T>* node, double mont){ // ---> Log n
	        if(node == nullptr) return;// ---> 2 
	        else if(mont > node->data.monto)// ---> 3
	            filtroMontosMayores(node->right,mont);// ---> Log n
	        else if(mont <= node->data.monto){// ---> 3
                cout << node->data;// ---> 2
                filtroMontosMayores(node->right,mont);// ---> Log n 
                filtroMontosMayores(node->left,mont);// ---> Log n
            }
            return;// ---> 1
	    }
        //FILTRO USUARIO IGUAL A
        void filtroUsuarioIgualA(NodeBTFiltro<T>* node, string usuario){ // ---> Log n
	        if(node == nullptr) return;// ---> 2
	        else if(usuario < node->data.emisor)// ---> 3
	            filtroUsuarioIgualA(node->left, usuario);// ---> Log n
	        else if(usuario > node->data.emisor)// ---> 3
	            filtroUsuarioIgualA(node->right, usuario);// ---> Log n
	        else if(usuario == node->data.emisor){// ---> 3
                cout << node->data;// ---> 2
                filtroUsuarioIgualA(node->right, usuario);// ---> Log n
            }
            return;// ---> 1
	    }
        //FILTRO USUARIO INICIA CON
        void filtroUsuarioIniciaCon(NodeBTFiltro<T>* node, string usuario){ // ---> Log n
	        if(node == nullptr) return; // ---> 2

            int tam = usuario.size(); // ---> 2
            string iniciaCon = (node->data.emisor).substr(0,tam); // ---> 4

            if(usuario == iniciaCon){// ---> 2
                cout << node->data;// ---> 2
                filtroUsuarioIniciaCon(node->right, usuario);// ---> Log n
                filtroUsuarioIniciaCon(node->left, usuario);// ---> Log n
            }
	        else if(usuario < iniciaCon)// ---> 2
	            filtroUsuarioIniciaCon(node->left, usuario);// ---> Log n
	        else if(usuario > iniciaCon)// ---> 2
	            filtroUsuarioIniciaCon(node->right, usuario);// ---> Log n
            return;// ---> 1
	    }
        //FILTRO RECEPTOR IGUAL A
        void filtroReceptorIgualA(NodeBTFiltro<T>* node, string recep){ // --->
	        if(node == nullptr) return;
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
	        if(node == nullptr) return;// ---> 2

            int tam = recep.size();// ---> 2
            string iniciaCon = (node->data.receptor).substr(0,tam);// ---> 4

	        if(recep < iniciaCon)// ---> 2
	            filtroReceptorIniciaCon(node->left, recep);// ---> Log n
	        else if(recep > iniciaCon)// ---> 2
	            filtroReceptorIniciaCon(node->right, recep);// ---> Log n
	        else if(recep == iniciaCon){// ---> 2
                cout << node->data;// ---> 2
                filtroReceptorIniciaCon(node->right, recep);// ---> Log n
            }
            return;// ---> 1
	    }


}; 