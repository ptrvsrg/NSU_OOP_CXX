#include "mute.h"
#include "converter_errors.h"

MuteConverter::MuteConverter(ConverterParams params)
{
    if (params.size() != 2)
        throw IncorrectParamsNum("mute");
    if (!IsNumber(params[0]))
        throw IncorrectNumericalParam("mute");
    if (!IsNumber(params[1]))
        throw IncorrectNumericalParam("mute");

    start_second_ = std::stoi(params[0]);
    end_second_ = std::stoi(params[1]);

    if (start_second_ > end_second_)
        throw IncorrectInterval("mute");
}

void MuteConverter::Process(SampleBuffer & working_sample,
                            const SampleVector & default_samples)
{
    if (current_second_ >= start_second_ &&
        current_second_ <= end_second_)
        for (int16_t & sample : working_sample)
            sample = 0;
    ++current_second_;
}
