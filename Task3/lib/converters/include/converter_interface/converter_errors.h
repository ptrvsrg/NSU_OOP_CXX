#ifndef TASK3_CONVERTER_ERRORS_H
#define TASK3_CONVERTER_ERRORS_H

#include <stdexcept>

class IntervalException : std::invalid_argument
{
public:
    IntervalException();
};

class IncorrectParamsNum : std::invalid_argument
{
public:
    explicit IncorrectParamsNum(const std::string & converter_name);
};

class IncorrectFileLink : std::invalid_argument
{
public:
    explicit IncorrectFileLink(const std::string & file_link);
};


#endif //TASK3_CONVERTER_ERRORS_H
