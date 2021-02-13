#include<iostream>
using namespace std;

int main(){
	int a,b,x,y;
	cout<<"Hi\n";
	cout<<"enter 2 numbers:\n";
	cin>>a>>b;
	if (a == 5) {
		cout<<"five\n";
		b = 2*a;
		cout<<"b = "<<b<<endl;
		}
	else if (a > b) {
			x = 2*b;
			cout<<"x = "<<x<<endl;
			}
		else {
			y = 2*a;
			cout<<"a = "<<a<<endl<<"b = "<<b<<endl<<"y = "<<y<<endl;
			}
	
	return 0;
}
