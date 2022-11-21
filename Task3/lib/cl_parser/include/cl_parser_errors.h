#ifndef TASK3_CL_PARSER_ERRORS_H
#define TASK3_CL_PARSER_ERRORS_H

#include <stdexcept>

class NoConfigFileException : public std::invalid_argument
{
public:
    NoConfigFileException();
};

class NoOutputFileException : public std::invalid_argument
{
public:
    NoOutputFileException();
};

class NoInputFilesException : public std::invalid_argument
{
public:
    NoInputFilesException();
};

#endif //TASK3_CL_PARSER_ERRORS_H
