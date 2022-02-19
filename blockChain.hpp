template <typename T>
struct BlockChain {
    string user;
    string prevHash;
    string Hash;
    list<T> *data;

    BlockChain() {
        next = prev = nullptr;
    }

    BlockChain(T value) {
        user = value;
        next = prev = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }
};