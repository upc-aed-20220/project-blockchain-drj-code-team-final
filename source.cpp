#include <iostream>
#include "nodeL.hpp"
#include "list.hpp"
#include "avl.hpp"
using namespace std;

int main(){

    ForwardList<string, int, string> blockChain;
    short op;
    do
    {
        cout << ":::::::::MENU::::::::::\n";
        cout << "1. Crear nuevo usuario\n";
        cout << "2. Cargar datos\n";
        cout << "3. Insertar registro\n";
        cout << "5. Imprimir transacciones\n";//uncluye filtros //todas? o por bloque?
        cout << "6. Salir\n";

        if (op == 1){
            string usuario;
            cout << "Ingrese el nombre del nuevo usuario: ";
            cin >> usuario;
            blockChain.push_back(usuario);
        }
        else if(op == 2){

        }
        else if (op == 3)
        


    } while (op != 6);
    
    
    


}