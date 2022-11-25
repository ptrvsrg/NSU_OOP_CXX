#include "converter_creator_errors.h"

IncorrectConverterName::IncorrectConverterName(const std::string & converter_name)
    : std::invalid_argument(converter_name + " : Converter was not found") {}
