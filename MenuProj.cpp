//Menu using struct
#include <iostream>
#include <array>
#include <string>
#include <sstream> // Allows you to wr

using namespace std;

struct menu_item {
    string item;
    double cost;
};

int choice=0;
double total = 0;
const double tax = 1.08875;

array<menu_item, 4> appetizer_menu = {{
    { "Fruit Salad                ", 4.50 },
    { "Popcorn Chicken            ", 4.00 },
    { "Sweet Potato Fries         ", 2.00 },
    { "Hors d'oeuvres             ", 3.00 }
}};

array<menu_item, 2> entree_menu = {{
    { "Caesar Salad               ",  7.00 },
    { "Shrimp & Broccoli Stir Fry ", 10.00 }
}};

array<menu_item, 4> sushi_menu = {{
    { "California Roll Platter    ", 18.00 },
    { "Eel Roll Platter           ", 23.00 },
    { "Shrimp Tempura Roll Platter", 20.00 },
    { "Salmon Roll Platter        ", 19.00 },
}};

array<menu_item, 4> pizza_menu = {{
    { "Pepperoni Pizza            ", 12.50 },
    { "Mushroom Pizza             ", 11.75 },
    { "Broccoli Pizza             ", 11.00 },
    { "Bacon Pizza                ", 12.00 },
}};

void showAppetizer() {
    for (int i=0; i<appetizer_menu.size(); i++)
        cout << appetizer_menu[i].item << "\t$" << appetizer_menu[i].cost << endl;
}
void showMainCourse() {
    for (int i=0; i<entree_menu.size(); i++)
        cout << entree_menu[i].item << "\t$" << entree_menu[i].cost << endl;
}
void showSushi() {
    for (int i=0; i<sushi_menu.size(); i++)
        cout << sushi_menu[i].item << "\t$" << sushi_menu[i].cost << endl;
}
void showPizza() {
    for (int i=0; i<pizza_menu.size(); i++)
        cout << pizza_menu[i].item << "\t$" << pizza_menu[i].cost << endl;
}
void orderItem(string& order) {
    int aI, aC;
    cout << "Please choose an item.\n";
    cin >> aI;
    cout << "How many you want?\n";
    cin >> aC;
    stringstream ss;
    switch(choice) {
        case 1:
            ss << aC << "x " << appetizer_menu[aI-1].item << " \t$" << appetizer_menu[aI-1].cost*aC << endl;
            order += ss.str();
            total += appetizer_menu[aI-1].cost*aC;
            break;
        case 2:
            ss << aC << "x " << entree_menu[aI-1].item << " \t$" << entree_menu[aI-1].cost*aC << endl;
            order += ss.str();
            total += entree_menu[aI-1].cost*aC;
            break;
        case 3:
            ss << aC << "x " << sushi_menu[aI-1].item << " \t$" << sushi_menu[aI-1].cost*aC << endl;
            order += ss.str();
            total += sushi_menu[aI-1].cost*aC;
            break;
        case 4:
            ss << aC << "x " << pizza_menu[aI-1].item << " \t$" << pizza_menu[aI-1].cost*aC << endl;
            order += ss.str();
            total += pizza_menu[aI-1].cost*aC;
            break;
        default: break;
    }
    //cout << order << endl;
}

void mainMenu() {
    cout << "Choose from:\n1 - Appetizer\n2 - Main Course\n3 - Sushi\n4 - Pizza\n9 - End Order" << endl;
}

int main() {
    cout << "Welcome to our Restaurant!\n";
    string order = "";
    while (choice != 9) {
        mainMenu();
        cin >> choice;
        switch(choice) {
            case 1:
                showAppetizer();
                orderItem(order);
                break;
            case 2: 
                showMainCourse();
                orderItem(order);
                break;
            case 3: 
                showSushi();
                orderItem(order);
                break;
            case 4: 
                showPizza();
                orderItem(order);
                break;
            default: break;
        }
    }
    cout << "Your order:\n\n" << order << endl;
    cout << "Total:                       \t$" << total << endl;
    cout << "Tax:                         \t$" << ((int)(total*tax*100))/100.0 << endl;
    return 0;
}