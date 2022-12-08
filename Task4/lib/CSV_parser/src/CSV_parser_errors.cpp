#include "CSV_parser_errors.h"

CSVException::CSVException(size_t row, size_t column, const std::string & message)
    :         std::invalid_argument("(" + std::to_string(row) +
                                    ", " + std::to_string(column) +
                                    ") : " + message) {}
