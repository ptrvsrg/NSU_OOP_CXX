#include "config_parser.h"
#include "iostream_errors.h"
#include <sstream>

ConfigParser::ConfigParser(std::string file_path)
    : file_path_(std::move(file_path))
{
    fin_.open(file_path_,
              std::ios_base::in);
    if (!fin_.good())
        throw FileNotOpen(file_path_);
}

static bool IsComment(std::string & str)
{
    // case: "     #something"
    while (!str.empty() && str[0] == ' ')
        str.erase(0, 1);
    return str.empty() || str[0] == '#';
}

static void RemoveCommentAtEnd(std::string & str)
{
    // case: "converter_command #something"
    str = str.substr(0,
                     str.find('#'));
}

ConverterCommand ConfigParser::GetConverterCommand()
{
    ConverterCommand cvt_cmd;
    std::string buff;

    // skip comments
    do
    {
        if (fin_.eof())
            return cvt_cmd;
        getline(fin_,
                buff);
    } while (IsComment(buff));

    // skip comment at the end
    RemoveCommentAtEnd(buff);

    std::istringstream ssin(buff);

    // write converter name
    ssin >> buff;
    cvt_cmd.push_back(buff);

    // write converter params
    while (ssin >> buff)
        cvt_cmd.push_back(buff);

    return cvt_cmd;
}