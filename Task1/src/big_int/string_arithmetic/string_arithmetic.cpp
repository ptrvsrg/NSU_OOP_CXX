#include "string_arithmetic.h"

static int CharToInt(char sym)
{
    return sym - '0';
}

static char IntToChar(int digit)
{
    return digit + '0';
}

static bool IsDigit(char sym)
{
    return sym >= '0' && sym <= '9';
}

static void RemoveBeginZero(std::string& number)
{
    while (number[0] == '0')
    {
        number.erase(number.begin(), number.begin() + 1);
    }
}

Addition::Addition(std::string addend1, std::string addend2)
{
    int carry = 0;
    auto iter1 = addend1.rbegin();
    auto iter2 = addend2.rbegin();
    
    while (iter1 != addend1.rend() || iter2 != addend2.rend())
    {
        if(iter1 != addend1.rend())
        {
            if (!IsDigit(*iter1))
            {
                throw std::invalid_argument("Invalid symbol");
            }

            carry += CharToInt(*iter1);
            ++iter1;
        }

        if(iter2 != addend2.rend())
        {
            if (!IsDigit(*iter2))
            {
                throw std::invalid_argument("Invalid symbol");
            }

            carry += CharToInt(*iter2);
            ++iter2;
        }
        
        sum.insert(sum.begin(), IntToChar(carry % 10));
        carry /= 10;
    }

    if (carry != 0)
    {
        sum.insert(sum.begin(), IntToChar(carry));
    }
}

std::string Addition::GetSum()
{
    return sum;
}

Addition::~Addition()
{
    sum.clear();
}

Multiplication::Multiplication(std::string multiplier, std::string multiplicand)
{
    auto iter1 = multiplier.rbegin();

    while (iter1 != multiplier.rend())
    {
        std::string buffer;
        buffer.insert(buffer.begin(), iter1 - multiplier.rbegin(), '0');

        int carry = 0;
        auto iter2 = multiplicand.rbegin();

        while (iter2 != multiplicand.rend())
        {
            carry += CharToInt(*iter1) * CharToInt(*iter2);
            buffer.insert(buffer.begin(), IntToChar(carry % 10));
            carry /= 10;
            ++iter2;
        }

        if (carry != 0)
        {
            buffer.insert(buffer.begin(), IntToChar(carry));
        }

        product = Addition(product, buffer).GetSum();
        ++iter1;
    }
}

std::string Multiplication::GetProduct()
{
    return product;
}

Multiplication::~Multiplication()
{
    product.clear();
}

Division::Division(std::string dividend, int divisor)
{
    int buffer = 0;
    for (auto iter = dividend.begin(); iter != dividend.end(); ++iter)
    {
        if (!IsDigit(*iter))
        {
            throw std::invalid_argument("Invalid symbol");
        }

        buffer = buffer * 10 + CharToInt(*iter);
        if (buffer < divisor)
        {
            quotient.push_back('0');
            continue;
        }

        quotient.push_back(IntToChar(buffer / divisor));
        buffer %= divisor;
    }

    RemoveBeginZero(quotient);
    remainder = std::to_string(buffer);
}

Division::~Division()
{
    quotient.clear();
    remainder.clear();
}

std::string Division::GetQuotient()
{
    return quotient;
}

std::string Division::GetRemainder()
{
    return remainder;
}
