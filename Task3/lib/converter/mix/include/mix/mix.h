#ifndef TASK3_MIX_CONVERTER_H
#define TASK3_MIX_CONVERTER_H

#include <cstdint>

using Sample = int16_t;
const int32_t SAMPLING_RATE = 44100;

class MixConverter
{
public:
    explicit MixConverter(int start_sec = 0);
    Sample Convert(Sample input_sample,
                   Sample additional_sample);
private:
    int start_sample_;
    int current_sample_;
};

#endif // TASK3_MIX_CONVERTER_H
