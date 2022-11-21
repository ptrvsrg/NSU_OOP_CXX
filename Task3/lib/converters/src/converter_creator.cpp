#include "converter_creator.h"
#include "converter_creator_errors.h"

ConverterPtr ConverterCreator::Create(ConverterCommand converter_command)
{
    std::string converter_name = converter_command[0];
    converter_command.erase(converter_command.cbegin());

    if (converter_name == "mute")       return std::make_unique<MuteConverter>(converter_command);
    else if (converter_name == "mix")   return std::make_unique<MixConverter>(converter_command);
    else                                throw IncorrectConverterNameException(converter_name);
}
