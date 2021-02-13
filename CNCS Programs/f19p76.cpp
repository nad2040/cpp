#include<iostream>
using namespace std;
int main(){
	int w,num;
	w = 1;
	cout<<"enter the nums from the list: ";
	do {
		cin>>num;
		if (w%2 != 0)
			cout<<num<<" ";
		w++;
	} while (w <= 5);
	return 0;
}