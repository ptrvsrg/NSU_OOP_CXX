#include "mix.h"
#include "converter_errors.h"

MixConverter::MixConverter(ConverterParams params)
{
    if (params.size() != 2)
        throw IncorrectParamsNum("mix");
    if (!IsLink(params[0]))
        throw IncorrectFileLink("mix");
    if (!IsNumber(params[1]))
        throw IncorrectNumericalParam("mix");

    additional_file_link_ = std::stoi(params[0].substr(1));
    start_second_ = std::stoi(params[1]);
}

void MixConverter::Process(SampleBuffer & working_sample,
                           const SampleVector & default_samples)
{
    if (current_second_ >= start_second_)
        for (int i = 0; i < working_sample.size(); ++i)
            working_sample[i] = (working_sample[i] / 2) + (default_samples[additional_file_link_][i] / 2);

    ++current_second_;
}
