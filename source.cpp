#include "doubleList.hpp"
#include "BSTseguridad.hpp"
#include <stdlib.h>

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

struct BlockChain {
    string usuario;
    string hashcode;
    string prevHashCode;
    DoubleList<transaccion> data;

    BlockChain() {
    }

    BlockChain(string _usuario) {
        usuario = _usuario;
    }

    //BlockChain(string _usuario) {
    //    usuario = _usuario;
    //}

    BlockChain(string _usuario, string _prevHashCode) {
        usuario = _usuario;
        prevHashCode = _prevHashCode;
    }

    friend void operator << (ostream& o, BlockChain& b){
        b.data.imprimir_registros();
    }

    friend bool operator < (BlockChain& b1, BlockChain& b2){
        if (b1.hashcode < b2.hashcode) return true;
        else return false;
    }

    friend bool operator > (BlockChain& b1, BlockChain& b2){
        if (b1.hashcode > b2.hashcode) return true;
        else return false;
    }

    void Hashing() {
		int aux = 0;
	    int aux2 = 0;
	    int aux3 = 0;
	    string t;
	    int j = 0;
	    int num;
	    t.resize(11);

	    for (int i = 0; i < usuario.length(); ++i) {
		    aux = aux + (int)usuario[i];//suma todos los ascii del usuario	
	    }
	    for (int i = 0; i < 1; ++i) {
            string s = data[i].receptor;
            aux2 = aux2 + (int)s[0];//suma los ascii de la primera letra de cada persona
	    }
	    for (int i = 0; i < 1; ++i) {
            double s = data[i].monto;
		    aux3 = aux3 + (int)s;//suma los montos 		
	    }

	    for (int i = 0; i < 11; ++i) {
		
		    if (i < 5) {//Condicional para insertar solo la parte del usuario
			    num = aux + (int)prevHashCode[j];
		    }
		    else if (5 <= i && i < 10) {//Condicional para insertar solo la parte del receptor
			    num = aux2 + (int)prevHashCode[j];
		    }
		    else {//Condicional para insertar solo la parte del monto
			    num = aux3 + (int)prevHashCode[j];
		    }

            // Condicionales para realizar un hash estable que depende del prevhash y de los datos del bloque
            //Se inserta el char en la pos i del hash
            if (num % 2 == 0 && (int)prevHashCode[j] %2 == 0) {
				    num = 48 + num % 10;
				    t[j] = char(num);
			}else if(num % 2 == 0 && (int)prevHashCode[j] % 2 != 0){
				    num = 65 + num % 25;
				    t[j] = char(num);
			}else if (num % 2 != 0 && (int)prevHashCode[j] % 2 != 0) {
				    num = 97 + num % 25;
				    t[j] = char(num);
			}else if (num % 2 != 0 && (int)prevHashCode[j] % 2 == 0) {
				    num = 35 + num % 4;
				    t[j] = char(num);
			}
			    ++j;
		
	    }

        hashcode = t;//Se asigna el valor al hash
    }
};


    



void leer_archivo(DoubleList<BlockChain>& lista){

		ifstream arcLec("datos.txt");
		string registro,campo;
		string emisor, receptor;
		double monto;
    	if (arcLec.is_open()){
    	    while(getline(arcLec,registro)){
    		    stringstream am(registro);
    		    getline(am,campo,'|');
    		    monto = stod(campo);
    		    getline(am,campo,'|');
    		    emisor = campo;
    		    getline(am,campo);
    		    receptor = campo;

                lista.push_back(emisor);
                int ultimo = lista.size();
                lista[ultimo - 1].data.push_back(transaccion(emisor, monto, receptor));

    		    //cout<<monto<<"|"<<emisor<<"|"<<receptor<<"\n";
    		}
    		arcLec.close();
    	}
}


int main(){

    DoubleList<BlockChain> listaBlockChains;
    BSTree<BlockChain> arbolBlockChains;
    BSTree<BlockChain> arbolBlockChains1;
    BSTree<BlockChain> arbolBlockChains2;
    BSTree<BlockChain> arbolBlockChains3;
    short op;
    bool seleccion = false;
    int criterio;
    char regresar;
    do
    {
        system("cls");
        cout << ":::::::::MENU::::::::::\n";
        cout << "1. Crear nuevo usuario(BlockChain)\n";
        cout << "2. Cargar datos\n";
        cout << "3. Insertar registro\n";
        cout << "4. Imprimir transacciones\n";
        cout << "5. Imprimir arbol de seguridad\n";
        cout << "6. Ordenar la Cadena de BlockChains en base a un criterio\n";
        cout << "7. Salir\n";
        cout << "Opcion: "; cin >> op;
        
        if (op == 1){
            string nombre;
            int ultimo = listaBlockChains.size();
            cout << "Ingresar nombre del blockChain: ";
            cin >> nombre;
            BlockChain nuevo;
            nuevo.usuario = nombre;
            if(listaBlockChains.size() != 0){
                string prevHash = listaBlockChains[ultimo-1].prevHashCode;
                nuevo.prevHashCode = prevHash;
            }

            listaBlockChains.push_back(nuevo);

            arbolBlockChains.insert(nuevo);

        }
        else if (op == 2){
            leer_archivo(listaBlockChains);
            
           
        }
        else if (op == 3){
            string emisor, receptor;
            double monto;
            cout << "Ingrese el nombre del emisor: ";
            cin >> emisor;
            cout << "Ingrese el nombre del receptor: ";
            cin >> receptor;
            cout << "Ingrese el monto: ";
            cin >> monto;

            int ultimo = listaBlockChains.size();
            listaBlockChains[ultimo - 1].data.push_back(transaccion(emisor, monto, receptor));

            arbolBlockChains[0].data.push_back(transaccion(emisor, monto, receptor));
        }
        else if (op == 4){
            listaBlockChains.imprimir_registros();
            cout << "Desea volver al menu?: ";
            cin >> regresar;
            if (regresar == 'n') op = 7;
        }
        else if (op == 5){
            arbolBlockChains.display();
            cout << "Desea volver al menu?: ";
            cin >> regresar;
            if (regresar == 'n') op = 7;
        }
        
        
    } while (op != 7);
    
    
    


}
/*
void Hashing1(double montos[], string usuario, string receptores[], string prevhash) {
	int aux = 0;
	int aux2 = 0;
	int aux3 = 0;
	string t;
	float n = usuario.length() / 5;
	int j = 0;
	int num;
	t.resize(11);
	for (int i = 0; i < usuario.length(); ++i) {

		aux = aux + (int)usuario[i];//suma todos los ascii del usuario
		if ((int)(n * j) == i) {

			num = aux + (int)prevhash[j];
			if (num % 2 == 0) {
				num = 48 + num % 10;
				t[j] = char(num);
			}
			else {
				num = 65 + num % 25;
				t[j] = char(num);
			}
			++j;
		}
	}
	j = 0;
	n = 5 / 5;
	for (int i = 0; i < 5; ++i) {
		aux2 = aux2 + (int)receptores[i][0];//suma los ascii de la primera letra de cada persona

		if ((int)(n * j) == i) {

			num = aux2 + (int)prevhash[j + 5];
			if (num % 2 == 0) {
				num = 48 + num % 10;
				t[j + 5] = char(num);
			}
			else {
				num = 65 + num % 25;
				t[j + 5] = char(num);
			}
			++j;
		}
	}
	for (int i = 0; i < 5; ++i) {
		aux3 = aux3 + (int)montos[i];//suma los montos 		
	}
	num = aux3 + (int)prevhash[10];
	if (num % 2 == 0) {
		num = 48 + num % 10;
		t[10] = char(num);
	}
	else {
		num = 65 + num % 25;
		t[10] = char(num);
	}

	for (int i = 0; i < 11; ++i) {
		cout << t[i] << " ";
	}

}
*/
