#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));
    int answer = rand()%100+1;
    cout << "enter a number between 1-100\n";
    int choice = -1;
    while (choice != answer) {
        cin >> choice;
        if (choice > answer) {
            cout << "guess lower\n";
        } else if (choice < answer) {
            cout << "guess higher\n";
        } else {
            cout << "correct\n";
            break;
        }
    }

}