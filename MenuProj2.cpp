//Menu using struct
#include <iostream>
#include <string>
#include <sstream> 

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

menu_item entree_menu[] = {
    { "1. Caesar Salad               ",  7.00 },
    { "2. Shrimp & Broccoli Stir Fry ", 10.00 }
};

menu_item sushi_menu[] = {
    { "1. California Roll Platter    ", 18.00 },
    { "2. Eel Roll Platter           ", 23.00 },
    { "3. Shrimp Tempura Roll Platter", 20.00 },
    { "4. Salmon Roll Platter        ", 19.00 },
};

menu_item pizza_menu[] = {
    { "1. Pepperoni Pizza            ", 12.50 },
    { "2. Mushroom Pizza             ", 11.75 },
    { "3. Broccoli Pizza             ", 11.00 },
    { "4. Bacon Pizza                ", 12.00 },
};

void showMenu(menu_item mi[], int elems) {
    for (int i=0; i<elems; i++)
        cout << "\t\t" << mi[i].item << "\t$" << mi[i].cost << endl;
}

void orderItem(menu_item mi[], string& order, double& total) {
    int aI, aC;
    cout << "Please choose an item.\n";
    cin >> aI;
    cout << "How many you want?\n";
    cin >> aC;
    stringstream ss;
    ss << aC << "x " << mi[aI-1].item << " \t$" << mi[aI-1].cost*aC << endl;
    order += ss.str();
    total += mi[aI-1].cost*aC;
}

void mainMenu() {
    cout << "Choose from:\n1 - Appetizer\n2 - Main Course\n3 - Sushi\n4 - Pizza\n9 - End Order" << endl;
}

int main() {
    cout << "Welcome to our Restaurant!\n";
    string order = "";
    double total = 0.0;
    int choice = 0;
    while (choice != 9) {
        mainMenu();
        cin >> choice;
        switch(choice) {
            case 1:
                showMenu(appetizer_menu, sizeof(appetizer_menu)/sizeof(appetizer_menu[0]));
                orderItem(appetizer_menu, order, total);
                break;
            case 2: 
                showMenu(entree_menu, sizeof(entree_menu)/sizeof(entree_menu[0]));
                orderItem(entree_menu, order, total);
                break;
            case 3: 
                showMenu(sushi_menu, sizeof(sushi_menu)/sizeof(sushi_menu[0]));
                orderItem(sushi_menu, order, total);
                break;
            case 4: 
                showMenu(pizza_menu, sizeof(pizza_menu)/sizeof(pizza_menu[0]));
                orderItem(pizza_menu, order, total);
                break;
            default: break;
        }
    }
    cout << "Your order:\n\n" << order << endl;
    cout << "Total:                       \t$" << total << endl;
    cout << "Tax:                         \t$" << ((int)(total*1.0875*100))/100.0 << endl;
    return 0;
}