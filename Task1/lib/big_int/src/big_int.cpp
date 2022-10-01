#include "big_int.h"

BigInt::BigInt()
{
    is_positive_ = true;
    bytes_.push_back(0);
}

BigInt::BigInt(int num)
{
    is_positive_ = (num >= 0);
    
    union UInt
    {
        unsigned int bit32;
        Byte bit8[4];
    } bits{};

    bits.bit32 = abs(num);
    bytes_ = std::vector<Byte>(std::cbegin(bits.bit8), std::cend(bits.bit8));

    this->delete_null_bytes();
}

BigInt::BigInt(const std::string & str)
{
    if (str.empty())
    {
        *this = BigInt();
        return;
    }

    is_positive_ = (str[0] != '-');

    if (!is_positive_ && str.size() == 1)
    {
        throw std::invalid_argument("Wrong number");
    }

    String quotient(is_positive_ ? str : str.substr(1, str.size()));
    String base(std::to_string(base_));

    while (base <= quotient)
    {
        bytes_.push_back((Byte)stoi((quotient % base).to_string()));
        quotient /= base;
    }

    bytes_.push_back((Byte)stoi(quotient.to_string()));

    if (*(bytes_.crbegin()) == 0)
    {
        is_positive_ = true;
    }
}

BigInt::BigInt(const BigInt & src)
{
    is_positive_ = src.is_positive_;
    bytes_.assign(src.bytes_.begin(), src.bytes_.end());
}

BigInt::~BigInt()
{
    bytes_.clear();
    bytes_.shrink_to_fit();
}



BigInt & BigInt::operator=(const BigInt & src)
{
    if (this != &src)
    {
        is_positive_ = src.is_positive_;
        bytes_.assign(src.bytes_.begin(), src.bytes_.end());
    }

    return *this;
}

BigInt & BigInt::operator+=(const BigInt & addend)
{
    if (is_positive_ ^ addend.is_positive_)
    {
        is_positive_ = !is_positive_;
        *this -= addend;
        is_positive_ = !is_positive_;
        return *this;
    }

    auto addendIter = addend.bytes_.cbegin();
    auto addendEnd = addend.bytes_.cend();

    auto sumIter = bytes_.begin();
    auto sumEnd = bytes_.end();

    unsigned int carry = 0;
    while (sumIter < sumEnd || addendIter < addendEnd)
    {
        if(addendIter < addendEnd)
        {
            carry += *addendIter;
            ++addendIter;
        }

        if (sumIter < sumEnd)
        {
            carry += *sumIter;
            *sumIter = carry % base_;
            ++sumIter;
        }
        else
        {
            bytes_.push_back(carry % base_);
        }

        carry /= base_;
    }

    if (carry != 0)
    {
        bytes_.push_back(carry);
    }

    return *this;
}

BigInt & BigInt::operator-=(const BigInt & subtrahend)
{
    if (is_positive_ ^ subtrahend.is_positive_)
    {
        is_positive_ = !is_positive_;
        *this += subtrahend;
        is_positive_ = !is_positive_;
        return *this;
    }

    bool absCmp = abs_compare(*this, subtrahend);

    auto minuendIter = absCmp ? bytes_.cbegin() : subtrahend.bytes_.cbegin();
    auto minuendEnd = absCmp ? bytes_.cend() : subtrahend.bytes_.cend();

    auto subtrahendIter = absCmp ? subtrahend.bytes_.cbegin() : bytes_.cbegin();
    auto subtrahendEnd = absCmp ? subtrahend.bytes_.cend() : bytes_.cend();

    auto differenceIter = bytes_.begin();
    auto differenceEnd = bytes_.end();

    is_positive_ = (absCmp == is_positive_);

    int carry = 0;
    while (minuendIter < minuendEnd || subtrahendIter < subtrahendEnd)
    {
        if(minuendIter < minuendEnd)
        {
            carry += *minuendIter;
            ++minuendIter;
        }

        if(subtrahendIter < subtrahendEnd)
        {
            carry -= *subtrahendIter;
            ++subtrahendIter;
        }

        if (differenceIter < differenceEnd)
        {
            *differenceIter = (carry >= 0) ? carry : base_ + carry;
            ++differenceIter;
        }
        else
        {
            bytes_.push_back(carry % base_);
        }

        carry = (carry >= 0) ? 0 : -1;
    }

    delete_null_bytes();
    return *this;
}

BigInt & BigInt::operator*=(const BigInt & multiplier2)
{
    BigInt multiplier1(*this);
    *this = BigInt();

    for (auto multiplierIter1 = multiplier1.bytes_.cbegin(); multiplierIter1 < multiplier1.bytes_.cend(); ++multiplierIter1)
    {
        BigInt buffer;
        buffer.bytes_.clear();
        buffer.bytes_.insert(buffer.bytes_.cbegin(), multiplierIter1 - multiplier1.bytes_.cbegin(), 0);

        unsigned int carry = 0;
        for (auto multiplierIter2 = multiplier2.bytes_.cbegin(); multiplierIter2 < multiplier2.bytes_.cend(); ++multiplierIter2)
        {
            carry += (*multiplierIter1) * (*multiplierIter2);
            buffer.bytes_.push_back(carry % base_);
            carry /= base_;
        }

        if (carry != 0)
        {
            buffer.bytes_.push_back(carry);
        }

        *this += buffer;
    }

    is_positive_ = !(multiplier1.is_positive_ ^ multiplier2.is_positive_);
    delete_null_bytes();

    return *this;
}

BigInt & BigInt::operator/=(const BigInt & divisor)
{
    if (divisor == BigInt(0))
    {
        throw std::invalid_argument("Division by zero");
    }

    BigInt dividend(*this);
    bytes_.clear();

    BigInt remainder;
    remainder.bytes_.clear();

    auto dividendIter = dividend.bytes_.crbegin();
    while (dividendIter < dividend.bytes_.crend())
    {
        remainder.bytes_.insert(remainder.bytes_.cbegin(), *dividendIter);
        ++dividendIter;
        remainder.delete_null_bytes();

        unsigned int carry = 0;
        while (abs_compare(remainder, divisor))
        {
            remainder -= abs(divisor);
            ++carry;
        }

        bytes_.insert(bytes_.cbegin(), carry);
    }

    is_positive_ = !(dividend.is_positive_ ^ divisor.is_positive_);
    delete_null_bytes();

    return *this;
}

BigInt & BigInt::operator%=(const BigInt & divisor)
{
    if (divisor == BigInt(0))
    {
        throw std::invalid_argument("Division by zero");
    }

    BigInt dividend(*this);
    bytes_.clear();
    is_positive_ = true;

    auto dividendIter = dividend.bytes_.crbegin();
    while (dividendIter < dividend.bytes_.crend())
    {
        bytes_.insert(bytes_.cbegin(), *dividendIter);
        ++dividendIter;
        delete_null_bytes();

        while (abs_compare(*this, divisor))
        {
            *this -= abs(divisor);
        }
    }

    is_positive_ = dividend.is_positive_;
    delete_null_bytes();

    return *this;
}

BigInt & BigInt::operator|=(const BigInt & bits)
{
    is_positive_ = is_positive_ && bits.is_positive_;

    auto bitsIter = bits.bytes_.cbegin();
    auto resultIter = bytes_.begin();

    while (resultIter < bytes_.end() || bitsIter < bits.bytes_.cend())
    {
        Byte carry = 0;
        if(bitsIter < bits.bytes_.cend())
        {
            carry = *bitsIter;
            ++bitsIter;
        }

        if (resultIter < bytes_.end())
        {
            *resultIter |= carry;
            ++resultIter;
        }
        else
        {
            bytes_.push_back(carry);
        }
    }

    return *this;
}

BigInt & BigInt::operator&=(const BigInt & bits)
{
    is_positive_ = is_positive_ || bits.is_positive_;

    auto bitsIter = bits.bytes_.cbegin();
    auto resultIter = bytes_.begin();

    while (resultIter < bytes_.end() && bitsIter < bits.bytes_.cend())
    {
        *resultIter &= *bitsIter;
        ++bitsIter;
        ++resultIter;
    }

    if (resultIter < bytes_.end())
    {
        bytes_.erase(resultIter, bytes_.end());
    }

    return *this;
}

BigInt & BigInt::operator^=(const BigInt & bits)
{
    is_positive_ = !(is_positive_ ^ bits.is_positive_);

    auto bitsIter = bits.bytes_.cbegin();
    auto resultIter = bytes_.begin();

    while (resultIter < bytes_.end() || bitsIter < bits.bytes_.cend())
    {
        Byte carry = 0;
        if(bitsIter < bits.bytes_.cend())
        {
            carry = *bitsIter;
            ++bitsIter;
        }

        if (resultIter < bytes_.end())
        {
            *resultIter ^= carry;
            ++resultIter;
        }
        else
        {
            bytes_.push_back(carry);
        }
    }

    delete_null_bytes();
    return *this;
}



BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt tmp(*this);
    tmp.is_positive_ = !is_positive_;
    return tmp;
}



BigInt & BigInt::operator++()
{
    *this += BigInt(1);
    return *this;
}

const BigInt BigInt::operator++(int)
{
    BigInt tmp(*this);
    ++(*this);
    return tmp;
}

BigInt & BigInt::operator--()
{
    *this -= BigInt(1);
    return *this;
}

const BigInt BigInt::operator--(int)
{
    BigInt tmp(*this);
    --(*this);
    return tmp;
}



bool BigInt::operator==(const BigInt & cmp) const
{
    if (is_positive_ ^ cmp.is_positive_)
    {
        return false;
    }

    if (bytes_.size() != cmp.size())
    {
        return false;
    }
    
    for (int i = (int)bytes_.size() - 1; i >= 0; i--)
    {
        if (bytes_[i] != cmp.bytes_[i])
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator!=(const BigInt & cmp) const
{
    return !((*this) == cmp);
}

bool BigInt::operator<(const BigInt & cmp) const
{
    if (is_positive_ ^ cmp.is_positive_)
    {
        return cmp.is_positive_;
    }

    if (bytes_.size() != cmp.size())
    {
        return is_positive_ ^ (cmp.size() < bytes_.size());
    }

    for (int i = (int)bytes_.size() - 1; i >= 0 ; i--)
    {
        if (bytes_[i] != cmp.bytes_[i])
        {
            return is_positive_ ^ (cmp.bytes_[i] < bytes_[i]);
        }
    }

    return false;
}

bool BigInt::operator>(const BigInt & cmp) const
{
    return !(*this < cmp) && !(*this == cmp);
}

bool BigInt::operator<=(const BigInt & cmp) const
{
    return !((*this) > cmp);
}

bool BigInt::operator>=(const BigInt & cmp) const
{
    return !((*this) < cmp);
}



BigInt BigInt::operator~() const
{
    BigInt tmp(*this);

    for (Byte & byte : tmp.bytes_)
    {
        byte = ~byte;
    }

    tmp.is_positive_ = !tmp.is_positive_;
    tmp.delete_null_bytes();

    return tmp;
}



BigInt::operator int() const
{
    if (bytes_.size() > 4)
    {
        throw std::invalid_argument("Int overflow");
    }

    union UInt
    {
        int bit32;
        Byte bit8[4];
    } intNum{};

    std::copy(bytes_.begin(), bytes_.end(), intNum.bit8);

    return (is_positive_) ? intNum.bit32 : -intNum.bit32;
}

BigInt::operator std::string() const
{
    String number;
    for (auto byteIter = bytes_.crbegin(); byteIter != bytes_.crend(); ++byteIter)
    {
        String base(std::to_string(base_));
        String byte(std::to_string(*byteIter));

        number *= base;
        number += byte;
    }

    std::string numberStr = number.to_string();
    if (!is_positive_ && numberStr != "0")
    {
        numberStr.insert(numberStr.cbegin(), '-');
    }

    return numberStr;
}



size_t BigInt::size() const
{
    return bytes_.size();
}

void BigInt::delete_null_bytes()
{
    while (*(bytes_.rbegin()) == 0 && bytes_.size() > 1)
    {
        bytes_.pop_back();
    }
}

BigInt abs(const BigInt & num)
{
    BigInt absNum(num);
    absNum.is_positive_ = true;
    return absNum;
}

bool abs_compare(const BigInt & cmp1, const BigInt & cmp2)
{
    return abs(cmp1) >= abs(cmp2);
}



BigInt operator+(const BigInt & addend1, const BigInt & addend2)
{
    BigInt sum(addend1);
    sum += addend2;
    return sum;
}

BigInt operator-(const BigInt & minuend, const BigInt & subtrahend)
{
    BigInt difference(minuend);
    difference -= subtrahend;
    return difference;
}

BigInt operator*(const BigInt & multiplier1, const BigInt & multiplier2)
{
    BigInt product(multiplier1);
    product *= multiplier2;
    return product;
}

BigInt operator/(const BigInt & dividend, const BigInt & divisor)
{
    BigInt quotient(dividend);
    quotient /= divisor;
    return quotient;
}

BigInt operator%(const BigInt & dividend, const BigInt & divisor)
{
    BigInt remainder(dividend);
    remainder %= divisor;
    return remainder;
}

BigInt operator|(const BigInt & bits1, const BigInt & bits2)
{
    BigInt result(bits1);
    result |= BigInt(bits2);
    return result;
}

BigInt operator&(const BigInt & bits1, const BigInt & bits2)
{
    BigInt result(bits1);
    result &= BigInt(bits2);
    return result;
}

BigInt operator^(const BigInt & bits1, const BigInt & bits2)
{
    BigInt result(bits1);
    result ^= BigInt(bits2);
    return result;
}



std::ostream & operator<<(std::ostream & out, const BigInt & num)
{
    out << std::string(num);
    return out;
}

std::istream & operator>>(std::istream & in, BigInt & num)
{
    std::string str;
    in >> str;
    num = BigInt(str);
    return in;
}
