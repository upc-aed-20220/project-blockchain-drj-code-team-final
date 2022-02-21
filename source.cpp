#include "doubleList.hpp"
#include "doubleListToBlockChain.hpp"

struct transaccion{
	string emisor;
	double monto;
    string receptor;
	transaccion(){}
	transaccion(string _emisor, double _monto, string _receptor)
    {emisor = _emisor; emisor = _monto; receptor = _receptor;}
    
    //:::::::::VERSION 1::::::::: 
	//string& operator = (string& n) {
    //     n = to_string(monto) + " from " + emisor + " to " + receptor + "\n";
    //     return n;
    //}

    //:::::::::VERSION 2::::::::: 
    //friend ostream& operator << (ostream& o, transaccion& t) {
    //    o << t.monto << " from " << t.emisor << " to " << t.receptor + "\n";
    //}

    friend ostream &operator<<(ostream& o, transaccion& t) {
        o << t.monto << " from " << t.emisor << " to " << t.receptor + "\n";
        return o;
    }
}; 

struct BlockChain {
    string usuario;
    string hashcode;
    string prevHashCode;
    DoubleListToBlockChain<transaccion> data;

    BlockChain() {

    }

    BlockChain(string _usuario) {
        usuario = _usuario;
    }

    //:::::::::VERSION 1::::::::: 
    //friend ostream& operator << (ostream& o, BlockChain& b) {
    //    o << b.data.display();
    //}

    //:::::::::VERSION 2::::::::: 
    //friend ostream& operator << (ostream& o, BlockChain& b) {
    //    b.data.display(o);
    //}

    /*friend ostream& operator<<(ostream& o, BlockChain& b) {
        
        int cant = 0;
        while (cant < b.data.size()){
            o << b.data.display(cant);
            ++cant;
        }
        return o;
        //o << b.data.display();
    }
 
    //void killSelf() {
    //    //if (prev != nullptr)
    //    //    next->killSelf();//arreglar
    //    //delete this;
    //}
    */
};


int main(){

    DoubleList<BlockChain> listaBlockChains;
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
        cout << "6. Salir\n";
        cin >> op;
        
        if (op == 1){
            string usuario;
            cout << "Ingrese el nombre del usuario: ";
            cin >> usuario;
            BlockChain nuevoBloque(usuario);
            listaBlockChains.push_back(nuevoBloque);
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
            BlockChain aux = listaBlockChains.ultimo_blockChain();
            transaccion tra(emisor, monto, receptor);
            aux.data.push_back(tra);
        }
        else if (op == 4){
            //listaBlockChains.imprimir_registros();
            int cant = 0;
            int tamanio = listaBlockChains.size();
            while (cant < tamanio){
                //cout << "hola";
                listaBlockChains[cant].data.display();
                cant++;
            }
            
            /*int cant = 0;
            BlockChain aux;
            while (cant < listaBlockChains.size()){
                aux = listaBlockChains.retornar_block_chain(cant);
                cout << aux.data;
                cant++;
            }*/
        }
        
    } while (op != 6);
    
    
    


}