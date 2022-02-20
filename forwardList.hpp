#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node() {
        next = nullptr;
    }

    Node(T value) {
        data = value;
        next = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }
};

template <typename T>
class ForwardList {
private: 
    Node<T>* head;
    int nodes;
public:
    ForwardList(){
		head = nullptr;
		nodes = 0;
    }

    ~ForwardList() { 
		clear();
		delete this->head;
    }

    T front() {
        return this->head->data;
    }

    T back() {
        Node<T>* aux = this->head;
        while (aux->next != nullptr)
            aux = aux->next;

        return aux->data;
    }

    void push_front(T data) {//esta
        Node<T>* nuevo = new Node<T>(data);
	    if (this->head == nullptr) {
		    this->head = nuevo;
	    }
	    else {
		    nuevo->next = this->head;
		    this->head = nuevo;
	    }
		this->nodes++;
    }

    void push_back(T data) {//esta
		Node<T>* nuevo = new Node<T>(data);
        if (this->head == nullptr) {
			this->head = nuevo;
	    }
	    else {
	    	Node<T>* temp = this->head;
		    while (temp->next != nullptr) { temp = temp->next; }
	    	temp->next = nuevo;
	    }
		this->nodes++;
    }

    T pop_front() {//esta...
        Node<T>* temp = this->head;
		if (this->nodes == 0) throw ("No hay elementos para eliminar");
        else if(this->nodes == 1){
	    	this->head = nullptr;
    	}
	    else {	
		    this->head = temp->next;
			temp->next = nullptr; //no sé si esto es necesario;
	    }
		this->nodes--;
		return temp->data;
    }

    T pop_back() {//esta
		Node<T>* temp = this->head;
		T temp2;
		if (this->nodes == 0) throw ("No hay elementos para eliminar");
        else if (this->nodes == 1) {
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
		this->nodes--;
		return temp2;
    }

    void insert(T data, int pos) {//esta
		if (pos < 1) throw ("No existe esa posicion");
        else if (pos == 1) {
		    push_front(data);
	    }
	    else if (pos == this->nodes + 1) {
		    push_back(data);
	    }
	    else {
			Node<T>* nuevo = new Node<T>(data);
			Node<T>* temp = this->head;
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
		if (pos < 1 || pos > this->nodes) return false;
		else if (pos == 1) {
			pop_front();
    	}
	    else if (pos == this->nodes) {
			pop_back();
	    }
    	else {
		    Node<T>* temp = this->head;	
	    	for (int i = 1; i < pos - 1; i++) {//antes: int i = 0; i < pos - 1; i++
	    		temp = temp->next;
	    	}
			Node<T>* temp1 = temp->next;
	    	temp->next = temp->next->next;
	    	temp1->next = nullptr;//es necesario
	    	delete temp1;
	    	this->nodes--;
	    }
        return true;
    }

    T& operator[](int pos) {
        Node<T>* temp = this->head;
		for (int i = 1; i < pos; i++) {
			temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty() {
		return (this->head == nullptr) ? true : false;
    }

    int size() {
        return this->nodes;
    }

    void clear() {
		if (this->head == nullptr) delete this->head;
		else
		{
			this->head->killSelf();
			this->head = nullptr;
			this->nodes = 0;
		}
    }

    void sort() {
		int tamanio = size();
		Node<T>* a1, *a2, *a3;
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
	    Node<T>* temp = this->head;
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

    void reverse() {
        Node<T>* temp_d = this->head;
	    Node<T>* temp_i = nullptr;
    	Node<T>* temp_c = nullptr;
    	while (temp_d != nullptr) {//antes era temp_i
	    	temp_i = temp_c;
	    	temp_c = temp_d;
	    	temp_d = temp_d->next;
	    	temp_c->next = temp_i;	
	    }
	    this->head = temp_c;//antes era temp_i
		
    }

	void display(){
		Node<T>* temp = head;
        while (temp != nullptr)
			cout << temp->data;
	}

};
