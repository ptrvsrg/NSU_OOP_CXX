#ifndef TASK3_CONVERTER_CREATOR_H
#define TASK3_CONVERTER_CREATOR_H

#include <string>
#include <vector>

#include "converter_interface.h"
#include "mute.h"
#include "mix.h"

using ConverterCommand = std::vector<std::string>;

class ConverterCreator
{
public:
    ConverterPtr Create(ConverterCommand converter_command);
};

#endif //TASK3_CONVERTER_CREATOR_H
