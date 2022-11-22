#include "converter_errors.h"
#include <algorithm>
#include <cctype>

IncorrectParams::IncorrectParams(const std::string & converter_name,
                                 const std::string & desc)
    : std::invalid_argument(converter_name + " converter : " + desc) {}

IncorrectParamsNum::IncorrectParamsNum(const std::string & converter_name)
    : IncorrectParams(converter_name,
                      "Incorrect number of parameters") {}

IncorrectNumericalParam::IncorrectNumericalParam(const std::string & converter_name)
    : IncorrectParams(converter_name,
                      "Incorrect numerical parameter") {}

IncorrectFileLink::IncorrectFileLink(const std::string & converter_name)
    : IncorrectParams(converter_name,
                      "Incorrect file link") {}

IncorrectInterval::IncorrectInterval(const std::string & converter_name)
    : IncorrectParams(converter_name,
                      "Incorrect interval time") {}

bool IsNumber(const std::string & str)
{
    return std::all_of(str.cbegin(),
                       str.cend(),
                       [](char sym){ return std::isdigit(sym); });
}

bool IsLink(const std::string & str)
{
    return str.size() > 1 && str[0] == '$' && IsNumber(str.substr(1));
}