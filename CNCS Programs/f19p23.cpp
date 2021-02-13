#include <iostream>
using namespace std;

int main(){
	int s;
	cin>>s;
	switch(s/10)
	{
		case 10: cout<<"Your grade is A\n";
			break;
		case 9: cout<<"Your grade is A\n";
			break;
		case 8: cout<<"Your grade is B\n";
			break;
		case 7: cout<<"Your grade is C\n";
			break;
		case 6: cout<<"Your grade is D\n";
			break;
		default: cout<<"Your grade is F\n";
	}
	return 0;
}
