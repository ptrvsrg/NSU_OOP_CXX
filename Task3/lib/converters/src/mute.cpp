#include "mute.h"
#include "converter_errors.h"

MuteConverter::MuteConverter(std::vector<std::string> params)
{
    if (params.size() != 2) throw IncorrectParamsNum("mute");

    start_second_ = std::stoi(params[0]);
    current_second_ = 0;
    end_second_ = std::stoi(params[1]);

    if (start_second_ > end_second_) throw IntervalException();
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
