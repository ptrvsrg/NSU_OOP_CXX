#ifndef TASK3_CONFIG_PARSER_ERRORS_H
#define TASK3_CONFIG_PARSER_ERRORS_H

#include <stdexcept>

class IncorrectParamsException : std::invalid_argument
{
public:
    explicit IncorrectParamsException(const std::string & file_path);
};

#endif //TASK3_CONFIG_PARSER_ERRORS_H
