#include<iostream>
using namespace std;
int main(){
	int s;
	cout<<"Enter a score 0-100: ";
	cin>>s;
	switch(s)
	{
		case 60 ... 70:
			cout<<"Grade is D";
			break;
		default:
			break;
	}
	return 0;
}
