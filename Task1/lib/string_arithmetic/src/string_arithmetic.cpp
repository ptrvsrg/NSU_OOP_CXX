#include "string_arithmetic.h"

static int CharToInt(char sym)
{
    return sym - '0';
}

static char IntToChar(int digit)
{
    return digit + '0';
}

static bool IsNegative(const std::string & num)
{
    return (num[0] == '-');
}

static bool IsDigit(char sym)
{
    return sym >= '0' && sym <= '9';
}

static bool IsNumber(const std::string &num)
{
    if (num.size() == 1 && IsNegative(num))
    {
        return false;
    }

    for (int i = IsNegative(num) ? 1 : 0; i < num.size(); ++i)
    {
        if (!IsDigit(num[i]))
        {
            return false;
        }
    }

    return true;
}



String::String()
{
    data_ = "0";
}

String::String(const std::string& src)
{
    if (!IsNumber(src))
    {
        throw std::invalid_argument("Wrong string number");
    }
    if (IsNegative(src))
    {
        throw std::invalid_argument("Number must be positive");
    }

    data_.assign(src);
    delete_begin_zero();
}

String::String(const String& src)
{
    data_.assign(src.data_);
}



String &String::operator=(const String & src)
{
    if (&src != this)
    {
        data_.assign(src.data_);
    }

    return *this;
}

String &String::operator+=(const String & addend)
{
    auto sumIter = data_.rbegin();
    auto sumEnd = data_.rend();

    auto addendIter = addend.data_.crbegin();

    int carry = 0;
    while (sumIter < sumEnd || addendIter < addend.data_.crend())
    {
        if(addendIter < addend.data_.crend())
        {
            carry += CharToInt(*addendIter);
            ++addendIter;
        }

        if(sumIter < sumEnd)
        {
            carry += CharToInt(*sumIter);
            *sumIter = IntToChar(carry % 10);
            ++sumIter;
        }
        else
        {
            data_.insert(data_.cbegin(), IntToChar(carry % 10));
        }

        carry /= 10;
    }

    if (carry != 0)
    {
        data_.insert(data_.cbegin(), IntToChar(carry));
    }

    return *this;
}

String &String::operator-=(const String & subtrahend)
{
    if (*this < subtrahend)
    {
        throw std::invalid_argument("String minuend must be greater than string subtrahend");
    }

    auto subtrahendIter = subtrahend.data_.crbegin();
    auto differenceIter = data_.rbegin();

    int carry = 0;
    while (subtrahendIter < subtrahend.data_.crend())
    {
        if(subtrahendIter < subtrahend.data_.crend())
        {
            carry -= CharToInt(*subtrahendIter);
            ++subtrahendIter;
        }

        carry += CharToInt(*differenceIter);
        *differenceIter = IntToChar((carry >= 0) ? carry : 10 + carry);
        ++differenceIter;
        carry = (carry >= 0) ? 0 : -1;
    }

    if (carry != 0)
    {
        carry += CharToInt(*differenceIter);
        *differenceIter = IntToChar((carry >= 0) ? carry : 10 + carry);
    }

    delete_begin_zero();
    return *this;
}

String &String::operator*=(const String & multiplier2)
{
    String multiplier1(*this);
    data_.clear();
    *this = String();

    for (auto multiplierIter1 = multiplier1.data_.crbegin(); multiplierIter1 != multiplier1.data_.crend(); ++multiplierIter1)
    {
        String buffer;
        buffer.data_.clear();
        buffer.data_.insert(buffer.data_.cbegin(), multiplierIter1 - multiplier1.data_.crbegin(), '0');

        int carry = 0;
        for (auto multiplierIter2 = multiplier2.data_.crbegin(); multiplierIter2 != multiplier2.data_.crend(); ++multiplierIter2)
        {
            carry += CharToInt(*multiplierIter1) * CharToInt(*multiplierIter2);
            buffer.data_.insert(buffer.data_.cbegin(), IntToChar(carry % 10));
            carry /= 10;
        }

        if (carry != 0)
        {
            buffer.data_.insert(buffer.data_.cbegin(), IntToChar(carry));
        }

        *this += buffer;
    }

    delete_begin_zero();
    return *this;
}

String &String::operator/=(const String & divisor)
{
    if (divisor == String("0"))
    {
        throw std::invalid_argument("Division by zero");
    }

    String dividend(*this);
    data_.clear();
    String remainder;
    remainder.data_.clear();

    auto dividendIter = dividend.data_.cbegin();

    while (dividendIter < dividend.data_.cend())
    {
        remainder.data_.push_back(*dividendIter);
        ++dividendIter;
        remainder.delete_begin_zero();

        int carry = 0;
        while (remainder >= divisor)
        {
            remainder -= divisor;
            ++carry;
        }

        data_.push_back(IntToChar(carry));
    }

    delete_begin_zero();
    return *this;
}

String &String::operator%=(const String & divisor)
{
    if (divisor == String("0"))
    {
        throw std::invalid_argument("Division by zero");
    }

    String dividend(*this);
    data_.clear();

    auto dividendIter = dividend.data_.cbegin();

    while (dividendIter < dividend.data_.cend())
    {
        data_.push_back(*dividendIter);
        ++dividendIter;
        delete_begin_zero();

        while (*this >= divisor)
        {
            *this -= divisor;
        }
    }
    return *this;
}



bool String::operator==(const String & cmp) const
{
    if (data_.size() != cmp.data_.size())
    {
        return false;
    }

    for (int i = 0; i < data_.size(); ++i)
    {
        if (data_[i] != cmp.data_[i])
        {
            return false;
        }
    }

    return true;
}

bool String::operator<(const String & cmp) const
{
    if (data_.size() != cmp.data_.size())
    {
        return data_.size() < cmp.data_.size();
    }

    for (int i = 0; i < data_.size(); ++i)
    {
        if (data_[i] != cmp.data_[i])
        {
            return data_[i] < cmp.data_[i];
        }
    }

    return false;
}

bool String::operator>=(const String & cmp) const
{
    return !(*this < cmp);
}



void String::delete_begin_zero()
{
    while (data_[0] == '0' && data_.size() > 1)
    {
        data_.erase(data_.begin(), data_.begin() + 1);
    }
}

std::string String::to_string()
{
    return data_;
}



String operator+(const String & addend1, const String & addend2)
{
    String sum(addend1);
    sum += addend2;
    return sum;
}

String operator-(const String & minuend, const String & subtrahend)
{
    String difference(minuend);
    difference -= subtrahend;
    return difference;
}

String operator*(const String & multiplier1, const String & multiplier2)
{
    String product(multiplier1);
    product *= multiplier2;
    return product;
}

String operator/(const String & dividend, const String & divisor)
{
    String quotient(dividend);
    quotient /= divisor;
    return quotient;
}

String operator%(const String & dividend, const String & divisor)
{
    String remainder(dividend);
    remainder %= divisor;
    return remainder;
}