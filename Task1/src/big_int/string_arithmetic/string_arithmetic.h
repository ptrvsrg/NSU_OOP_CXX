#ifndef STRING_ARITH_OPERATIONS_H
#define STRING_ARITH_OPERATIONS_H

#include <iostream>
#include <string>

class Addition
{
public:
    Addition(std::string, std::string);
    ~Addition();
    std::string GetSum();
private:
    std::string sum;
};

class Multiplication
{
public:
    Multiplication(std::string, std::string);
    ~Multiplication();
    std::string GetProduct();
private:
    std::string product;
};

class Division
{
public:
    Division(std::string dividend, int divisor);
    ~Division();
    std::string GetQuotient();
    std::string GetRemainder();
private:
    std::string quotient;
    std::string remainder;
};

#endif // STRING_ARITH_OPERATIONS_H