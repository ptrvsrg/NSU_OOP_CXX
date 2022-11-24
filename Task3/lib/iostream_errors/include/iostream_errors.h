#ifndef TASK3_IOSTREAM_ERRORS_H
#define TASK3_IOSTREAM_ERRORS_H

#include <ios>

class FileNotOpen : public std::ios_base::failure
{
public:
    explicit FileNotOpen(std::string file_path);
};

class FileNotWrite : public std::ios_base::failure
{
public:
    explicit FileNotWrite(std::string file_path);
};

#endif //TASK3_IOSTREAM_ERRORS_H
