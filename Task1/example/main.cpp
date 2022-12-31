#include <iostream>
#include "big_int.h"

int main(int argc, char ** argv)
{
    if (argc >= 3)
    {
        BigInt num1(argv[1]);
        BigInt num2(argv[2]);

        std::cout << num1 * num2 << std::endl;
    }

    return EXIT_SUCCESS;
}