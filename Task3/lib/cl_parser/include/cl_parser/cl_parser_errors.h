#ifndef TASK3_CL_PARSER_ERRORS_H
#define TASK3_CL_PARSER_ERRORS_H

#include <stdexcept>

class NoConfigFileException : public std::logic_error
{
public:
    NoConfigFileException();
};

class NoOutputFileException : public std::logic_error
{
public:
    NoOutputFileException();
};

class NoInputFilesException : public std::logic_error
{
public:
    NoInputFilesException();
};

#endif //TASK3_CL_PARSER_ERRORS_H
