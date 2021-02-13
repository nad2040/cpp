#include<iostream>
using namespace std;
int main(){
	int w,num;
	w = 1;
	cout<<"enter the nums from the list: ";
	while (w <= 5) {
		cin>>num;
		if (w == 1)
			cout<<num<<" ";
		w++;
	}
	cout<<num<<" ";
	return 0;
}
