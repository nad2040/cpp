#include <iostream>
#include <fstream>
#include <string>
#include "write.h"
using namespace std;

int main() {
    ifstream ifs("asdf.txt");
    char c;
    while (ifs.get(c)) {
        if (ifs.peek() == EOF) cout << "EOF found \n";
        cout << c << '\n';
    }
}