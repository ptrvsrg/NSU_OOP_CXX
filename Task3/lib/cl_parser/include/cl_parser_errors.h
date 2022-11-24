#ifndef TASK3_CL_PARSER_ERRORS_H
#define TASK3_CL_PARSER_ERRORS_H

#include <stdexcept>

class NoConfigFile : public std::invalid_argument
{
public:
    NoConfigFile();
};

class NoOutputFile : public std::invalid_argument
{
public:
    NoOutputFile();
};

class NoInputFiles : public std::invalid_argument
{
public:
    NoInputFiles();
};

#endif //TASK3_CL_PARSER_ERRORS_H
