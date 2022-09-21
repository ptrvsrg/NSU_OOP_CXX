#include "big_int.h"

BigInt::BigInt()
{
    isNegative_ = false;
    bytes_.clear();
    bytes_.shrink_to_fit();
}

BigInt::BigInt(int number)
{
    isNegative_ = (number < 0);
    
    union UInt
    {
        unsigned int bit32;
        Byte bit8[4];
    } num{};

    num.bit32 = abs(number);
    bytes_ = std::vector<Byte>(std::cbegin(num.bit8), std::cend(num.bit8));

    this->delete_null_bytes();
}

BigInt::BigInt(const std::string& str)
{
    if (str.empty())
    {
        *this = BigInt();
        return;
    }

    isNegative_ = (str[0] == '-');

    if (str.empty() || (isNegative_ && str.size() == 1))
    {
        throw std::invalid_argument("Wrong string number");
    }

    String quotient((str[0] == '-') ? str.substr(1, str.size()) : str);
    String base(std::to_string(base_));
    while (base < quotient)
    {
        bytes_.push_back((Byte)stoi((quotient % base).to_string()));
        quotient /= base;
    }

    bytes_.push_back((Byte)stoi(quotient.to_string()));
}

BigInt::BigInt(const BigInt& src)
{
    isNegative_ = src.isNegative_;
    bytes_.assign(src.bytes_.begin(), src.bytes_.end());
}

BigInt::BigInt(BigInt&& src) noexcept
{
    isNegative_ = src.isNegative_;
    bytes_ = std::move(src.bytes_);
}

BigInt::~BigInt()
{
    bytes_.clear();
    bytes_.shrink_to_fit();
}

BigInt& BigInt::operator=(const BigInt& src)
{
    if (this == &src)
    {
        return *this;
    }

    isNegative_ = src.isNegative_;
    bytes_.assign(src.bytes_.begin(), src.bytes_.end());

    return *this;
}

BigInt &BigInt::operator=(BigInt && tmp) noexcept
{
    isNegative_ = tmp.isNegative_;
    bytes_ = std::move(tmp.bytes_);
    return *this;
}

BigInt BigInt::operator~() const
{
    BigInt tmp(*this);

    for (unsigned char & byte : tmp.bytes_)
    {
        byte = ~byte;
    }

    tmp.delete_null_bytes();

    return tmp;
}

BigInt &BigInt::operator+=(const BigInt & addend2)
{
    if (isNegative_ ^ addend2.isNegative_)
    {
        isNegative_ = !isNegative_;
        *this -= addend2;
        isNegative_ = !isNegative_;
        return *this;
    }

    BigInt addend1(*this);
    bytes_.clear();

    unsigned int carry = 0;
    auto addend1_= addend1.bytes_.begin();
    auto addend2_ = addend2.bytes_.begin();

    while (addend1_ != addend1.bytes_.end() || addend2_ != addend2.bytes_.end())
    {
        if(addend1_ != addend1.bytes_.end())
        {
            carry += *addend1_;
            ++addend1_;
        }

        if(addend2_ != addend2.bytes_.end())
        {
            carry += *addend2_;
            ++addend2_;
        }

        bytes_.push_back(carry % base_);
        carry /= base_;
    }

    if (carry != 0)
    {
        bytes_.push_back(carry);
    }

    return *this;
}

BigInt &BigInt::operator*=(const BigInt & multiplier2)
{
    BigInt multiplier1(*this);
    *this = BigInt();

    for (int i = 0; i < multiplier1.size(); ++i)
    {
        BigInt buffer;
        buffer.bytes_.clear();
        buffer.bytes_.insert(buffer.bytes_.begin(), i, 0);

        unsigned int carry = 0;
        for (int j = 0; j < multiplier2.size(); ++j)
        {
            carry += multiplier1.bytes_[i] * multiplier2.bytes_[j];
            buffer.bytes_.push_back(carry % base_);
            carry /= base_;
        }

        if (carry != 0)
        {
            buffer.bytes_.push_back(carry);
        }

        *this += buffer;
    }

    isNegative_ = (multiplier1.isNegative_ ^ multiplier2.isNegative_);
    delete_null_bytes();
    return *this;
}

BigInt &BigInt::operator-=(const BigInt & subtrahend)
{
    if (isNegative_ ^ subtrahend.isNegative_)
    {
        isNegative_ = !isNegative_;
        *this += subtrahend;
        isNegative_ = !isNegative_;
        return *this;
    }

    BigInt minuend(*this);
    bytes_.clear();

    bool absCmp = (isNegative_ ^ (subtrahend < minuend));
    auto minuend_ = absCmp ? minuend.bytes_.begin() : subtrahend.bytes_.begin();
    auto subtrahend_ = absCmp ? subtrahend.bytes_.begin() : minuend.bytes_.begin();
    auto minuendEnd = absCmp ? minuend.bytes_.end() : subtrahend.bytes_.end();
    auto subtrahendEnd = absCmp ? subtrahend.bytes_.end() : minuend.bytes_.end();
    isNegative_ = (absCmp == minuend.isNegative_);

    int carry = 0;

    while (minuend_ != minuendEnd || subtrahend_ != subtrahendEnd)
    {
        if(minuend_ != minuendEnd)
        {
            carry += *minuend_;
            ++minuend_;
        }

        if(subtrahend_ != subtrahendEnd)
        {
            carry -= *subtrahend_;
            ++subtrahend_;
        }

        bytes_.push_back((carry >= 0) ? carry : base_ + carry);
        carry = (carry >= 0) ? 0 : -1;
    }

    delete_null_bytes();
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& divisor)
{
    if (divisor == BigInt(0))
    {
        throw std::invalid_argument("Division by zero");
    }

    BigInt dividend(*this);
    BigInt remainder;
    remainder.bytes_.clear();
    bytes_.clear();

    for (auto dividend_ = dividend.bytes_.rbegin(); dividend_ != dividend.bytes_.rend(); ++dividend_)
    {
        remainder.bytes_.insert(remainder.bytes_.begin(), *dividend_);

        if (remainder < divisor)
        {
            bytes_.insert(bytes_.begin(), 0);
            continue;
        }

        int carry = 0;
        do
        {
            remainder -= divisor;
            ++carry;
        } while (remainder >= divisor);

        bytes_.insert(bytes_.begin(), carry);
    }

    delete_null_bytes();
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& divisor)
{
    if (divisor == BigInt(0))
    {
        throw std::invalid_argument("Division by zero");
    }

    BigInt dividend(*this);
    bytes_.clear();
    auto dividend_ = dividend.bytes_.rbegin();

    while (dividend_ != dividend.bytes_.rend())
    {
        while(dividend_ != dividend.bytes_.rend() && *this < divisor)
        {
            bytes_.insert(bytes_.begin(), *dividend_);
            ++dividend_;
        }

        while (*this >= divisor)
        {
            *this -= divisor;
        }
    }

    return *this;
}

BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt tmp(*this);
    tmp.isNegative_ = !isNegative_;
    return tmp;
}

bool BigInt::operator==(const BigInt& cmp) const
{
    if (isNegative_ ^ cmp.isNegative_)
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

bool BigInt::operator!=(const BigInt& cmp) const
{
    return !((*this) == cmp);
}

bool BigInt::operator<(const BigInt& cmp) const
{
    if (isNegative_ ^ cmp.isNegative_)
    {
        return isNegative_;
    }

    if (bytes_.size() != cmp.size())
    {
        return isNegative_ ^ (bytes_.size() < cmp.size());
    }

    for (int i = (int)bytes_.size() - 1; i >= 0 ; i--)
    {
        if (bytes_[i] != cmp.bytes_[i])
        {
            return isNegative_ ^ (bytes_[i] < cmp.bytes_[i]);
        }
    }

    return false;
}

bool BigInt::operator>(const BigInt& cmp) const
{
    return !(*this < cmp) && !(*this == cmp);
}

bool BigInt::operator<=(const BigInt& cmp) const
{
    return !((*this) > cmp);
}

bool BigInt::operator>=(const BigInt& cmp) const
{
    return !((*this) < cmp);
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
    } num{};

    std::copy(bytes_.begin(), bytes_.end(), num.bit8);

    return (isNegative_) ? -num.bit32 : num.bit32;
}

BigInt::operator std::string() const
{
    String base(std::to_string(base_));
    String number("0");

    for (auto byteIt = bytes_.rbegin(); byteIt != bytes_.rend(); ++byteIt)
    {
        String byte(std::to_string(*byteIt));
        number *= base;
        number += byte;
    }

    std::string numberStr = number.to_string();
    if (isNegative_ && numberStr != "0")
    {
        numberStr.insert(numberStr.begin(), '-');
    }

    return numberStr;
}

size_t BigInt::size() const
{
    return bytes_.size();
}

void BigInt::delete_null_bytes()
{
    while (bytes_.size() > 1 && *(bytes_.rbegin()) == 0)
    {
        bytes_.pop_back();
    }

    bytes_.shrink_to_fit();
}

bool BigInt::null_byte()
{
    return bytes_.size() == 1 && bytes_[0] == 0;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num)
{
    out << std::string(num);
    return out;
}
