#include "forwardList.hpp"

template <typename T>
struct BlockChain {
    string user;
    string prevHash;
    string Hash;
    ForwardList<T> data;

    BlockChain() {
    }

    BlockChain(string value) {
        user = value;
    }

    void ingresar_prevHash(string value) { prevHash = value; } 
    void ingresar_Hash(string value) { prevHash = value; } 
    string retornar_prevHash() { return prevHash;}
    string retornar_Hash() { return Hash;}

    friend bool operator > (BlockChain& b1, BlockChain& b2){
        if (b1.Hash > b2.Hash) return true;
        else return false;
    }

    friend bool operator < (BlockChain& b1, BlockChain& b2){
        if (b1.Hash < b2.Hash) return true;
        else return false;
    }

    friend ostream& operator << (ostream& o, BlockChain& n) {
        o << n.data.display();
    }

    void killSelf() {
        /*if (prev != nullptr)
            next->killSelf();//arreglar
        delete this;*/
    }
};