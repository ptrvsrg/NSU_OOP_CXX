#include "mute.h"
#include "converter_errors.h"

MuteConverter::MuteConverter(std::vector<std::string> params)
{
    if (params.size() != 2) throw IncorrectParamsNum("mute");

    start_sample_num_ = std::stoi(params[0]) * 44100;
    current_sample_num_ = 0;
    end_sample_num_ = std::stoi(params[1]) * 44100;

    if (start_sample_num_ > end_sample_num_) throw IntervalException();
}

void MuteConverter::Process(Sample & working_sample,
                            const SampleVector & default_samples)
{
    if (current_sample_num_ >= start_sample_num_ &&
        current_sample_num_ <= end_sample_num_) working_sample = 0;
    ++current_sample_num_;
}
