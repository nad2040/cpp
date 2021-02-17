#include <iostream>
int main() {
    int i = 0;
    int sum = 0;
    while (i<=10) {
        sum += i;
        //++i;
        i += 2;
    }
    std::cout << sum << '\n';

    sum = 0;
    for(i=0; i<=10; i+=2) {
        sum += i;
    }
    std::cout << sum << '\n';

    i = 1;
    sum = 0;
    do {
        sum += i;
        i += 2;
    } while(i<=10);
    std::cout << sum << '\n';
}