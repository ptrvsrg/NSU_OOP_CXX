#ifndef TASK4_CSV_PARSER_ERRORS_H
#define TASK4_CSV_PARSER_ERRORS_H

#include <stdexcept>

class CSVException : public std::invalid_argument
{
public:
    CSVException(size_t row, size_t column, const std::string & message);
};

#endif //TASK4_CSV_PARSER_ERRORS_H
