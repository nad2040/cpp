#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Pole {
    stack<int> rod;
    string name;
};

stack<int> source;
stack<int> middle;
stack<int> dest;
Pole a = {source, "A"};
Pole b = {middle, "B"};
Pole c = {dest, "C"};
int moveCount = 0;

void displayStack(Pole pole) {
    stack<int> s = pole.rod;
    cout << pole.name+":";
    while(!s.empty()) {
        std::cout << "\n   "+to_string(s.top());
        s.pop();
    }
    cout << endl;
}
void displayPoles(){
    displayStack(a);
    displayStack(b);
    displayStack(c);
}

void move(int disk, Pole &source, Pole &dest) {
    dest.rod.push(source.rod.top());
    source.rod.pop();
    cout << "move "+to_string(disk)+" from "+source.name+" to "+dest.name << endl;
    moveCount++;
}
void hanoi(int n, Pole &source, Pole &middle, Pole &dest) {
    if (n == 1) {
        move(1,source,dest);
    } else if (n > 1) {
        hanoi(n-1,source,dest,middle);
        displayPoles();
        move(n,source,dest);
        displayPoles();
        hanoi(n-1,middle,source,dest);
    } else {
        cout << "wrong input\n";
        return;
    }
}
void load(Pole &a, int n) {
    for (int i=n; i>0; --i) {
        a.rod.push(i);
    }
}

int main() {
    int numDisks=4;
    load(a,numDisks);
    displayPoles();
    hanoi(numDisks,a,b,c);
    displayPoles();
    cout << moveCount << " moves taken\n";
}