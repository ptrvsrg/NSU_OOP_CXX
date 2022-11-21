#ifndef TASK3_CONVERTER_ERRORS_H
#define TASK3_CONVERTER_ERRORS_H

#include <stdexcept>

class IncorrectParams : public std::invalid_argument
{
protected:
    IncorrectParams(const std::string & converter_name,
                    const std::string & desc);
};

class IncorrectParamsNum : public IncorrectParams
{
public:
    explicit IncorrectParamsNum(const std::string & converter_name);
};

class IncorrectFileLink : public IncorrectParams
{
public:
    explicit IncorrectFileLink(const std::string & converter_name);
};

class IncorrectNumericalParam : public IncorrectParams
{
public:
    explicit IncorrectNumericalParam(const std::string & converter_name);
};

class IncorrectInterval : public IncorrectParams
{
public:
    explicit IncorrectInterval(const std::string & converter_name);
};

bool IsNumber(const std::string & str);
bool IsLink(const std::string & str);


#endif //TASK3_CONVERTER_ERRORS_H
