#include <iostream>
#include "big_int.h"

int main()
{
    BigInt num1;
    std::cin >> num1;

    BigInt num2;
    std::cin >> num2;

    std::cout << num1 * num2 << std::endl;

    return EXIT_SUCCESS;
}