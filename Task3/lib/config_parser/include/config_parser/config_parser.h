#ifndef TASK3_CONFIG_PARSER_H
#define TASK3_CONFIG_PARSER_H

#include <fstream>
#include <string>
#include <vector>

class ConfigParser
{
public:
    explicit ConfigParser(std::string file_path);
    std::vector<std::string> GetConverterCommand();
    ~ConfigParser();

private:
    std::string file_path_;
    std::ifstream in_stream_;
};

#endif //TASK3_CONFIG_PARSER_H
