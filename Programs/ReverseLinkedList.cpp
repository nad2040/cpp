#include <iostream>

class LinkedList {
public:
    int value;
    LinkedList *next;

    LinkedList(int val) : value(val), next(nullptr) {}

    LinkedList(int a, int b, int c, int d) {
        value = a;
        next = new LinkedList(b);
        next->next = new LinkedList(c);
        next->next->next = new LinkedList(d);
    }

};

void printLinkedList(LinkedList *head) {
    if (!head) return;
    LinkedList *curr = head;
    while (curr->next) {
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << curr->value << std::endl;
}

void reverseLinkedList(LinkedList *&head) {
    LinkedList *prev = head, *curr = head->next, *next = nullptr;
    prev->next = nullptr;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

int main() {
    LinkedList *test = new LinkedList(1,2,3,4);
    printLinkedList(test);

    reverseLinkedList(test);
    
    printLinkedList(test);

    return 0;
}