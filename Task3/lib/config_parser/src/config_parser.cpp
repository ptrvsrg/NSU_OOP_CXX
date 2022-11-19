#include "config_parser.h"
#include "config_parser_errors.h"
#include <algorithm>
#include <cctype>
#include <sstream>

ConfigParser::ConfigParser(std::string  file_path)
    : file_path_(std::move(file_path))
{
    in_stream_.open(file_path_,
                    std::ios_base::in);
    if (!in_stream_.good()) throw std::ios_base::failure(file_path_ + " ");
}

static bool IsNumber(const std::string & str)
{
    return std::all_of(str.cbegin(),
                       str.cend(),
                       [](char sym){ return std::isdigit(sym); });
}

static bool IsLink(const std::string & str)
{
    return str[0] == '$' && IsNumber(str.substr(1));
}

std::vector<std::string> ConfigParser::GetConverterCommand()
{
    std::vector<std::string> cvt_cmd;
    std::string buff;

    // skip comments
    do
    {
        if (in_stream_.eof()) return cvt_cmd;
        getline(in_stream_,
                buff);
        while (buff[0] == ' ' && !buff.empty()) buff.erase(0,
                                                           1);  // case: "     #something"
    } while (buff.empty() || buff[0] == '#');

    // skip comment at the end
    buff = buff.substr(0,
                       buff.find('#')); // case: "something #something"

    std::istringstream ssin(buff);

    // write converter name
    ssin >> buff;
    cvt_cmd.push_back(buff);

    // write converter params
    while (ssin >> buff)
    {
        if (!IsNumber(buff) && !IsLink(buff)) throw IncorrectParamsException(file_path_);
        cvt_cmd.push_back(buff);
    }

    return cvt_cmd;
}

ConfigParser::~ConfigParser()
{
    in_stream_.close();
}
