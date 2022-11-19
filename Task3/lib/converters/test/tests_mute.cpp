#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>
#include "mute.h"
#include "converter_errors.h"

struct MuteArgs
{
    std::vector<std::string> params_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        INCORRECT_PARAMS_NUM_EXCEPTION,
        INTERVAL_EXCEPTION
    } exception_type_;

    MuteArgs(std::vector<std::string> params,
             ExceptionType exception_type)
    :   params_(std::move(params)),
        exception_type_(exception_type) {}
};

class MuteTest : public ::testing::TestWithParam<MuteArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_mute,
    MuteTest,
    ::testing::Values
    (
        MuteArgs({"8", "12"},
                 MuteArgs::ExceptionType::NO_EXCEPTION),
        MuteArgs({"12", "8", "14"},
                 MuteArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION),
        MuteArgs({"8"},
                 MuteArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION),
        MuteArgs({"12", "8"},
                 MuteArgs::ExceptionType::INTERVAL_EXCEPTION)
    )
);

TEST_P(MuteTest,
       check_init)
{
    MuteArgs params = GetParam();

    switch (params.exception_type_)
    {
        case MuteArgs::ExceptionType::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                {
                    MuteConverter mute_converter(params.params_);
                }
            );
            break;
        case MuteArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MuteConverter mute_converter(params.params_);
                },
                IncorrectParamsNum
            );
            break;
        case MuteArgs::ExceptionType::INTERVAL_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MuteConverter mute_converter(params.params_);
                },
                IntervalException
            );
            break;
    }
}

static Sample GenerateSample()
{
    Sample sample = random();
    sample *= (random() % 2) ? -1 : 1;
    return sample;
}

static void FillSampleVector(std::vector<Sample> & vector)
{
    for (Sample sample : vector)
        sample = GenerateSample();
}

TEST(test_mute,
     check_process)
{
    MuteConverter mute_converter({"20", "67"});

    SampleVector input_samples(2);

    srandom(time(nullptr));
    for (int i = 0; i < 100 * SAMPLING_RATE; ++i)
    {
        FillSampleVector(input_samples);
        Sample output_sample = mute_converter.Process(input_samples);

        EXPECT_EQ(output_sample,
                  (i >= 20 * SAMPLING_RATE &&
                   i <= 67 * SAMPLING_RATE) ? 0 : input_samples[0]);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}