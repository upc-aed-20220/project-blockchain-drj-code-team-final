#include <iostream>
#include "blockChain.hpp"

template <typename TK,typename TV1, typename TV2>
class CadenaBlockChain {
private:
    struct Entry{
		TK key;
		TV1 value1;
        TV2 value2;
        //TV3 prevHashcode;
		//size_t hashcode;
		Entry(){}
		Entry(TK _key,TV1 _value1, TV2 _value2){key = _key; value1 = _value1; value2 = _value2;}
		friend ostream& operator << (ostream& o, Entry& n) {
        o << n.key << ": " << n.value;
    	}
	}; 
    Block<Entry>* tail;
    int cantBloques;

public:
    CadenaBlockChain(){
        tail = nullptr;
        cantBloques = 0;
    }

    ~CadenaBlockChain() {                                                 
		clear();
		delete this->head;
    }

    Entry front() {
        return this->head->data;
    }

    Entry back() {
        Block<Entry>* aux = this->head;
        while (aux->next != nullptr)
            aux = aux->next;

        return aux->data;
    }

    //void push_front(Entry data) {//esta
    //    Block<Entry>* nuevo = new Block<Entry>(data);
	//    if (this->head == nullptr) {
	//	    this->head = nuevo;
	//    }
	//    else {
	//	    nuevo->next = this->head;
	//	    this->head = nuevo;
	//    }
	//	this->cantBloques++;
    //}

    void push_back(string data) {//esta
	
        Block<Entry>* nuevo = new Block<Entry>(data);

		nuevo.Hash = "0000000"; //funcion que cree el hash segun contenido
	    if (tail == nullptr) {
            nuevo.prevHash = "0000000";
        }
	    else {
			nuevo.prevHash = tail.Hash;
	    }
		tail = nuevo;
		cantBloques++;
    }

    //void push_back(Entry data) {//esta
	//	Block<Entry>* nuevo = new Block<Entry>(data);
    //    if (this->head == nullptr) {
	//		this->head = nuevo;
	//    }
	//    else {
	//    	Block<Entry>* temp = this->head;
	//	    while (temp->next != nullptr) { temp = temp->next; }
	//    	temp->next = nuevo;
	//    }
	//	this->cantBloques++;
    //}

    Entry pop_front() {//esta...
        Block<Entry>* temp = this->head;
		if (this->cantBloques == 0) throw ("No hay elementos para eliminar");
        else if(this->cantBloques == 1){
	    	this->head = nullptr;
    	}
	    else {	
		    this->head = temp->next;
			temp->next = nullptr; //no sé si esto es necesario;
	    }
		this->cantBloques--;
		return temp->data;
    }

    Entry pop_back() {//esta
		Block<Entry>* temp = this->head;
		Entry temp2;
		if (this->cantBloques == 0) throw ("No hay elementos para eliminar");
        else if (this->cantBloques == 1) {
			temp2 = this->head->data;
			this->head = nullptr;
	    }
	    else {
			
		    while (temp->next->next != nullptr){
			    temp = temp->next;
		    }
			temp2 = temp->next->data;
	    	delete temp->next;
	    	temp->next = nullptr;
	    }
		this->cantBloques--;
		return temp2;
    }

    void insert(Entry data, int pos) {//esta
		if (pos < 1) throw ("No existe esa posicion");
        else if (pos == 1) {
		    push_front(data);
	    }
	    else if (pos == this->cantBloques + 1) {
		    push_back(data);
	    }
	    else {
			Block<Entry>* nuevo = new Block<Entry>(data);
			Block<Entry>* temp = this->head;
	    	for (int i = 1; i < pos - 1; i++) {
	    		temp = temp->next;
	    	}
	    	nuevo->next = temp->next;
		    temp->next = nuevo;
			//delete temp;
			//Como debería borrar al temp?
	    }
    }

    bool remove(int pos) {//esta... revisar orden de los ifs y agregar el retorno
		if (pos < 1 || pos > this->cantBloques) return false;
		else if (pos == 1) {
			pop_front();
    	}
	    else if (pos == this->cantBloques) {
			pop_back();
	    }
    	else {
		    Block<Entry>* temp = this->head;	
	    	for (int i = 1; i < pos - 1; i++) {//antes: int i = 0; i < pos - 1; i++
	    		temp = temp->next;
	    	}
			Block<Entry>* temp1 = temp->next;
	    	temp->next = temp->next->next;
	    	temp1->next = nullptr;//es necesario
	    	delete temp1;
	    	this->cantBloques--;
	    }
        return true;
    }

    Entry& operator[](int pos) {
        Block<Entry>* temp = this->head;
		for (int i = 1; i < pos; i++) {
			temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty() {
		return (this->head == nullptr) ? true : false;
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

    void sort() {
		int tamanio = size();
		Block<Entry>* a1, *a2, *a3;
		for (int i = 1; i <= tamanio; i++)
		{
			a1 = this->head; a2 = a1->next; a3 = this->head;
			for (int j = 1; j <= tamanio; j++)
			{
				if (a1->data > a2->data)
				{
					if (a1 == this->head)
					{
						a1->next = a2->next;
						a2->next = a1;
						this->head = a2;
						a3 = this->head;
					}
					else
					{
						a3->next = a2;
						a1->next = a2->next;
						a2->next = a1;
						a3 = a3->next;
					}
				}
				else
				{
					a1 = a1->next;
					if (j != 1)a3 = a3->next;
				}

				a2 = a1->next;
			}
		}
    }

    bool is_sorted() {
        int num = -1;
	    Block<Entry>* temp = this->head;
	    while (temp != nullptr) {
	    	if (num <= temp->data) {
			    num = temp->data;
	    	}
	    	else {
			    return false;
		    }
	    	temp = temp->next;
	    }
	    return true;
    }

    void Hashing(Block<Entry> *node){
		Block<Entry> *temp = node;
		string user = node->key;
		double monto = node->value1;
		string user2 = node->value2;

	}
	
    void updateNodo(TK emisor, TV1 v1, TV2 v2){
        Block<Entry>* aux = head;
        while (aux->)
        {
            /* code */
        }
        
    }


    std::string name() {
        return "CadenaBlockChain";
    }

};