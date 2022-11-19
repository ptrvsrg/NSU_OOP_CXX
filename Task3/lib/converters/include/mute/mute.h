#ifndef TASK3_MUTE_CONVERTER_H
#define TASK3_MUTE_CONVERTER_H

#include "converter_interface.h"

class MuteConverter : public ConverterInterface
{
public:
    explicit MuteConverter(std::vector<std::string> params);
    ~MuteConverter() override = default;
    Sample Process(const SampleVector & input_samples) override;

private:
    int start_samples_ = 0;
    int current_sample_ = 0;
    int end_samples_ = 0;
};

#endif //TASK3_MUTE_CONVERTER_H
