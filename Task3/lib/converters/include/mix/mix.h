#ifndef TASK3_MIX_CONVERTER_H
#define TASK3_MIX_CONVERTER_H

#include "converter_interface.h"

class MixConverter : public ConverterInterface
{
public:
    explicit MixConverter(std::vector<std::string> params);
    ~MixConverter() override = default;
    void Process(Sample & working_sample,
                 const SampleVector & default_samples) override;

private:
    int start_sample_=  0;
    int current_sample_ = 0;
    int num_additional_file_ = 0;
};

#endif // TASK3_MIX_CONVERTER_H
