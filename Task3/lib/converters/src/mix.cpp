#include "mix.h"
#include "converter_errors.h"

MixConverter::MixConverter(std::vector<std::string> params)
{
    if (params.size() != 2) throw IncorrectParamsNum("mix");
    if (params[0][0] != '$') throw IncorrectFileLink(params[0]);

    num_additional_file_ = std::stoi(params[0].substr(1));

    start_sample_ = std::stoi(params[1]) * 44100;
    current_sample_ = 0;
}

void MixConverter::Process(Sample & working_sample,
                           const SampleVector & default_samples)
{
    if (num_additional_file_ >= default_samples.size())
        throw IncorrectFileLink("$" + std::to_string(num_additional_file_));

    if (current_sample_ >= start_sample_)
        working_sample = (working_sample / 2) + (default_samples[num_additional_file_] / 2);

    ++current_sample_;
}
