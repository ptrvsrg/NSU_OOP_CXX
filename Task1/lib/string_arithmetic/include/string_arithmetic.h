#ifndef STRING_ARITHMETIC_H
#define STRING_ARITHMETIC_H

#include <iostream>
#include <string>

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
    bool operator<=(const String&) const;
    bool operator>=(const String&) const;

    void delete_begin_zero();
    explicit operator std::string() const;
private:
    std::string data_;
};

String operator+(const String&, const String&);
String operator-(const String&, const String&);
String operator*(const String&, const String&);
String operator/(const String&, const String&);
String operator%(const String&, const String&);

#endif // STRING_ARITHMETIC_H