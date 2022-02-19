template <typename T>
struct Block {
    string user;
    list<T> *data;
    string prevHash;

    Block() {
        next = prev = nullptr;
    }

    Block(T value) {
        user = value;
        next = prev = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }
};