#include <iostream> 
#include <string> 
using namespace std; 

void demo();
void recur(int count) {
    if (count > 10) return;
    demo();
    recur(++count);
}
void demo() 
{  
    // static variable 
    
    static int count = 0; 
    //if (count == 10) exit(1);
    cout << ++count << " "; 
    //demo();
      
    // value is updated and 
    // will be carried to next 
    // function calls 
    
} 
  
int main() 
{ 
    //for (int i=0; i<5; i++)     
        //demo(); 
    recur(0);
    return 0; 
} 