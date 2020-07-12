#include <iostream>
using namespace std;

struct menu_item {
    string item;
    double cost;
};

menu_item appetizer_menu[] = {
    { "1. Fruit Salad                ", 4.50 },
    { "2. Popcorn Chicken            ", 4.00 },
    { "3. Sweet Potato Fries         ", 2.00 },
    { "4. Hors d'oeuvres             ", 3.00 }
};

int test[5] = {0,1,2,3,4};

int hello[2][3] = {
    {0, 1, 2},
    {3, 4, 5}
};

int main() {
    for (int i=0; i<4; i++)
        cout << appetizer_menu[i].item << "\t$" << appetizer_menu[i].cost << endl;

    cout << endl;

    for (int i=0; i<5; ++i)
        cout << test[i] << " " << endl;
    
    cout << endl;

    for (int i=0; i<2; ++i) {
        for (int j=0; j<3; ++j) {
            cout << hello[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}