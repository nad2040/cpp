#include<iostream>
using namespace std;
int main(){
	int w,num,count;
	w = 1;
	cout<<"enter the nums from the list: ";
	count = 0;
	do {
		cin>>num;
		if (num == -7)
			count++;
		w++;
	} while (w <= 5);
	if (count != 0)
		cout<<"-7 exists\n";
	else
		cout<<"-7 doesn't exist\n";
	return 0;
}