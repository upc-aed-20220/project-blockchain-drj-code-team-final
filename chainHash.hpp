#include "blockChain.hpp"
#include "doubleList.hpp"
using namespace std;

template<typename TK, typename TV>
class ChainHash {
private:    

	DoubleList<BlockChain> listaBlockChains;

public:
    ChainHash(){
		capacity = 10; 
		array = new list<Entry>[capacity];
		size = 0;
	}

	void set(TK key, TV value){
		if(fillFactor() >= maxFillFactor) rehashing();
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		//TODO: insertar el Entry(key, value) en index, manejando colisiones
		bool colision = false;
		int recorrido = 0;

		for (int i = index; colision == false && recorrido != capacity ; i = (i+1)%capacity){
			recorrido++;
			for (int j = 0; j < array[i].size(); j++){
				if (array[i].returnDataOfNodo(j).key == key){
					array[i].returnDataOfNodo(j).value = value;
					colision = true;
					break;
				}
			}
		}
			
		if(colision == false) {
			while (array[index].size() >= 3)
				index = (index + 1)%capacity;
			array[index].push_front(Entry(key, value));
			size++;
		}
	}

	TV get(TK key){
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		int cant = 0;
		for (int i = index; cant != capacity; i = (i+1)%capacity){
			cant++;
			for (int j = 0; j < array[i].size(); j++)
				if(array[i].returnDataOfNodo(j).key == key) 
					return array[i].returnDataOfNodo(j).value;
		}
		
		throw("No se encontro el elemento\n");
	}

	int bucket_count(){
		return capacity;
	}

	int bucket_size(int i){
		return array[i].size();
	}

	void remove(TK key){
		size_t hashcode = getHashCode(key);
		int index = hashcode % capacity;
		Entry auxElem;
		int cant = 0;
		for (int i = index; cant != capacity; i = (i + 1)%capacity){
			cant++;
			for (int j = 0; j < array[i].size(); j++)
				if (array[i].returnDataOfNodo(j).key == key){
					array[i].remove(j+1);
					size--;
					return;
				}
		}
		
		throw("No existe el elemento que quieres eliminar\n");
	}

	list<Entry>& operator [](int i){
		return array[i];
	}

	TV operator [](TK key){
		return get(key);;
	}

private:
	double fillFactor(){
		return size*1.0 / (capacity * maxColision);
	}

	size_t getHashCode(TK key){
		std::hash<TK> ptr_hash;
		return ptr_hash(key);
	}

	void rehashing(){
		list<Entry> *aux = new list<Entry>[capacity * 2];
		int index;
		size_t hashcode;
		for (int i = 0; i < capacity; i++){
			while (array[i].size() > 0)
			{
				Entry elem = array[i].pop_front();
				hashcode = getHashCode(elem.key);
				index = hashcode % (capacity*2);
				if (aux[index].size() >= 3)
					index = (index + 1) % (capacity*2);
				
				aux[index].push_front(elem);
			}
		}

		capacity = capacity * 2;
		array = new list<Entry>[capacity];
		array = aux;
	}	
};