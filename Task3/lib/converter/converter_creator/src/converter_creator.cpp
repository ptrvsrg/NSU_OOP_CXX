#include "converter_interface.h"
#include "converter_creator_errors.h"
#include "double.h"
#include "mix.h"
#include "mute.h"

ConverterPtr ConverterInterface::Create(ConverterCommand converter_command)
{
    std::string converter_name = converter_command[0];
    converter_command.erase(converter_command.cbegin());

    if (converter_name == "double")
        return std::make_unique<DoubleConverter>(converter_command);
    else if (converter_name == "mute")
        return std::make_unique<MuteConverter>(converter_command);
    else if (converter_name == "mix")
        return std::make_unique<MixConverter>(converter_command);
    else
        throw IncorrectConverterNameException(converter_name);
}
