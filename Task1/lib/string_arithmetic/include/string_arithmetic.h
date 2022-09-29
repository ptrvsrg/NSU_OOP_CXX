#ifndef STRING_ARITHMETIC_H
#define STRING_ARITHMETIC_H

#include <iostream>
#include <string>

class const_iterator;

class String
{
public:
    String();
    explicit String(const std::string&);
    String(const String&);

    String& operator=(const String&);

    String& operator+=(const String&);
    String& operator*=(const String&);
    String& operator-=(const String&);
    String& operator/=(const String&);
    String& operator%=(const String&);

    bool operator==(const String&) const;
    bool operator<(const String&) const;
    bool operator>=(const String&) const;

    void delete_begin_zero();
    std::string to_string();
private:
    std::string data_;
};

String operator+(const String&, const String&);
String operator-(const String&, const String&);
String operator*(const String&, const String&);
String operator/(const String&, const String&);
String operator%(const String&, const String&);

#endif // STRING_ARITHMETIC_H