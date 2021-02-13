#include<iostream>
using namespace std;
int main(){
	int i,num,sum;
	sum = 0;
	cout<<"enter the nums from the list: ";
	for (i=1; i<=5; i++) {
		cin>>num;
		sum += num;
	}
	cout<<sum<<endl;
	return 0;
}
