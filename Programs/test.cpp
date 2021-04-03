#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ignorews(istream& in) {
    char c;
    while (in.get(c) && !in.eof()) {
        if (isspace(c)) continue;
        else if (c == ';') {
            while (in.get(c) && !in.eof() && c != '\n');
            continue;
        }
        in.unget();
        break;
    }
}

int parenCount(string& line) {
    int left = 0, right = 0;
    for (int i=0; i<line.length(); ++i) {
        if (line[i] == '(') ++left;
        if (line[i] == ')') ++right;
    }
    return left - right;
}

void getInput(istream& in, string& temp) {
    char c;
    ignorews(in);
    while (in.get(c) && !in.eof()) {
        temp += c;
        if (c == '\n' && parenCount(temp) == 0) return;
        else if (c == '"') {
            while (in.get(c) && !in.eof() && c != '"') temp += c;
            temp+='"';
        }
        else if (c == '(') { getInput(in, temp); if (parenCount(temp) == 0) return; }
        else if (c == ')') return;
    }
}

int main() {
    ifstream ifs("../scheme_proj/scm_files/run-meta-circular.scm");
    string s;
    getInput(cin, s);
    cout << s << '\n';
}

