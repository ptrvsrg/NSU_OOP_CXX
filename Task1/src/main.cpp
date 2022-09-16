#include "big_int.h"

int main()
{
    BigInt number("255");
    std::cout << number << std::endl;
    std::cout << ~number << std::endl;
}