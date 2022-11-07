#ifndef TASK2_CL_PARSER_H
#define TASK2_CL_PARSER_H

#include <string>
#include <vector>

class NoConfigFileError : public std::exception
{
public:
    NoConfigFileError() = default;
    const char * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class NoOutputFileError : public std::exception
{
public:
    NoOutputFileError() = default;
    const char * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class NoInputFilesError : public std::exception
{
public:
    NoInputFilesError() = default;
    const char * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

struct Options
{
    std::vector<std::string> input_files_;
    std::string output_file_;
    std::string config_file_;

    Options() = default;
};

bool GetOptions(int argc,
                char ** argv,
                Options & opts);

#endif // TASK2_CL_PARSER_H
