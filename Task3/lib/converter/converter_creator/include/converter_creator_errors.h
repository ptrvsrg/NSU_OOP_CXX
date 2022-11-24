#ifndef TASK3_CONVERTER_CREATOR_ERRORS_H
#define TASK3_CONVERTER_CREATOR_ERRORS_H

#include <stdexcept>

class IncorrectConverterName : std::invalid_argument
{
public:
    explicit IncorrectConverterName(const std::string & converter_name);
};

#endif //TASK3_CONVERTER_CREATOR_ERRORS_H
