#ifndef TASK4_CSV_PARSER_ERRORS_H
#define TASK4_CSV_PARSER_ERRORS_H

#include <stdexcept>

class CSVException : public std::runtime_error
{
public:
    CSVException(size_t row, size_t column, const std::string & message);
};

class FewColumnsException : public CSVException
{
public:
    FewColumnsException(size_t row, size_t column);
};

class ManyColumnsException : public CSVException
{
public:
    ManyColumnsException(size_t row, size_t column);
};

class TypeMismatchException : public CSVException
{
public:
    TypeMismatchException(size_t row, size_t column);
};

class EscapeSymbolsCountException : public CSVException
{
public:
    EscapeSymbolsCountException(size_t row, size_t column);
};

#endif //TASK4_CSV_PARSER_ERRORS_H
