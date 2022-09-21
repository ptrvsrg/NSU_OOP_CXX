#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "string_arithmetic.h"

typedef unsigned char Byte;

class BigInt
{
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(const std::string&);
    BigInt(const BigInt&);
    BigInt(BigInt&&) noexcept ;
    ~BigInt();

    BigInt& operator=(const BigInt&);
    BigInt& operator=(BigInt&&) noexcept ;

    BigInt operator~() const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    // BigInt& operator|=(const BigInt&);
    // BigInt& operator&=(const BigInt&);
    // BigInt& operator^=(const BigInt&);

    // BigInt& operator++();
    // const BigInt operator++(int) const;
    // BigInt& operator--();
    // const BigInt operator--(int) const;

    BigInt operator+() const;
    BigInt operator-() const;

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    explicit operator int() const;
    explicit operator std::string() const;

    size_t size() const;
private:
    const unsigned int base_ = 256;
    bool isNegative_;
    std::vector <Byte> bytes_;

    void delete_null_bytes();
    bool null_byte();
};

// BigInt operator+(const BigInt&, const BigInt&);
// BigInt operator-(const BigInt&, const BigInt&);
// BigInt operator*(const BigInt&, const BigInt&);
// BigInt operator/(const BigInt&, const BigInt&);
// BigInt operator^(const BigInt&, const BigInt&);
// BigInt operator%(const BigInt&, const BigInt&);
// BigInt operator&(const BigInt&, const BigInt&);
// BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream&, const BigInt&);

#endif // BIG_INT_H