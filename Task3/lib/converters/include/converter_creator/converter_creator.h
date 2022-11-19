#ifndef TASK3_CONVERTER_CREATOR_H
#define TASK3_CONVERTER_CREATOR_H

#include <string>
#include <vector>

#include "converter_interface.h"
#include "mute.h"
#include "mix.h"

class ConverterCreator
{
public:
    ConverterPtr Create(std::vector<std::string> converter_command);
};

#endif //TASK3_CONVERTER_CREATOR_H
