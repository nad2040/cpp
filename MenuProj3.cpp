//Menu using struct
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Menu {
public:
    struct MenuItem {
        string item;
        double cost;
    }; 
    MenuItem appetizer[4];
    MenuItem entree[2];
    MenuItem sushi[4];
    MenuItem pizza[4];
    Menu(): 
        appetizer {
            {"Fruit Salad                ", 4.50},
            {"Popcorn Chicken            ", 4.00},
            {"Sweet Potato Fries         ", 2.00},
            {"Hors d'oeuvres             ", 3.00}
        },
        entree {
            {"Caesar Salad               ", 7.00},
            {"Shrimp & Broccoli Stir Fry ", 10.00}
        },
        sushi {
            { "California Roll Platter    ", 18.00 },
            { "Eel Roll Platter           ", 23.00 },
            { "Shrimp Tempura Roll Platter", 20.00 },
            { "Salmon Roll Platter        ", 19.00 },
        },
        pizza {
            { "Pepperoni Pizza            ", 12.50 },
            { "Mushroom Pizza             ", 11.75 },
            { "Broccoli Pizza             ", 11.00 },
            { "Bacon Pizza                ", 12.00 },
        }
    {
    }

    void displayMainMenu()
    {
        cout << "Choose from:\n1 - Appetizer\n2 - Main Course\n3 - Sushi\n4 - Pizza\n9 - End Order" << endl;
    }
    void displayAppetizerMenu() {
        for(int i=0; i<sizeof(appetizer)/sizeof(appetizer[0]); ++i)
            cout << i+1 << ". " << appetizer[i].item << "\t" << appetizer[i].cost << endl;
    }
    void displayEntreeMenu() {
        for(int i=0; i<sizeof(entree)/sizeof(entree[0]); ++i)
            cout << i+1 << ". " << entree[i].item << "\t" << entree[i].cost << endl;
    }
    void displaySushiMenu() {
        for(int i=0; i<sizeof(sushi)/sizeof(sushi[0]); ++i)
            cout << i+1 << ". " << sushi[i].item << "\t" << sushi[i].cost << endl;
    }
    void displayPizzaMenu() {
        for(int i=0; i<sizeof(pizza)/sizeof(pizza[0]); ++i)
            cout << i+1 << ". " << pizza[i].item << "\t" << pizza[i].cost << endl;
    }
    void pickItem(MenuItem items[]) {
        int aI, aC;
        cout << "Please choose an item.\n";
        cin >> aI;
        cout << "How many you want?\n";
        cin >> aC;
        stringstream ss;
        ss << aC << "x " << items[aI - 1].item << " \t$" << items[aI - 1].cost * aC << endl;
        order += ss.str();
        total += items[aI - 1].cost * aC;
    }
    void printOrder() {
        cout << "Your order:\n\n" << order << endl;
        cout << "Total:                       \t$" << total << endl;
        cout << "Tax:                         \t$" << ((int)(total * 1.0875 * 100)) / 100.0 << endl;
    }
private:
    string order;
    double total;
};

int main() {
    cout << "Welcome to our Restaurant!\n";
    Menu menu;
    int choice = 0;
    while (choice != 9) {
        menu.displayMainMenu();
        cin >> choice;
        switch(choice) {
            case 1:
                menu.displayAppetizerMenu();
                menu.pickItem(menu.appetizer);
                break;
            case 2: 
                menu.displayEntreeMenu();
                menu.pickItem(menu.entree);
                break;
            case 3: 
                menu.displaySushiMenu();
                menu.pickItem(menu.sushi);
                break;
            case 4: 
                menu.displayPizzaMenu();
                menu.pickItem(menu.pizza);
                break;
            default: break;
        }
    }
    menu.printOrder();
    return 0;
}