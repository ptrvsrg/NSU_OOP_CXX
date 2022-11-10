#include "config_parser_errors.h"

OpeningException::OpeningException(const std::string &file_name)
    : logic_error(file_name) {}
