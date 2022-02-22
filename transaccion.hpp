#include <iostream>
using namespace std;

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
	void extraer_valores(string& _emisor, string& _receptor, double& _monto){
		_emisor = emisor;
		_receptor = receptor;
		_monto = monto;
	}
}; 