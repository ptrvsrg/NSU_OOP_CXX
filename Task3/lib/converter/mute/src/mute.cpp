#include "mute.h"
#include "mute_errors.h"

MuteConverter::MuteConverter(int start_sec,
                             int end_sec)
 :  start_samples_(start_sec * SAMPLING_RATE),
    current_sample_(0),
    end_samples_(end_sec * SAMPLING_RATE)
{
    if (start_sec > end_sec) throw IntervalException();
}

Sample MuteConverter::Convert(Sample input_sample)
{
    Sample output_sample = input_sample;
    if (current_sample_ >= start_samples_ &&
        current_sample_ <= end_samples_) output_sample = 0;
    ++current_sample_;
    return output_sample;
}