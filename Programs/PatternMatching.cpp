#include <string>
#include <iostream>

using namespace std;

bool matchStar(char c, string s, string p);

bool matchHere(string s, string p) {
    if (p[0] == '\0') return s[0] == '\0';
    if (p[1] == '*') return matchStar(p[0], s, p.substr(2));
    if (s[0] != '\0' && (p[0] == '.' || p[0] == s[0])) return matchHere(s.substr(1), p.substr(1));
    return false;
}

bool matchStar(char c, string s, string p) {
    int i=0;
    do {
        if (matchHere(s.substr(i),p)) return true;
    } while (s[0] != '\0' && (s[i++] == c || c == '.'));
    return false;
}

bool isMatch(string s, string p) {
    int si=0, pi=0;
    std::cout << " s:" << s << " si:" << si << " p:" << p << " pi:" << pi << std::endl;
    while (si < s.length() && pi < p.length()) {
        if (p[pi+1] != '\0' && p[pi+1] == '*') {
            cout << "match star si: " << si << " s[si]: " << s[si] << " pi: " << pi << " p[pi]: " << p[pi] << '\n';
            do {
                if (isMatch(s.substr(si), p.substr(pi+2))) return true;
            } while (si < s.length() && (s[si] == p[pi] || p[pi] == '.'));
            return false;
        } else {
            if (p[pi] == s[si] || p[pi] == '.') {
                ++pi;
                ++si;
                cout << "match char: si: " << si << " s[si]: " << s[si] << " pi: " << pi << " p[pi]: " << p[pi] << '\n';
            } else return false;
        }
    }
    std::cout << " s:" << s << " si:" << si << " p:" << p << " pi:" << pi << std::endl;
    return si == s.length() && pi == p.length();
}

int main() {
    cout << isMatch("ab", ".*c");
}