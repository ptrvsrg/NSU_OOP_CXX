#include "big_int.h"

BigInt::BigInt()
{}

BigInt::BigInt(int number)
{
    sign = (number < 0);
    
    union
    {
        unsigned int bit32;
        Byte bit8[4];
    };
    bit32 = number;
    bytes.assign(bit8, bit8 + 4);
}

BigInt::BigInt(std::string digitString)
{
    if (digitString.size() == 0)
    {
        return;
    }

    if (digitString[0] == '-')
    {
        sign = true;
        digitString.erase(digitString.begin());
    }
    
    while (digitString.size() > 3U || (unsigned int)atoi(digitString.c_str()) >= base)
    {
        Division tmp(digitString, base);
        digitString = tmp.GetQuotient();
        bytes.insert(bytes.begin(), (Byte)atoi(tmp.GetRemainder().c_str()));
    }
    
    if (atoi(digitString.c_str()) != 0)
    {
        bytes.insert(bytes.begin(), (Byte)atoi(digitString.c_str()));
    }
}

BigInt::BigInt(const BigInt& src)
{
    sign = src.sign;
    bytes.clear();
    bytes.assign(src.bytes.begin(), src.bytes.end());
}

BigInt::~BigInt()
{
    bytes.clear();
}

BigInt& BigInt::operator=(const BigInt& src)
{
    if (this == &src)
    {
        return *this;
    }

    sign = src.sign;
    bytes.clear();
    bytes.assign(src.bytes.begin(), src.bytes.end());

    return *this;
}

BigInt BigInt::operator~() const
{
    BigInt tmp(*this);
    for (auto iter = tmp.bytes.begin(); iter != tmp.bytes.end(); ++iter)
    {
        *iter = ~(*iter);
    }

    tmp.DeleteNullBytes();

    return tmp;
}

BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt tmp(*this);
    tmp.sign = !sign;
    return tmp;
}

bool BigInt::operator==(const BigInt& cmp) const
{
    if (bytes.size() != cmp.size())
    {
        return false;
    }
    
    for (int i = 0; i < bytes.size(); ++i)
    {
        if (bytes[i] != cmp.bytes[i])
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator!=(const BigInt& cmp) const
{
    if (bytes.size() != cmp.size())
    {
        return true;
    }
    
    for (int i = 0; i < bytes.size(); ++i)
    {
        if (bytes[i] != cmp.bytes[i])
        {
            return true;
        }
    }

    return false;
}

bool BigInt::operator<(const BigInt& cmp) const
{
    if (bytes.size() != cmp.size())
    {
        return bytes.size() < cmp.size();
    }
    
    for (int i = 0; i < bytes.size(); ++i)
    {
        if (bytes[i] != cmp.bytes[i])
        {
            return bytes[i] < cmp.bytes[i];
        }
    }

    return false;
}

bool BigInt::operator>(const BigInt& cmp) const
{
    if (bytes.size() != cmp.size())
    {
        return bytes.size() > cmp.size();
    }
    
    for (int i = 0; i < bytes.size(); ++i)
    {
        if (bytes[i] != cmp.bytes[i])
        {
            return bytes[i] > cmp.bytes[i];
        }
    }

    return false;
}

bool BigInt::operator<=(const BigInt& cmp) const
{
    if (bytes.size() != cmp.size())
    {
        return bytes.size() < cmp.size();
    }
    
    for (int i = 0; i < bytes.size(); ++i)
    {
        if (bytes[i] != cmp.bytes[i])
        {
            return bytes[i] < cmp.bytes[i];
        }
    }

    return true;
}

bool BigInt::operator>=(const BigInt& cmp) const
{
    if (bytes.size() != cmp.size())
    {
        return bytes.size() > cmp.size();
    }
    
    for (int i = 0; i < bytes.size(); ++i)
    {
        if (bytes[i] != cmp.bytes[i])
        {
            return bytes[i] > cmp.bytes[i];
        }
    }

    return true;
}

BigInt::operator std::string() const
{
    std::string strBase = std::to_string(base);
    std::string baseMultiplier = "1";
    std::string number;

    for (auto iter = bytes.rbegin(); iter != bytes.rend(); ++iter)
    {
        std::string product = Multiplication(std::to_string(*iter), baseMultiplier).GetProduct();
        number = Addition(number, product).GetSum();
        baseMultiplier = Multiplication(strBase, baseMultiplier).GetProduct();
    }

    if (sign)
    {
        number.insert(number.begin(), '-');
    }

    return number;
}

size_t BigInt::size() const
{
    return bytes.size();
}

std::ostream& operator<<(std::ostream& out, const BigInt& num)
{
    out << std::string(num);
    return out;
}

void BigInt::DeleteNullBytes()
{
    for (auto iter = bytes.begin(); iter != bytes.end() && *iter == 0; ++iter)
    {
        bytes.erase(iter);
    }
}
