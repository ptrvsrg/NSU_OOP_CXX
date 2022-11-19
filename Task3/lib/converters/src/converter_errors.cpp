#include "converter_errors.h"

IntervalException::IntervalException()
    : std::invalid_argument("mute converter : Incorrect interval time") {}

IncorrectParamsNum::IncorrectParamsNum(const std::string & converter_name)
    : std::invalid_argument(converter_name + " converter : Incorrect number of parameters") {}

IncorrectFileLink::IncorrectFileLink(const std::string & file_link)
    : std::invalid_argument("mix converter : File at link " + file_link + " was not found") {}
