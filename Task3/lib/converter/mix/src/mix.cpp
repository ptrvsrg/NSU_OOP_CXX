#include "mix.h"
#include "converter_errors.h"

MixConverter::MixConverter(ConverterParams params)
{
    if (params.size() != 2) throw IncorrectParamsNum("mix");
    if (!IsLink(params[0])) throw IncorrectFileLink("mix");
    if (!IsNumber(params[1])) throw IncorrectNumericalParam("mix");

    num_additional_file_ = std::stoi(params[0].substr(1));
    start_second_ = std::stoi(params[1]);
}

void MixConverter::Process(SampleBuffer & working_sample,
                           const SampleVector & default_samples)
{
    if (num_additional_file_ >= default_samples.size())
        throw IncorrectFileLink("mix");

    if (current_second_ >= start_second_)
        for (int i = 0; i < working_sample.size(); ++i)
            working_sample[i] = (working_sample[i] / 2) + (default_samples[num_additional_file_][i] / 2);

    ++current_second_;
}
