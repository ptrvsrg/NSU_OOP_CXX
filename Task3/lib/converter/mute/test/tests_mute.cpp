#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>
#include "mute.h"
#include "mute_errors.h"

TEST(test_mute,
     check_constructor)
{
    EXPECT_NO_THROW
    (
        {
            MuteConverter mute_converter(8,
                                         12);
        }
    );

    EXPECT_THROW
    (
        {
            MuteConverter mute_converter(12,
                                         8);
        },
        IntervalException
    );
}

TEST(test_mute,
     check_procces)
{
    MuteConverter mute_converter(20,
                                 672);
    srandom(time(nullptr));
    for (int i = 0; i < 1000 * SAMPLING_RATE; ++i)
    {
        Sample input_sample = random();
        input_sample *= (random() % 2) ? -1 : 1;
        Sample output_sample = mute_converter.Convert(input_sample);

        EXPECT_EQ(output_sample,
                  (i >= 20 * SAMPLING_RATE &&
                   i <= 672 * SAMPLING_RATE) ? 0 : input_sample);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}