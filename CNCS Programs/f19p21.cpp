#include<iostream>
using namespace std;
int main(){
	int a;
	cout<<"Enter a number: ";
	cin>>a;
	switch(a)
	{
		case 5:cout<<"five\n";
			break;
		case 7:cout<<"seven\n";
			break;
		case 9:cout<<"nine\n";
			break;
		default:cout<<"none\n";
			break;
	}
	return 0;
}
