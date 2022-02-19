template <typename T>
struct NodeBT {
    T data;
    Node<T>* left;
    Node<T>* right;
    int altura;

    NodeBT() {
        left = right = nullptr;
        altura = 0;
    }

    NodeBT(T value) {
        data = value;
        left = right = nullptr;
        altura = 0;
    }

    void killSelf() {
        if (next != nullptr)
            next->killSelf();
        delete this;
    }
};