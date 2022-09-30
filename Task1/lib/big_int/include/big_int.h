#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <cstdlib>
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
    ~BigInt();

    BigInt& operator=(const BigInt&);

    BigInt operator+() const;
    BigInt operator-() const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt operator~() const;
    BigInt& operator|=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator^=(const BigInt&);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    explicit operator int() const;
    explicit operator std::string() const;

    [[nodiscard]] size_t size() const;
private:
    const unsigned int base_ = 256;
    bool is_positive_;
    std::vector <Byte> bytes_;

    void delete_null_bytes();
    friend BigInt abs(const BigInt&);
    friend bool abs_compare(const BigInt&, const BigInt&);
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);

BigInt operator|(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream&, const BigInt&);
std::istream& operator>>(std::istream&, BigInt&);

#endif // BIG_INT_H