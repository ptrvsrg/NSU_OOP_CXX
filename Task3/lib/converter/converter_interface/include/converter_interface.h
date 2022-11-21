#ifndef TASK3_CONVERTER_INTERFACE_H
#define TASK3_CONVERTER_INTERFACE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "WAV_types.h"

using SampleVector = std::vector<SampleBuffer>;
using ConverterParams = std::vector<std::string>;

class ConverterInterface
{
public:
    virtual ~ConverterInterface() = default;
    virtual void Process(SampleBuffer & working_sample,
                         const SampleVector & default_samples) = 0;
};

using ConverterPtr = std::unique_ptr<ConverterInterface>;

#endif //TASK3_CONVERTER_INTERFACE_H
