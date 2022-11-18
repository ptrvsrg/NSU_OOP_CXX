#ifndef TASK3_CONFIG_PARSER_ERRORS_H
#define TASK3_CONFIG_PARSER_ERRORS_H

#include <stdexcept>

class OpeningException : std::logic_error
{
public:
    explicit OpeningException(const std::string & file_path);
};

#endif //TASK3_CONFIG_PARSER_ERRORS_H
