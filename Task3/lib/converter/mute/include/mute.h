#ifndef TASK3_MUTE_CONVERTER_H
#define TASK3_MUTE_CONVERTER_H

#include "converter_interface.h"

class MuteConverter : public ConverterInterface
{
public:
    explicit MuteConverter(ConverterParams params);
    ~MuteConverter() override = default;
    void Process(SampleBuffer & working_sample,
                 const SampleVector & default_samples) override;

private:
    int start_second_ = 0;
    int current_second_ = 0;
    int end_second_ = 0;
};

#endif //TASK3_MUTE_CONVERTER_H
