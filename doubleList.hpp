#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

template <typename N>
struct Node {
    N data;
    Node<N>* next;
    Node<N>* prev;

    Node () {
        next = prev = nullptr;
    }

    Node(N value) {
        data = value;
        next = prev = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }
};

template <typename T>
class DoubleList {
private:
    Node<T>* head;
    Node<T>* tail;
    int nodes;
public:
    DoubleList() {
        head = nullptr;
        tail = nullptr;
        nodes = 0;
    }

    ~DoubleList() {
		clear();
		delete this->head;
    }

	bool find(string value){
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == value) return true;
			temp = temp->next;
		}
		return false;
	}

	T front() {
		return this->head->data;
	}

	T back() {
		return this->tail->data;
	}

	void push_front(T data) {
		Node<T>* nuevo = new Node<T>(data);
		if (this->head == nullptr) {
			this->head = this->tail = nuevo;
		}
		else {
			nuevo->next = this->head;
			this->head->prev = nuevo;
			this->head = nuevo;
		}
		this->nodes++;
	}

	void push_back(T data) {
		Node<T>* nuevo = new Node<T>(data);
		if (this->head == nullptr) {
			this->head = this->tail = nuevo;
		}
		else {
			this->tail->next = nuevo;
			nuevo->prev = this->tail;
			this->tail = nuevo;
		}
		this->nodes++;
	}

	T pop_front() {
		T temp;
		if (this->nodes == 0) throw ("No existen elementos a borrar");
		else if (this->nodes == 1)
		{
			temp = this->head->data;
			this->head->killSelf();
			this->head = this->tail = nullptr;
		}
		else
		{
			temp = this->head->data;
			this->head = this->head->next;
			delete this->head->prev;
			this->head->prev = nullptr;
		}
		this->nodes--;

		return temp;
	}

	T pop_back() {
		T temp;
		if (this->nodes == 0) throw ("No existen elementos a borrar");
		else if (this->nodes == 1)
		{
			temp = this->tail->data;
			this->tail->killSelf();
			this->head = this->tail = nullptr;
		}
		else
		{
			temp = this->tail->data;
			this->tail = this->tail->prev;
			delete this->tail->next;
			this->tail->next = nullptr;
		}
		this->nodes--;

		return temp;
	}

	void insert(T data, int pos) {
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
			nuevo->next->prev = nuevo;
			nuevo->prev = temp;
			//delete temp;
			//Como debería borrar al temp?
		}
	}

	bool remove(int pos) {
		if (pos < 1 || pos > this->nodes) return false;
		else if (pos == 1) {
			pop_front();
		}
		else if (pos == this->nodes) {
			pop_back();
		}
		else {
			Node<T>* temp = this->head;
			for (int i = 1; i < pos - 1; i++) {
				temp = temp->next;
			}
			Node<T>* temp1 = temp->next;
			temp->next = temp1->next;
			temp1->next->prev = temp;
			delete temp1;//revisar delete
			this->nodes--;
		}
		return true;
	}

	T& operator[](int pos) {//se puede mejorar (que pasa si el arreglo es de 100000)
		Node<T>* temp = this->head;
		for (int i = 0; i < pos; i++) {
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

		if (this->head != nullptr){
			this->head->killSelf();
			this->head = nullptr;
			this->nodes = 0;
		}
	}

	void imprimir_registros(){
        Node<T>* temp = head;
        while (temp != nullptr){
            cout << temp->data;
            temp = temp->next;
        }
    }


};