#ifndef TASK3_MIX_CONVERTER_H
#define TASK3_MIX_CONVERTER_H

#include "converter_interface.h"

class MixConverter : public ConverterInterface
{
public:
    explicit MixConverter(ConverterParams params);
    ~MixConverter() override = default;
    void Process(SampleBuffer & working_sample,
                 const SampleVector & default_samples) override;

private:
    int start_second_=  0;
    int current_second_ = 0;
    int num_additional_file_ = 0;
};

#endif // TASK3_MIX_CONVERTER_H
