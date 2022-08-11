#pragma once
#include "Token.h"

class AST {
public:
	AST *left, *right;
    Token value;
    bool leaf;

    // AST() : value_(), left_(nullptr), right_(nullptr), leaf(false) {
    //     //std::cout << "def construct" << std::endl;
    // }

    AST(Token t) : value(t), left(nullptr), right(nullptr), leaf(true) {}
    AST(Token t, AST* l, AST* r) : value(t), left(l), right(r), leaf(false) {}

    ~AST() {
        delete left;
        delete right;
        //std::cout << "destruct AST " << toString(value_) << std::endl;
    }

    friend std::ostream & operator<<(std::ostream &out, AST *tree) {
        static int depth = 0;
        if (tree->leaf) {
            for (int i=0; i<depth; i++) out << "  ";
            out << tree->value << '\n';
        } else {
            for (int i=0; i<depth; i++) out << "  ";
            out << tree->value << '\n';
            depth++;
            if (tree->left) out << tree->left;
            if (tree->right) out << tree->right;
            depth--;
        }
        return out;
    }
};

// template<typename T>
// void visitTreeInfix(AST<T>* tree) {
//     if (tree != nullptr) {
//         std::cout << "(";
//         if (tree->left_ != nullptr) {
//             AST<T>* l = tree->left_;
//             visitTreeInfix(l);
//         }
//         std::cout << tree->getValue().getValue();
//         if (tree->right_ != nullptr) {
//             AST<T>* r = tree->right_;
//             visitTreeInfix(r);
//         }
//         std::cout << ")";
//     }
// }

// template<typename T>
// void visitTreeReverseInfix(AST<T>* tree) {
//     if (tree != nullptr) {
//         std::cout << "(";
//         if (tree->right_ != nullptr) {
//             AST<T>* r = tree->right_;
//             visitTreeReverseInfix(r);
//         }
//         std::cout << tree->getValue().getValue();
//         if (tree->left_ != nullptr) {
//             AST<T>* l = tree->left_;
//             visitTreeReverseInfix(l);
//         }
//         std::cout << ")";
//     }
// }

// template<typename T>
// void visitTreePostfix(AST<T>* tree) {
//     if (tree != nullptr) {
//         std::cout << "(";
//         if (tree->left_ != nullptr) {
//             AST<T>* l = tree->left_;
//             visitTreePostfix(l);
//         }
//         if (tree->right_ != nullptr) {
//             AST<T>* r = tree->right_;
//             visitTreePostfix(r);
//         }
//         std::cout << tree->getValue().getValue();
//         std::cout << ")";
//     }
// }