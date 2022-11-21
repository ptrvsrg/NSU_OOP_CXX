#ifndef TASK3_CONFIG_PARSER_H
#define TASK3_CONFIG_PARSER_H

#include <fstream>
#include <string>
#include <vector>

using ConverterCommand = std::vector<std::string>;

class ConfigParser
{
public:
    explicit ConfigParser(std::string file_path);
    ConverterCommand GetConverterCommand();
    ~ConfigParser();

private:
    std::string file_path_;
    std::ifstream in_stream_;
};

#endif //TASK3_CONFIG_PARSER_H
