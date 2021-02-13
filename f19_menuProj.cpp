#include<iostream>
#include<string>
using namespace std;

void appetizer();
void mainCourse();
void dessert();
void yourOrder();
int yourTotal();

int order = 0;
int toppings = 0;
int welldone = 0;
int sushi = 0;
int counta = 0;
int countm = 0;
int countd = 0;
float total = 0;
const double tax = 1.08875;

int main() {
	cout << "Welcome to Our Restaurant!\n" << "Here is the menu: " << endl;
	appetizer();
	mainCourse();
	dessert();
	yourOrder();
	return 0;
}
void appetizer() {
	int a,count;
	cout << "What appetizer do you want?\n";
	cout << "Enter:\n1 - Fruit Salad $4.50\n2 - Popcorn Chicken $4.00\n3 - Sweet Potato Fries $2.00\n4 - Hors d'oeuvres $3.00" << endl;
	cin >> a;
	cout << "How many do you want?\n";
	cin >> count;
	counta = count;
	order += a;
	order *= 10;
}
void mainCourse() {
	int a,b,c,d,count;
	cout << "What main dish do you want?\n";
	cout << "Enter:\n1 - Steak $14.00\n2 - Caesar Salad $7.00\n3 - Sushi Platter $25.00\n4 - Pizza Pie $10.00\n5 - Shrimp & Broccoli Stir Fry $10.00" << endl;
	cin >> a;
	cout << "How many do you want?\n";
	cin >> count;
	countm = count;
	order += a;
	order *= 10;
	switch(a) {
		case 1: {
			cout << "How do you want your steak done?\n";
			cout << "Enter:\n1 - Rare\n2 - Medium Rare\n3 - Medium\n4 - Medium Well\n5 - Well Done" << endl;
			cin >> c;
			welldone += c;
			break;
		}
		case 2: {
			cout << "What toppings do you want?\n";
			cout << "Enter:\n1 - Croutons +$1.00\n2 - Diced Tomatoes +$1.00" << endl;
			cin >> b;
			toppings += b;
			break;
			}
		case 3: {
			cout << "What type of Sushi do you want?\n";
			cout << "Enter:\n1 - California Roll\n2 - Eel Roll\n3 - Shrimp Tempura Roll\n4 - Salmon Roll" << endl;
			cin >> d;
			sushi += d;
			break;
		}
		case 4: {
			cout << "What toppings do you want?\n";
			cout << "Enter:\n1 - Pepperonis +$1.50\n2 - Mushrooms +$2.00\n3 - Broccoli +$1.50\n4 - Bacon +$2.50" << endl;
			cin >> b;
			toppings += b;
			break;
		}
		default:;
	}
}
void dessert() {
	int a,count;
	cout << "What dessert do you want?\n";
	cout << "Enter:\n1 - Mango Sorbet $5.00\n2 - Vanilla Sundae w/ Cherry $5.50\n3 - Chocolate Mousse $4.50\n4 - Fruit Cake $3.00" << endl;
	cin >> a;
	cout << "How many do you want?\n";
	cin >> count;
	countd = count;
	order += a;
}
void yourOrder() {
	cout << "You ordered:\n";
//	cout << order/100 %10;
	cout << counta << "x ";
	switch(order/100 %10) {
		case 1: cout << "Fruit Salad\n";
			total += 4.50*counta;
			break;
		case 2: cout << "Popcorn Chicken\n";
			total += 4.00*counta;
			break;
		case 3: cout << "Sweet Potato Fries\n";
			total += 2.00*counta;
			break;
		case 4: cout << "Hors d'oeuvres\n";
			total += 3.00*counta;
			break;
		default: break;
	}
//	cout << order/10 %10;
	cout << countm << "x ";
	switch(order/10 %10) {
		case 1: {
			switch(welldone) {
				case 1: cout << "Rare Steak\n";
					total += 14.00*countm;
					break;
				case 2: cout << "Medium-Rare Steak\n";
					total += 14.00*countm;
					break;
				case 3: cout << "Medium Steak\n";
					total += 14.00*countm;
					break;
				case 4: cout << "Medium-Well Steak\n";
					total += 14.00*countm;
					break;
				case 5: cout << "Well-Done Steak\n";
					total += 14.00*countm;
					break;
				default: break;
			}
			break;
		}
		case 2: {
			switch(toppings) {
				case 1: cout << "Caesar Salad w/ Croutons\n";
					total += 8.00*countm;
					break;
				case 2: cout << "Caesar Salad w/ Diced Tomatoes\n";
					total += 8.00*countm;
					break;
				default: break;
			}
			break;
		}
		case 3: {
			switch(sushi) {
				case 1: cout << "California Roll Sushi Platter\n";
					break;
				case 2: cout << "Eel Roll Sushi Platter\n";
					break;
				case 3: cout << "Shrimp Tempura Roll Sushi Platter\n";
					break;
				case 4: cout << "Salmon Roll Sushi Platter\n";
					break;
				default: break;
			}
			break;
		}
		case 4: {
			switch(toppings) {
				case 1: cout << "Pepperoni Pizza\n";
					break;
				case 2: cout << "Mushroom Pizza\n";
					break;
				case 3: cout << "Broccoli Pizza\n";
					break;
				case 4: cout << "Bacon Pizza\n";
					break;
				default: break;
			}
			break;
		}
		case 5: cout << "Shrimp & Broccoli Stir Fry\n";
			break;
		default: break;
	}
//	cout << order %10;
	cout << countd << "x ";
	switch(order %10) {
		case 1: cout << "Mango Sorbet\n";
			break;
		case 2: cout << "Vanilla Sundae w/ Cherry\n";
			break;
		case 3: cout << "Chocolate Mousse\n";
			break;
		case 4: cout << "Fruit Cake\n";
			break;
		default: break;
	}
	cout << "Your total is: " << total << endl;
	cout << "After tax: " << (total*tax*100+0.5)/100 << endl;
}
