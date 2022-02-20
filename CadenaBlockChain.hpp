#include <iostream>
#include "blockChain.hpp"
#include "BSTseguridad.hpp"

template <typename T>
class CadenaBlockChain {
private:
    
    BlockChain<T>* tail;
	BSTree<BlockChain<T>> arbol;
    int cantBloques;

public:
    CadenaBlockChain(){
        tail = nullptr;
        cantBloques = 0;
    }

    ~CadenaBlockChain() {                                                 
		clear();
		delete this->tail;
    }

    void agregar_blockChain(string user) {
	
        BlockChain<T>* nuevo = new BlockChain<T>(user);

		nuevo->Hash = "0000000"; //funcion que cree el hash segun contenido
	    if (tail == nullptr) {
            nuevo->ingresar_prevHash("0000000000");
        }
	    else {
			nuevo->ingresar_prevHash(tail->retornar_Hash());
	    }
		tail = nuevo;
		cantBloques++;

		arbol.insert(nuevo);
    }

	void agregar_registro(T transaccion){

		//BlockChain<T>*temp = arbol.find(emisor);
		//temp->data.push_front(data);

		BlockChain<T>*temp = arbol.findBlockChain(tail);
		temp->data.push_front(transaccion);

	}

	void imprimir_registros(){
		arbol.display();
	}

    int size() {
        return this->cantBloques;
    }

    void clear() {
		if (this->head == nullptr) delete this->head;
		else
		{
			this->head->killSelf();
			this->head = nullptr;
			this->cantBloques = 0;
		}
    }
/*
    void Hashing(Block<Entry> *node){
		Block<Entry> *temp = node;
		string user = node->key;
		double monto = node->value1;
		string user2 = node->value2;

        for(int = 0;i<user. )
		//lo hare en mi VS 

	}
*/

};