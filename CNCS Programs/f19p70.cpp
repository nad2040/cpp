#include <iostream>
using namespace std;
int main(){
	int w,num;
	w = 1;
	cout<<"enter a num from the list: ";
	do {
		cin>>num;
		cout<<num<<endl;
		w++;
	} while (w<=5);
	return 0;
}
