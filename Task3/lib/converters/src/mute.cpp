#include "mute.h"
#include "converter_errors.h"

MuteConverter::MuteConverter(std::vector<std::string> params)
{
    if (params.size() != 2) throw IncorrectParamsNum("mute");

    start_samples_ = std::stoi(params[0]) * SAMPLING_RATE;
    current_sample_ = 0;
    end_samples_ = std::stoi(params[1]) * SAMPLING_RATE;

    if (start_samples_ > end_samples_) throw IntervalException();
}

Sample MuteConverter::Process(const SampleVector & input_samples)
{
    Sample input_sample = input_samples[0];
    Sample output_sample = input_sample;

    if (current_sample_ >= start_samples_ &&
        current_sample_ <= end_samples_) output_sample = 0;

    ++current_sample_;
    return output_sample;
}
