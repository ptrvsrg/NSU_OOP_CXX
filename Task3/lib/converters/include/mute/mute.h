#ifndef TASK3_MUTE_CONVERTER_H
#define TASK3_MUTE_CONVERTER_H

#include "converter_interface.h"

class MuteConverter : public ConverterInterface
{
public:
    explicit MuteConverter(std::vector<std::string> params);
    ~MuteConverter() override = default;
    void Process(Sample & working_sample,
                 const SampleVector & default_samples) override;

private:
    int start_sample_num_ = 0;
    int current_sample_num_ = 0;
    int end_sample_num_ = 0;
};

#endif //TASK3_MUTE_CONVERTER_H
