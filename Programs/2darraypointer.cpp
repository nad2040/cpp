#include <iostream>
#include <fmt/core.h>

int nums[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

long a = ((long)1 << 32) | 1;

int main()
{
    int *ptr = nums[0];
    for (int i = 0; i < 48; i++) {
        fmt::print("{:x} ", *ptr);
        ptr++;
    }
    return 0;
}