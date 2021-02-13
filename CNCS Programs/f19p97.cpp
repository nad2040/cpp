//p97
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int n[10];
	for (int i=0; i<10; i++)
		n[i]=0;
	cout << "Element" << setw(13) << "Value" << endl;
	for (int i=0; i<10; i++)
		cout << setw(7) << i << setw(13) << n[i] << endl;
	return 0;
}
