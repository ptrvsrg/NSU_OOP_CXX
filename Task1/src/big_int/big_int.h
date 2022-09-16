#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <string>
#include <vector>

#include "string_arithmetic.h"

typedef unsigned char Byte;

class BigInt
{
public:
    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

    BigInt operator~() const;

    // BigInt& operator++();
    // const BigInt operator++(int) const;
    // BigInt& operator--();
    // const BigInt operator--(int) const;

    // BigInt& operator+=(const BigInt&);
    // BigInt& operator*=(const BigInt&);
    // BigInt& operator-=(const BigInt&);
    // BigInt& operator/=(const BigInt&);
    // BigInt& operator^=(const BigInt&);
    // BigInt& operator%=(const BigInt&);
    // BigInt& operator&=(const BigInt&);
    // BigInt& operator|=(const BigInt&);

    BigInt operator+() const;
    BigInt operator-() const;

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    // operator int() const;
    operator std::string() const;

    size_t size() const;  // size in bytes

    friend std::ostream& operator<<(std::ostream& o, const BigInt& i);
private:
    const unsigned int base = 256;
    bool sign = false;
    std::vector <Byte> bytes;

    void DeleteNullBytes();
};

// BigInt operator+(const BigInt&, const BigInt&);
// BigInt operator-(const BigInt&, const BigInt&);
// BigInt operator*(const BigInt&, const BigInt&);
// BigInt operator/(const BigInt&, const BigInt&);
// BigInt operator^(const BigInt&, const BigInt&);
// BigInt operator%(const BigInt&, const BigInt&);
// BigInt operator&(const BigInt&, const BigInt&);
// BigInt operator|(const BigInt&, const BigInt&);

#endif // BIG_INT_H