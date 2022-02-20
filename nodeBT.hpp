template <typename T>
struct NodeBT {
    T data;
    NodeBT<T>* left;
    NodeBT<T>* right;

    NodeBT() {
        left = right = nullptr;
    }

    NodeBT(T value) {
        data = value;
        left = right = nullptr;
    }

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};
