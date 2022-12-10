#include "CSV_parser_errors.h"

CSVException::CSVException(size_t row, size_t column, const std::string & message)
    :   std::runtime_error("(" + std::to_string(row) +
                           ", " + std::to_string(column) +
                           ") : " + message) {}

FewColumnsException::FewColumnsException(size_t row, size_t column)
    : CSVException(row, column, "Few columns") {}

ManyColumnsException::ManyColumnsException(size_t row, size_t column)
    : CSVException(row, column, "Many columns") {}

TypeMismatchException::TypeMismatchException(size_t row, size_t column)
    : CSVException(row, column, "Data type mismatch") {}

EscapeSymbolsCountException::EscapeSymbolsCountException(size_t row, size_t column)
    : CSVException(row, column, "Escape symbols is incorrectly placed") {}