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
    string usuario;
    string hashcode;
    string prevHashCode;
    DoubleList<transaccion> data;

    BlockChain() {
    }

    BlockChain(string _usuario) {
        usuario = _usuario;
    }

    BlockChain(string _usuario, string _prevHashCode) {
        usuario = _usuario;
        prevHashCode = _prevHashCode;
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

	friend bool operator == (BlockChain& b, string& s){
		if (b.usuario == s) return true;
		else return false;
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
	
	void extraer_valores_data(int index, string& emisor, string& receptor, double& monto){
		data[index].extraer_valores(emisor,receptor,monto);
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
	//for (int i = 0;i<d.size();++i){
	//	
	//}
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
		cout << "7. Agregar registro a un usuario anterior\n";
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

		}
        
        
    } while (op != 10);
    
}
