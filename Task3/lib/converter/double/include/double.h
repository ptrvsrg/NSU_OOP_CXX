#ifndef TASK3_DOUBLE_CONVERTER_H
#define TASK3_DOUBLE_CONVERTER_H

#include "converter_interface.h"

class DoubleConverter : public ConverterInterface
{
public:
    explicit DoubleConverter(ConverterParams params);
    ~DoubleConverter() override = default;
    void Process(SampleBuffer & working_sample,
                 const SampleVector & default_samples) override;
    FileLinks GetFileLinks() override;

private:
    int start_second_ = 0;
    int current_second_ = 0;
    int end_second_ = 0;
};

#endif //TASK3_DOUBLE_CONVERTER_H
