#include<iostream>
using namespace std;
int main(){
	int i,num;
	cout<<"enter the nums from list: ";
	for (i=1; i<=5; i++) {
		cin>>num;
		if ((num%2 != 0)&&(num>=5)&&(num<=14))
			cout<<num<<" ";
	}
	return 0;
}
