#ifndef TASK3_MUTE_CONVERTER_H
#define TASK3_MUTE_CONVERTER_H

#include <cstdint>

using Sample = int16_t;
const int32_t SAMPLING_RATE = 44100;

class MuteConverter
{
public:
    MuteConverter(int start_sec,
                  int end_sec);
    Sample Convert(Sample input_sample);
private:
    int start_samples_;
    int current_sample_;
    int end_samples_;
};

#endif //TASK3_MUTE_CONVERTER_H
