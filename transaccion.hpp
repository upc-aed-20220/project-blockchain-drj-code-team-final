#include <iostream>
using namespace std;

struct transaccion{
	string emisor; // ---> 1
	double monto; // ---> 1
    string receptor; // ---> 1
	transaccion(){}
	transaccion(string _emisor, double _monto, string _receptor) // O(1)
    {emisor = _emisor; monto = _monto; receptor = _receptor;} // ---> 3
    
    friend ostream &operator<<(ostream& o, transaccion& t) { // O(1)
        o << t.monto << " from " << t.emisor << " to " << t.receptor << "\n"; // ---> 12
        return o; // ---> 1
    }
	void extraer_valores(string& _emisor, string& _receptor, double& _monto){ // O(1)
		_emisor = emisor; // ---> 1
		_receptor = receptor; // ---> 1
		_monto = monto; // ---> 1
	}
}; 