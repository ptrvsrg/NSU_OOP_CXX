#include <gtest/gtest.h>
#include "mix.h"

static Sample GenerateSample()
{
    Sample sample = random();
    sample *= (random() % 2) ? -1 : 1;
    return sample;
}

TEST(test_mix,
     check_procces)
{
    MixConverter mix_converter(20);
    srandom(time(nullptr));
    for (int i = 0; i < 100 * SAMPLING_RATE; ++i)
    {
        Sample input_sample = GenerateSample();
        Sample additional_sample = GenerateSample();
        Sample output_sample = mix_converter.Convert(input_sample,
                                                     additional_sample);

        EXPECT_EQ(output_sample,
                  (i >= 20 * SAMPLING_RATE) ?
                  (input_sample + additional_sample) / 2 :
                  input_sample);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}