#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct Atom {
    enum { CHAR, INT, STR, SYM } atomType_;
    std::variant<char, int, std::string> value_;
};

void display(const Atom& a) {
    switch(a.atomType_) {
        case Atom::CHAR: std::cout << "CHAR:" << std::get<char>(a.value_) << '\n'; return;
        case Atom::INT: std::cout << "INT:" << std::get<int>(a.value_) << '\n'; return;
        case Atom::STR: std::cout << "STR:" << std::get<std::string>(a.value_) << '\n'; return;
        case Atom::SYM: std::cout << "SYM:" << std::get<std::string>(a.value_) << '\n'; return;
        default: std::cout << "unknown type\n"; return;
    }
}

int main() {
    std::vector<Atom> atoms;
    atoms.push_back({Atom::CHAR, 'c'});
    atoms.push_back({Atom::INT, 123});
    atoms.push_back({Atom::STR, "hello"});
    atoms.push_back({Atom::SYM, "world"});
    for(auto& e : atoms) display(e);
}
