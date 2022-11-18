#include "config_parser.h"
#include "config_parser_errors.h"
#include <sstream>

ConverterCommand::ConverterCommand(std::string converter, std::initializer_list<std::string> params)
:   converter_(std::move(converter)),
    params_(params) {}

ConfigParser::ConfigParser(const std::string & file_path)
{
    in_stream_.open(file_path,
                    std::ios_base::in);
    if (!in_stream_.good()) throw OpeningException(file_path);
}

bool ConfigParser::GetConverterCommand(ConverterCommand & cvt_cmd)
{
    std::string buff;
    do
    {
        if (in_stream_.eof()) return false;
        getline(in_stream_,
                buff);
        while (buff[0] == ' ' && !buff.empty()) buff.erase(0,
                                                           1);  // case: "     #something"
    } while (buff.empty() || buff[0] == '#');

    buff = buff.substr(0,
                       buff.find('#')); // case: "something #something"

    std::istringstream ssin(buff);
    ssin >> cvt_cmd.converter_;
    while (ssin >> buff) cvt_cmd.params_.push_back(buff);

    return true;
}

ConfigParser::~ConfigParser()
{
    in_stream_.close();
}
