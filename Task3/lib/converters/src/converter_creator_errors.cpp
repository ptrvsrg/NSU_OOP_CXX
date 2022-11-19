#include "converter_creator_errors.h"

IncorrectConverterNameException::IncorrectConverterNameException(const std::string & converter_name)
    : std::invalid_argument(converter_name + " : Converter was not found"){}
