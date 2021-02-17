#include <iostream>

using namespace std;

int add(int a, int b) {
    return a+b;
}
int subtract(int a, int b) {
    return a-b;
}
int multiply(int a, int b) {
    return a*b;
}

int main()
{ 
    int (*add_ptr)(int, int) = &add;
    cout << (*add_ptr)(10,10);
    int (*sub_ptr)(int, int) = &subtract;
    cout << (*sub_ptr)(10,10);
    int (*mult_ptr)(int, int) = &multiply;
    cout << (*mult_ptr)(10,10);
  
    return 0; 
} 