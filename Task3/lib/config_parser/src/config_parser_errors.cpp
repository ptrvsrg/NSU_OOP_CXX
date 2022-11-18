#include "config_parser_errors.h"

OpeningException::OpeningException(const std::string & file_path)
    : logic_error(file_path + ": File opening error") {}
