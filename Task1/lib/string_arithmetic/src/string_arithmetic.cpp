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

static bool IsDigit(const std::string & num);

bool IsDigit(const std::string &num)
{
    if (num.size() == 1 && IsNegative(num))
    {
        return false;
    }

    for (int i = IsNegative(num) ? 1 : 0; i < num.size(); ++i)
    {
        if (num[i] < '0' || num[i] > '9')
        {
            return false;
        }
    }

    return true;
}

String::String() = default;

String::String(const std::string& src)
{
    if (!IsDigit(src) || IsNegative(src))
    {
        throw std::invalid_argument("Wrong string number");
    }

    data_.assign(src);
    delete_begin_zero();
}

String::String(const String& src)
{
    data_.assign(src.data_);
}

String::String(String&& tmp) noexcept
{
    data_.clear();
    data_ = std::move(tmp.data_);
}

String &String::operator=(const String & src)
{
    if (&src != this)
    {
        data_.assign(src.data_);
    }

    return *this;
}

String &String::operator=(String && tmp) noexcept
{
    data_.clear();
    data_ = std::move(tmp.data_);
    return *this;
}

String &String::operator+=(const String & addend2)
{
    String addend1(*this);
    data_.clear();

    int carry = 0;
    auto addendIt1 = addend1.data_.crbegin();
    auto addendIt2 = addend2.data_.crbegin();

    while (addendIt1 != addend1.data_.crend() || addendIt2 != addend2.data_.crend())
    {
        if(addendIt1 != addend1.data_.crend())
        {
            carry += CharToInt(*addendIt1);
            ++addendIt1;
        }

        if(addendIt2 != addend2.data_.crend())
        {
            carry += CharToInt(*addendIt2);
            ++addendIt2;
        }

        data_.insert(data_.cbegin(), IntToChar(carry % 10));
        carry /= 10;
    }

    if (carry != 0)
    {
        data_.insert(data_.cbegin(), IntToChar(carry));
    }

    return *this;
}

String operator+(const String & addend1, const String & addend2)
{
    String sum(addend1);
    sum += addend2;
    return sum;
}

String &String::operator*=(const String & multiplier2)
{
    String multiplier1(*this);
    data_.clear();

    for (auto multiplierIt1 = multiplier1.data_.crbegin(); multiplierIt1 != multiplier1.data_.crend(); ++multiplierIt1)
    {
        String buffer;
        buffer.data_.insert(buffer.data_.cbegin(), multiplierIt1 - multiplier1.data_.crbegin(), '0');

        int carry = 0;

        for (auto multiplierIt2 = multiplier2.data_.crbegin(); multiplierIt2 != multiplier2.data_.crend(); ++multiplierIt2)
        {
            carry += CharToInt(*multiplierIt1) * CharToInt(*multiplierIt2);
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

String operator*(const String & multiplier1, const String & multiplier2)
{
    String product(multiplier1);
    product *= multiplier2;
    return product;
}

String &String::operator-=(const String & subtrahend)
{
    if (*this < subtrahend)
    {
        throw std::invalid_argument("String minuend must be greater than string subtrahend");
    }

    String minuend(*this);
    data_.clear();

    int carry = 0;
    auto minuendIt = minuend.data_.crbegin();
    auto subtrahendIt = subtrahend.data_.crbegin();

    while (minuendIt != minuend.data_.crend() || subtrahendIt != subtrahend.data_.crend())
    {
        if(subtrahendIt != subtrahend.data_.crend())
        {
            carry -= CharToInt(*subtrahendIt);
            ++subtrahendIt;
        }

        if(minuendIt != minuend.data_.crend())
        {
            carry += CharToInt(*minuendIt);
            ++minuendIt;
        }

        data_.insert(data_.cbegin(), IntToChar((carry >= 0) ? carry : 10 + carry));
        carry = (carry >= 0) ? 0 : -1;
    }

    delete_begin_zero();
    return *this;
}

String operator-(const String & minuend, const String & subtrahend)
{
    String difference(minuend);
    difference -= subtrahend;
    return difference;
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

    auto dividendIt = dividend.data_.cbegin();

    while (dividendIt != dividend.data_.cend())
    {
        while (remainder < divisor && dividendIt != dividend.data_.cend())
        {
            remainder.data_.push_back(*dividendIt);
            data_.push_back('0');
        }

        int carry = 0;
        do
        {
            remainder -= divisor;
            ++carry;
        } while (remainder >= divisor);

        data_.push_back(IntToChar(carry));
    }

    delete_begin_zero();
    return *this;
}

String operator/(const String & dividend, const String & divisor)
{
    String quotient(dividend);
    quotient /= divisor;
    return quotient;
}

String &String::operator%=(const String & divisor)
{
    if (divisor == String("0"))
    {
        throw std::invalid_argument("Division by zero");
    }

    String dividend(*this);
    data_.clear();

    for (char dividendNum : dividend.data_)
    {
        data_.push_back(dividendNum);

        if (*this < divisor)
        {
            continue;
        }

        do
        {
            *this -= divisor;
        } while (*this >= divisor);
    }

    return *this;
}

String operator%(const String & dividend, const String & divisor)
{
    String remainder(dividend);
    remainder %= divisor;
    return remainder;
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
    while (!data_.empty() && data_[0] == '0' && data_.size() > 1)
    {
        data_.erase(data_.begin(), data_.begin() + 1);
    }
}

std::string String::to_string()
{
    return data_;
}