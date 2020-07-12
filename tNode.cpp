#include<cstddef>

class Token {
};

class Node {
public:
	Token token_;
	Node* left_;
	Node* right_;
};





int main() {
	Token t;
	Node l;
	Node r;
	Node root;
	root.token_ = t;
	root.left_ = &l;
	root.right_ = &r;

	return 0;
}
