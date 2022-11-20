#ifndef TASK3_CONVERTER_INTERFACE_H
#define TASK3_CONVERTER_INTERFACE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using Sample = int16_t;
using SampleVector = std::vector<Sample>;

class ConverterInterface
{
public:
    virtual ~ConverterInterface() = default;
    virtual void Process(Sample & working_sample,
                         const SampleVector & default_samples) = 0;
};

using ConverterPtr = std::unique_ptr<ConverterInterface>;

#endif //TASK3_CONVERTER_INTERFACE_H
