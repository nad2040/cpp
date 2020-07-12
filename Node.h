#include<iostream>

template<typename T>
std::string toString(T& t) {
    return t.getValue();
}

template<typename T>
class Node {
public:
	Node* left_;
	Node* right_;

    Node() : value_(), left_(nullptr), right_(nullptr) {
        //std::cout << "def construct" << std::endl;
    }

    Node(T value) : value_(value), left_(nullptr), right_(nullptr) {
        //std::cout << "val constructor" << std::endl;
    }

    Node(T value, Node* left, Node* right) : value_(value), left_(left), right_(right) {
        //std::cout << "branch constructor" << std::endl;
    }

    ~Node() {
        delete left_;
        delete right_;
        //std::cout << "destruct node " << toString(value_) << std::endl;
    }

    T getValue() {
        return value_;
    }

private:
    T value_;

};

template<typename T>
void visitTreeInfix(Node<T>* tree) {
    if (tree != nullptr) {
        std::cout << "(";
        if (tree->left_ != nullptr) {
            Node<T>* l = tree->left_;
            visitTreeInfix(l);
        }
        std::cout << tree->getValue().getValue();
        if (tree->right_ != nullptr) {
            Node<T>* r = tree->right_;
            visitTreeInfix(r);
        }
        std::cout << ")";
    }
}

template<typename T>
void visitTreeReverseInfix(Node<T>* tree) {
    if (tree != nullptr) {
        std::cout << "(";
        if (tree->right_ != nullptr) {
            Node<T>* r = tree->right_;
            visitTreeReverseInfix(r);
        }
        std::cout << tree->getValue().getValue();
        if (tree->left_ != nullptr) {
            Node<T>* l = tree->left_;
            visitTreeReverseInfix(l);
        }
        std::cout << ")";
    }
}

template<typename T>
void visitTreePostfix(Node<T>* tree) {
    if (tree != nullptr) {
        std::cout << "(";
        if (tree->left_ != nullptr) {
            Node<T>* l = tree->left_;
            visitTreePostfix(l);
        }
        if (tree->right_ != nullptr) {
            Node<T>* r = tree->right_;
            visitTreePostfix(r);
        }
        std::cout << tree->getValue().getValue();
        std::cout << ")";
    }
}