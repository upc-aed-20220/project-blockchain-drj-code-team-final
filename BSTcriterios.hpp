#include "string"
#include <math.h>
#include <iostream>
using namespace std;

struct transaccion{
	string emisor;
	double monto;
    string receptor;
	transaccion(){}
	transaccion(string _emisor, double _monto, string _receptor)
    {emisor = _emisor; monto = _monto; receptor = _receptor;}
    
    friend ostream &operator<<(ostream& o, transaccion& t) {
        o << t.monto << " from " << t.emisor << " to " << t.receptor << "\n";
        return o;
    }
}; 

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

        void insertMonto(transaccion trans, T monto){
            contNodos++;
            insertMonto(root,trans,monto);
        }

        void insertReceptor(transaccion trans, T receptor){
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

        void filtroReceptor(T receptor){
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

        void insertMonto(NodeBT<T>* &node, T transaccion, T criterio){
	    	if(node == nullptr)
	    		node = new NodeBT<T>(transaccion);
	    	else if(criterio < node->data.monto)
	    		insert(node->left, transaccion, criterio);
	    	else if(criterio >= node->data.monto)
	    		insert(node->right, transaccion, criterio);
	    }

        //INSERTAR USUARIOS

        void insertUsuario(NodeBT<T>* &node, T transaccion, T criterio){
	    	if(node == nullptr)
	    		node = new NodeBT<T>(transaccion);
	    	else if(criterio < node->data.emisor)
	    		insert(node->left, transaccion, criterio);
	    	else if(criterio >= node->data.emisor)
	    		insert(node->right, transaccion, criterio);
	    }

        //INSERTAR RECEPTOR

        void insertReceptor(NodeBT<T>* &node, T transaccion, T criterio){
	    	if(node == nullptr)
	    		node = new NodeBT<T>(transaccion);
	    	else if(criterio < node->data.receptor)
	    		insert(node->left, transaccion, criterio);
	    	else if(criterio >= node->data.receptor)
	    		insert(node->right, transaccion, criterio);
	    }

        //FILTRO RANGO DE PRECIOS

        void filtroRangoMontos(NodeBT<T>* node, T montoIni, T montoFin){
	        if(node == nullptr)
                return;
            else if(montoIni <= node->data.monto && node->data.monto <= montoFin){
                cout << node->data;
                filtroRangoMontos(node->right, T montoIni, T montoFin);
                filtroRangoMontos(node->left, T montoIni, T montoFin);
            }
	        else if(montoFin < node->data.monto)
	            filtroRangoMontos(node->left, T montoIni, T montoFin);
	        else if(montoIni > node->data.monto)
	            filtroRangoMontos(node->right, T montoIni, T montoFin);
            return;
	    }

        //FILTRO USUARIO

        void filtroUsuario(NodeBT<T>* node, T usuario){
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

        void filtroReceptor(NodeBT<T>* node, T recep){
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