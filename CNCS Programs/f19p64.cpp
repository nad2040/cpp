#include <iostream>
using namespace std;
int main(){
	int w;
	w = 1;
	do {
		if (w%2==0)
			cout<<w<<" ";
		w=w+1;
	} while (w<=19);
	return 0;
}