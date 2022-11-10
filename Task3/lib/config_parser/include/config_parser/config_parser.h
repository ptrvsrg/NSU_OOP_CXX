#ifndef TASK3_CONFIG_PARSER_H
#define TASK3_CONFIG_PARSER_H

#include <fstream>
#include <string>
#include <vector>

struct ConverterCommand
{
    std::string converter_;
    std::vector<std::string> params_;

    ConverterCommand() = default;
    ConverterCommand(std::string converter,
                     std::initializer_list<std::string> params);
};

class ConfigParser
{
public:
    explicit ConfigParser(const std::string & file_name);
    bool GetConverterCommand(ConverterCommand & cvt_cmd);
    ~ConfigParser();
private:
    std::ifstream in_stream_;
};

#endif //TASK3_CONFIG_PARSER_H
