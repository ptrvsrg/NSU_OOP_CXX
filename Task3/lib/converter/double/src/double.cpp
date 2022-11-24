#include "double.h"
#include "converter_errors.h"

DoubleConverter::DoubleConverter(ConverterParams params)
{
    if (params.size() != 2)
        throw IncorrectParamsNum("double");
    if (!IsNumber(params[0]))
        throw IncorrectNumericalParam("double");
    if (!IsNumber(params[1]))
        throw IncorrectNumericalParam("double");

    start_second_ = std::stoi(params[0]);
    end_second_ = std::stoi(params[1]);

    if (start_second_ > end_second_)
        throw IncorrectInterval("double");
}

void DoubleConverter::Process(SampleBuffer & working_sample,
                              const SampleVector & default_samples)
{
    if (current_second_ >= start_second_ &&
        current_second_ <= end_second_)
    {
        for (int i = 0; i < working_sample.size() / 2; ++i)
            working_sample[i] = working_sample[2 * i];
        for (int i = 0; i < working_sample.size() / 2; ++i)
            working_sample[i] = working_sample[working_sample.size() / 2 + i];
    }

    ++current_second_;
}

FileLinks DoubleConverter::GetFileLinks()
{
    return { 0 };
}