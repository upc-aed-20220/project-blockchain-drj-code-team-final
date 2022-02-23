#include "doubleList.hpp"
#include "BSTseguridad.hpp"
#include "BSTcriterios.hpp"
#include <stdlib.h>

//struct transaccion{
//	string emisor;
//	double monto;
//    string receptor;
//	transaccion(){}
//	transaccion(string _emisor, double _monto, string _receptor)
//    {emisor = _emisor; monto = _monto; receptor = _receptor;}
//    
//    friend ostream &operator<<(ostream& o, transaccion& t) {
//        o << t.monto << " from " << t.emisor << " to " << t.receptor << "\n";
//        return o;
//    }
//	void extraer_valores(string& _emisor, string& _receptor, double& _monto){
//		_emisor = emisor;
//		_receptor = receptor;
//		_monto = monto;
//	}
//}; 

struct BlockChain {
    string usuario; // ---> 1
    string hashcode; // ---> 1
    string prevHashCode; // ---> 1
    DoubleList<transaccion> data; //---> 1

    BlockChain() {
    }

    BlockChain(string _usuario) { //---> O(1)
        usuario = _usuario; //---> 1
    }

    BlockChain(string _usuario, string _prevHashCode) {//---> O(1)
        usuario = _usuario; //---> 1
        prevHashCode = _prevHashCode;//---> 1
    }
	
	//friend bool operator < (string& criterio, BlockChain& b){
	// if (criterio == "cantTran") {
	// b.data,size();
	//
	//
	// }
	//
	//
	//
	//
    //    if (b1.hashcode < b2.hashcode) return true;
    //    else return false;
    //}

	friend bool operator == (BlockChain& b, string& s){ //---> O(1)
		if (b.usuario == s) return true; // ---> 2
		else return false; // ---> 1
	}

    friend void operator << (ostream& o, BlockChain& b){ //---> O( k )
        b.data.imprimir_registros(); // ---> K ,  K: cantidad de registros del BlockChain
    }

    friend bool operator < (BlockChain& b1, BlockChain& b2){ //---> O(1)
        if (b1.hashcode < b2.hashcode) return true; // ---> 2
        else return false; // ---> 1
    }

    friend bool operator > (BlockChain& b1, BlockChain& b2){ //---> O(1)
        if (b1.hashcode > b2.hashcode) return true; // ---> 2
        else return false; // ---> 1
    }
	
	void extraer_valores_data(int index, string& emisor, string& receptor, double& monto){ //---> O( k )
		data[index].extraer_valores(emisor,receptor,monto); //---> K
	}

	// q : cantidad de letras del usuario , K: cantidad de registros del BlockChain
    void Hashing() { // O( q ) + O( K ) 
		int aux = 0; // ---> 1
	    int aux2 = 0; // ---> 1
	    int aux3 = 0; // ---> 1
	    string t; // ---> 1
	    int j = 0; // ---> 1
	    int num; // ---> 1
	    t.resize(11); // ---> 1
		
	    for (int i = 0; i < usuario.length(); ++i) { //---> 1 + q(2+4+2) = O( q )
		    //suma todos los ascii del usuario	
			aux = aux + (int)usuario[i]; // ---> 4
	    }
		int tamanho = data.size(); // ---> 2
	    for (int i = 0; i < tamanho; ++i) { // ---> 1 + k(1+7+2) = O( K )
            string s = data[i].receptor; // --> 3
            //suma los ascii de la primera letra de cada persona
			aux2 = aux2 + (int)s[0]; // ---> 4
	    }
	    for (int i = 0; i < tamanho; ++i) { // 1 + k(1+6+2) = O( k )
            double s = data[i].monto; // ---> 3
			//suma los montos 
		    aux3 = aux3 + (int)s; // ---> 3	
		}
	    for (int i = 0; i < 11; ++i) { // ---> 1 + 11(1 + 7 + 13 + 2) = 254
		    if (i < 5) { // ---> 1 + 4 = 5
				//Condicional para insertar solo la parte del usuario
			    num = aux + (int)prevHashCode[j]; // ---> 4
		    }
		    else if (5 <= i && i < 10) { // ---> 3 + 4 = 7
				//Condicional para insertar solo la parte del receptor
			    num = aux2 + (int)prevHashCode[j]; // ---> 4
		    }
		    else {// ---> 4
				//Condicional para insertar solo la parte del monto
			    num = aux3 + (int)prevHashCode[j]; // ---> 4
		    }
            // Condicionales para realizar un hash estable que depende del prevhash y de los datos del bloque
            // Se inserta el char en la pos i del hash
            if (num % 2 == 0 && (int)prevHashCode[j] %2 == 0) {// 7 + 6 = 13
				    num = 48 + num % 10; // ---> 3
				    t[j] = char(num); // ---> 3
			}else if(num % 2 == 0 && (int)prevHashCode[j] % 2 != 0){// 7 + 6 = 13
				    num = 65 + num % 25; // ---> 3
				    t[j] = char(num); // ---> 3
			}else if (num % 2 != 0 && (int)prevHashCode[j] % 2 != 0) {// 7 + 6 = 13
				    num = 97 + num % 25; // ---> 3
				    t[j] = char(num); // ---> 3
			}else if (num % 2 != 0 && (int)prevHashCode[j] % 2 == 0) { // 7 + 6 = 13
				    num = 35 + num % 4; // ---> 3
				    t[j] = char(num); // ---> 3
			}
			    ++j; // ---> 2
	    }
		//Se asigna el valor al hash
        hashcode = t; // ---> 2
    }
};


void escribir_archivo(DoubleList<BlockChain>& lista){
	ofstream arcEsc("datos.txt");
	int cantBlockChains = lista.size();
	int indexBlockChain = 0;
	int cantRegistros;
	int indexRegistro = 0;
	string emisor, receptor;
	double monto;
	if (arcEsc.is_open()){
		while (indexBlockChain < cantBlockChains)
		{
			cantRegistros = lista[indexBlockChain].data.size();
			while (indexRegistro < cantRegistros)
			{
				lista[indexBlockChain].extraer_valores_data(indexRegistro,emisor,receptor,monto);
				arcEsc << monto << "|" << emisor << "|" << receptor << "\n";
				indexRegistro++;
			}
			indexRegistro = 0;
			indexBlockChain++;
		}

		arcEsc.close();
	}
}

void leer_archivo(DoubleList<BlockChain>& lista, BSTreeFiltro<transaccion>& arbolEmisores, BSTreeFiltro<transaccion>& arbolReceptores, BSTreeFiltro<transaccion>& arbolMontos){

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
                int ultimo = lista.size() - 1;
                lista[ultimo].data.push_back(transaccion(emisor, monto, receptor));

				arbolEmisores.insertUsuario(transaccion(emisor,monto,receptor), emisor);
				arbolReceptores.insertReceptor(transaccion(emisor,monto,receptor), receptor);
				arbolMontos.insertMonto(transaccion(emisor,monto,receptor), monto);

    		    //cout<<monto<<"|"<<emisor<<"|"<<receptor<<"\n";
    		}
    		arcLec.close();
    	}
		
}

bool VerificarFallo(DoubleList<BlockChain> d){
	for (int i = 0;i<d.size()-1;++i){
		if(d[i].hashcode != d[i+1].prevHashCode){
			return true;
		}
	}
	return false;
}

int VerificarNuevo(DoubleList<BlockChain> d,string s){

	for (int i = 0;i<d.size();++i){
		if(d[i].usuario == s){
			return i;
		 }
	}
	
}

void HashTrunc(DoubleList<BlockChain> d,string user){
	int j = 0;
	for(int i = 0;i < d.size();++i){
		 if(d[i].usuario == user){
			 j = i;
			 break;
		 }
	}


	for (int i = j; i < d.size();++i){
		d[i].Hashing();
	}
}

bool revisar_existencia_del_blockChain(DoubleList<BlockChain>& b, string& usuario){
	 return b.find(usuario);
}

int main(){

    DoubleList<BlockChain> listaBlockChains;
    BSTree<BlockChain> arbolBlockChains;
	BSTreeFiltro<transaccion> arbolTransaccionesUsuario;
	BSTreeFiltro<transaccion> arbolTransaccionesReceptor;
	BSTreeFiltro<transaccion> arbolTransaccionesMonto;

    short op;
    bool seleccion = false;
    int criterio;
    char regresar;
    do
    {
        system("cls");
        cout << ":::::::::MENU::::::::::\n";
        cout << "1. Crear nuevo usuario(BlockChain)\n";
		cout << "2. Insertar registro\n";
        cout << "3. Subir datos\n";
        cout << "4. Descargar Datos\n";
        cout << "5. Imprimir todas las transacciones\n";
        cout << "6. Ordenar la Cadena de BlockChains en base a un criterio\n";
		cout << "7. Agregar registro a un usuario anterior (forzar cambio)\n";
		cout << "8. Agregar registro a un usuario anterior maleficamente\n";
		cout << "9. verificar hashes enlazados\n";
		cout << "10. Salir\n";
        cout << "Opcion: "; cin >> op;
        
        if (op == 1){
            string nombre;
            int ultimo = listaBlockChains.size() - 1;
			bool existencia = true;

			while (existencia == true)
			{
				cout << "Ingresar nombre del blockChain: ";
            	cin >> nombre;
				existencia = revisar_existencia_del_blockChain(listaBlockChains, nombre);
				if (existencia == true) cout << "Ese usuario ya existe, tal vez quieres ingresar un registro\n";
			}

			BlockChain nuevo;//posiblemente se deba inicializar el hashCode en 00000000000
            nuevo.usuario = nombre;
            if(listaBlockChains.size() != 0){
                string hashCodeAnterior = listaBlockChains[ultimo].hashcode;
                nuevo.prevHashCode = hashCodeAnterior;
            }

            listaBlockChains.push_back(nuevo);
			
        }
		else if (op == 2){
			string emisor, receptor;
            double monto;
            cout << "Ingrese el nombre del emisor: ";
            cin >> emisor;
            cout << "Ingrese el nombre del receptor: ";
            cin >> receptor;
            cout << "Ingrese el monto: ";
            cin >> monto;

            int ultimo = listaBlockChains.size() - 1;
			if (listaBlockChains[ultimo].usuario == emisor){
				listaBlockChains[ultimo].data.push_back(transaccion(emisor, monto, receptor));

				listaBlockChains[ultimo].Hashing();

				// arbolBlockChains[0].data.push_back(transaccion(emisor, monto, receptor));

				//Insercion de arboles de criterios
				arbolTransaccionesUsuario.insertUsuario(transaccion(emisor,monto,receptor), emisor);
				arbolTransaccionesReceptor.insertReceptor(transaccion(emisor,monto,receptor), receptor);
				arbolTransaccionesMonto.insertMonto(transaccion(emisor,monto,receptor), monto);
			}
			else {
				char op2;
				cout << "No existe ese usuario, desea volver al menu?: \n";
				cin >> op2;
				if (op2 == 'n') op = 8;
			}

		}
        else if (op == 3){
			escribir_archivo(listaBlockChains);
        }
        else if (op == 4){
            listaBlockChains.clear();
			arbolTransaccionesUsuario.clear();
			arbolTransaccionesReceptor.clear();
			arbolTransaccionesMonto.clear();
            leer_archivo(listaBlockChains,arbolTransaccionesUsuario,arbolTransaccionesReceptor,arbolTransaccionesMonto);
        }
        else if (op == 5){
            listaBlockChains.imprimir_registros();
            cout << "Desea volver al menu?: ";
            cin >> regresar;
            if (regresar == 'n') op = 8;
        } 
		else if (op == 6){//falta completar los filtros
            system("cls");
            cout << ":::::::::FILTROS::::::::::\n";
            cout << "1. Usuario igual a\n";
            cout << "2. Usuario inicia con\n";
		    cout << "3. Receptor igual a\n";
            cout << "4. Receptor inicia con\n";
			cout << "5. Rango de Montos\n";
            cout << "6. Montos mayores\n";
		    cout << "7. Montos menores\n";
			int posss;
			cin >> posss;
			if(posss==1){
				string usuario;
				cout << "Ingrese el usuario para buscar sus transacciones" << endl;
				cin >> usuario;
				arbolTransaccionesUsuario.filtroUsuarioIgualA(usuario);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
			else if(posss==2){
				string usuario;
				cout << "Ingrese el usuario para buscar sus transacciones" << endl;
				cin >> usuario;
				arbolTransaccionesUsuario.filtroUsuarioIniciaCon(usuario);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
			else if(posss==3){
				string receptor;
				cout << "Ingrese el receptor para buscar sus transacciones" << endl;
				cin >> receptor;
				arbolTransaccionesReceptor.filtroReceptorIgualA(receptor);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
			else if(posss==4){
				string receptor;
				cout << "Ingrese el receptor para buscar las transacciones" << endl;
				cin >> receptor;
				arbolTransaccionesReceptor.filtroReceptorIniciaCon(receptor);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
			else if(posss==5){
				double montoIni, montoFin;
				cout << "Ingrese el monto inicial del rango de montos" << endl;
				cin >> montoIni;
				cout << "Ingrese el monto final del rango de montos" << endl;
				cin >> montoFin;
				arbolTransaccionesMonto.filtroRangoMontos(montoIni,montoFin);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
			else if(posss==6){
				double monto;
				cout << "Ingrese el monto" << endl;
				cin >> monto;
				arbolTransaccionesMonto.filtroMontosMayores(monto);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
			else if(posss==7){
				double monto;
				cout << "Ingrese el monto" << endl;
				cin >> monto;
				arbolTransaccionesMonto.filtroMontosMenores(monto);
				cout << "Desea volver al menu?: ";
                cin >> regresar;
                if (regresar == 'n') op = 8;
			}
		}
		else if (op == 7){
			string emisor, receptor;
            double monto;
            cout << "Ingrese el nombre del emisor: ";
            cin >> emisor;
            cout << "Ingrese el nombre del receptor: ";
            cin >> receptor;
            cout << "Ingrese el monto: ";
            cin >> monto;

			listaBlockChains[VerificarNuevo(listaBlockChains,emisor)].data.push_back(transaccion(emisor, monto, receptor));
			HashTrunc(listaBlockChains,emisor);
		}else if(op == 8){
			string emisor, receptor;
            double monto;
            cout << "Ingrese el nombre del emisor: ";
            cin >> emisor;
            cout << "Ingrese el nombre del receptor: ";
            cin >> receptor;
            cout << "Ingrese el monto: ";
            cin >> monto;
			listaBlockChains[VerificarNuevo(listaBlockChains,emisor)].data.push_back(transaccion(emisor, monto, receptor));
			listaBlockChains[VerificarNuevo(listaBlockChains, emisor)].Hashing();
		}else if(op == 9){
			if(VerificarFallo(listaBlockChains) == true){
				cout << "Se encontro un fallo de hashs";
			}else{
				cout << "No hay fallo en los hashes";
			}
		}
        
        
    } while (op != 10);
    
}
