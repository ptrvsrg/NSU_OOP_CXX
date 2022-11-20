#include "mix.h"
#include "converter_errors.h"

MixConverter::MixConverter(std::vector<std::string> params)
{
    if (params.size() != 2) throw IncorrectParamsNum("mix");
    if (params[0][0] != '$') throw IncorrectFileLink(params[0]);

    num_additional_file_ = std::stoi(params[0].substr(1));

    if (num_additional_file_ == 0) throw IncorrectFileLink(params[0]);

    start_sample_ = std::stoi(params[1]) * 44100;
    current_sample_ = 0;
}

Sample MixConverter::Process(const SampleVector & input_samples)
{
    if (num_additional_file_ >= input_samples.size())
        throw IncorrectFileLink("$" + std::to_string(num_additional_file_));

    Sample output_sample = (current_sample_ >= start_sample_) ?
                           (input_samples[0] / 2) + (input_samples[num_additional_file_] / 2)  :
                           input_samples[0];

    ++current_sample_;
    return output_sample;
}
