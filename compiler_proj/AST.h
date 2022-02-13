#pragma once
#include "Token.h"
#include <iostream>

class AST {
public:
	AST* left_;
	AST* right_;

    AST() : value_(), left_(nullptr), right_(nullptr) {
        //std::cout << "def construct" << std::endl;
    }

    AST(Token value) : value_(value), left_(nullptr), right_(nullptr) {
        //std::cout << "val constructor" << std::endl;
    }

    AST(Token value, AST* left, AST* right) : value_(value), left_(left), right_(right) {
        //std::cout << "branch constructor" << std::endl;
    }

    ~AST() {
        delete left_;
        delete right_;
        //std::cout << "destruct AST " << toString(value_) << std::endl;
    }

    Token getValue() {
        return value_;
    }

private:
    Token value_;

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