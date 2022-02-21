//#include "nodeLista.hpp"
//#include "blockChain.hpp"

#include <iostream>
#include <string>
using namespace std;

template <typename N>
struct Node1 {
    N data;
    Node1<N>* next;
    Node1<N>* prev;

    Node1 () {
        next = prev = nullptr;
    }

    Node1(N value) {
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
    Node1<T>* head;
    Node1<T>* tail;
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

	T front() {
		return this->head->data;
	}

	T back() {
		return this->tail->data;
	}

	void push_front(T data) {
		Node1<T>* nuevo = new Node1<T>(data);
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
		Node1<T>* nuevo = new Node1<T>(data);//nodo de tipo T
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
			Node1<T>* nuevo = new Node1<T>(data);
			Node1<T>* temp = this->head;
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
			Node1<T>* temp = this->head;
			for (int i = 1; i < pos - 1; i++) {
				temp = temp->next;
			}
			Node1<T>* temp1 = temp->next;
			temp->next = temp1->next;
			temp1->next->prev = temp;
			delete temp1;//revisar delete
			this->nodes--;
		}
		return true;
	}

	T& operator[](int pos) {//se puede mejorar (que pasa si el arreglo es de 100000)
		Node1<T>* temp = this->head;
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
		if (this->head == nullptr) delete this->head;
		else
		{
			this->head->killSelf();
			this->head = nullptr;
			this->nodes = 0;
		}
	}
/*
	void sort() {
		int tamanio = size();
		Node1<T>* a1, *a2;
		for (int i = 1; i <= tamanio; i++)
		{
			a1 = this->head; a2 = a1->next;
			for (int j = 1; j <= tamanio; j++)
			{
				if (a1->data > a2->data)
				{
					if (a1 == this->head)
					{
						a2->prev = nullptr;
						a1->next = a2->next;
						a1->prev = a2;
						a2->next = a1;
						this->head = a2;
					}
					else if (a2->next == nullptr)
					{
						a1->prev->next = a2;
						a2->prev = a1->prev;
						a1->next = nullptr;
						a1->prev = a2;
						a2->next = a1;
					}
					else
					{
						a1->prev->next = a2;
						a2->next->prev = a1;
						a2->prev = a1->prev;
						a1->next = a2->next;
						a1->prev = a2;
						a2->next = a1;
					}
				}
				else a1 = a1->next;

				a2 = a1->next;
			}
		}
	}
*/
/*	
    bool is_sorted() {
		int num = -1;
		Node1<T>* temp = this->head;
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
*/
    T& ultimo_blockChain(){
        return tail->data;
    }

    void imprimir_registros(){
        Node1<T>* temp = head;
        while (temp != nullptr){
            cout << temp->data;
            temp = temp->next;
        }
        
    }

    void retornar_block_chain(int index){
        Node1<T>* temp = head;
        //int cant = 0;
        //while (cant < index)
        //    temp = temp->next;
        //
        //return tail->data;
        while (temp != nullptr){
            cout << temp->data;
        }
        
    }

};