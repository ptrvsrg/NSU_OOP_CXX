#include "mix.h"

MixConverter::MixConverter(int start_sec)
: start_sample_(start_sec * SAMPLING_RATE),
  current_sample_(0) {}

Sample MixConverter::Convert(Sample input_sample,
                             Sample additional_sample)
{
    Sample output_sample = input_sample;
    if (current_sample_ >= start_sample_)
    {
        output_sample = (input_sample + additional_sample) / 2;
    }

    ++current_sample_;
    return output_sample;
}
