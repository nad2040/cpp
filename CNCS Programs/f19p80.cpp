#include<iostream>
using namespace std;
int main() {
	int i,j,k;
	for (i=5; i<=7; i++)
		for (j=1; j<=2; j++)
			for (k=10; k<=13; k++){
				cout<<i<<" "<<j<<" "<<k<<endl;
				cout<<"Nested\n";
			}
	return 0;
}
