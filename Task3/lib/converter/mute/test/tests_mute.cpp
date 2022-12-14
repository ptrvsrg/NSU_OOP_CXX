#include <gtest/gtest.h>
#include <algorithm>
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
        INCORRECT_NUMERICAL_PARAM_EXCEPTION,
        INCORRECT_INTERVAL_EXCEPTION
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
        MuteArgs({"1a", "8"},
                 MuteArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION),
        MuteArgs({"8", "3i"},
                 MuteArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION),
        MuteArgs({"12", "8"},
                 MuteArgs::ExceptionType::INCORRECT_INTERVAL_EXCEPTION)
    )
);

TEST_P(MuteTest,
       check_constructor)
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
        case MuteArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MuteConverter mute_converter(params.params_);
                },
                IncorrectNumericalParam
            );
            break;
        case MuteArgs::ExceptionType::INCORRECT_INTERVAL_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MuteConverter mute_converter(params.params_);
                },
                IncorrectInterval
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

static void FillSampleVector(SampleVector & vector)
{
    for (SampleBuffer sample_buffer : vector)
        for (Sample sample : sample_buffer)
            sample = GenerateSample();
}

TEST(test_mute,
     check_process)
{
    MuteConverter mute_converter({"20", "67"});

    SampleVector default_samples(2);
    SampleBuffer null;
    null.fill(0);

    srandom(time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        FillSampleVector(default_samples);
        SampleBuffer work_sample = default_samples[0];
        mute_converter.Process(work_sample,
                               default_samples);

        EXPECT_EQ(work_sample,
                  (i >= 20 &&
                   i <= 67) ? null : default_samples[0]);
    }
}

TEST(test_mute,
     check_get_file_links)
{
    MuteConverter mute_converter({"20", "67"});
    FileLinks file_links = mute_converter.GetFileLinks();
    EXPECT_EQ(file_links.size(),
              1);
    EXPECT_EQ(*file_links.cbegin(),
              0);
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}