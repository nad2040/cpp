#include<iostream>
using namespace std;
int main(){
	int i,num;
	cout<<"enter the nums from the list: ";
	for (i=1; i<=5; i++) {
		cin>>num;
		if (i == 1)
			cout<<num<<" ";
	}
	cout<<num<<" ";
	return 0;
}
