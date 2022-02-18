template <typename T>
struct Block {
    T data;
    Node<T>* next;
    Node<T>* prev;
    int hash;
    Node() {
        next = prev = nullptr;
    }

    Node(T value) {
        data = value;
        next = prev = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }
};