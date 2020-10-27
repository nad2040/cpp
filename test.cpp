#include <iostream>

using namespace std;

string getInput() {
    string buf, line;

    while (!cin.eof()) {
        getline(cin, line);
        cout << "got:" << int(line[0]) << endl;
        buf += line;
    }
    cin.clear();
    return buf;
}

int main() {
    string buf;
    while (true) {
        buf = getInput();
        cout << "received: " << buf << '\n';
    }
}

