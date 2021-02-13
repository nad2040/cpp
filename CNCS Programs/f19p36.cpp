#include <iostream>
using namespace std;
int main() {
	int w,num;
	w = 1;
	cout<<"enter the nums from list: ";
	while (w <= 5) {
		cin>>num;
		if (num > 0)
			cout<<num<<" ";
		w++;
	}
	return 0;
}
