#include "CadenaBlockChain.hpp"

struct transaccion{
	string emisor;
	double monto;
    string receptor;
	transaccion(){}
	transaccion(string _emisor, double _monto, string _receptor)
    {emisor = _emisor; emisor = _monto; receptor = _receptor;}
	friend ostream& operator << (ostream& o, transaccion& n) {
        o << n.monto << " from " << n.emisor << " to " << n.receptor << "\n";
    }
}; 

int main(){

    CadenaBlockChain<transaccion> cadenaBlockChain;
    short op;
    bool seleccion = false;
    int criterio;
    do
    {
        cout << ":::::::::MENU::::::::::\n";
        cout << "1. Crear nuevo usuario(BlockChain)\n";
        cout << "2. Cargar datos\n";
        cout << "3. Insertar registro\n";
        cout << "4. Imprimir transacciones\n";//uncluye filtros //todas? o por bloque?
        cout << "5. Ordenar la Cadena de BlockChains en base a un criterio\n";
        cout << "5. Salir\n";

        if (op == 1){
            string user;
            cout << "Ingrese el nombre del nuevo usuario(BlockChain): ";
            cin >> user;
            cadenaBlockChain.agregar_blockChain(user);
        }
        else if(op == 2){
            
            
        }
        else if (op == 3){
            string emisor, receptor;
            double monto;
            cout << "Ingrese el nomnbre del emisor: "; //Bro le agrego un prev al Blockchain para recorrer los nodos? :´v
            cin >> emisor;
            cout << "Ingrese el monto a transferir: ";
            cin >> monto;
            cout << "Ingrese el receptor: ";
            cin >> receptor;
            cadenaBlockChain.agregar_registro(transaccion(emisor, monto, receptor));
        }
        else if (op == 4){
            cadenaBlockChain.imprimir_registros();
        }

        


    } while (op != 5);
    
    
    


}