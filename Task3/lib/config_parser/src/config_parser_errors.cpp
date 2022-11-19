#include "config_parser_errors.h"

IncorrectParamsException::IncorrectParamsException(const std::string & file_path)
    : std::invalid_argument(file_path + " : Incorrect parameters") {}