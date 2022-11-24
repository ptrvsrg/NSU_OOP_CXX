#include <gtest/gtest.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "double.h"
#include "converter_errors.h"

struct DoubleArgs
{
    std::vector<std::string> params_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        INCORRECT_PARAMS_NUM_EXCEPTION,
        INCORRECT_NUMERICAL_PARAM_EXCEPTION,
        INCORRECT_INTERVAL_EXCEPTION
    } exception_type_;

    DoubleArgs(std::vector<std::string> params,
               ExceptionType exception_type)
    :   params_(std::move(params)),
        exception_type_(exception_type) {}
};

class DoubleTest : public ::testing::TestWithParam<DoubleArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_double,
    DoubleTest,
    ::testing::Values
    (
        DoubleArgs({"8", "12"},
                   DoubleArgs::ExceptionType::NO_EXCEPTION),
        DoubleArgs({"12", "8", "14"},
                   DoubleArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION),
        DoubleArgs({"8"},
                   DoubleArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION),
        DoubleArgs({"1a", "8"},
                   DoubleArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION),
        DoubleArgs({"8", "3i"},
                   DoubleArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION),
        DoubleArgs({"12", "8"},
                   DoubleArgs::ExceptionType::INCORRECT_INTERVAL_EXCEPTION)
    )
);

TEST_P(DoubleTest,
       check_constructor)
{
    DoubleArgs params = GetParam();

    switch (params.exception_type_)
    {
        case DoubleArgs::ExceptionType::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                {
                    DoubleConverter double_converter(params.params_);
                }
            );
            break;
        case DoubleArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION:
            EXPECT_THROW
            (
                {
                    DoubleConverter double_converter(params.params_);
                },
                IncorrectParamsNum
            );
            break;
        case DoubleArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION:
            EXPECT_THROW
            (
                {
                    DoubleConverter double_converter(params.params_);
                },
                IncorrectNumericalParam
            );
            break;
        case DoubleArgs::ExceptionType::INCORRECT_INTERVAL_EXCEPTION:
            EXPECT_THROW
            (
                {
                    DoubleConverter double_converter(params.params_);
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

static void FillSqueak(SampleBuffer & squeak)
{
    const double PI = acos(-1.0);
    for (int i = 0; i < squeak.size(); ++i)
        squeak[i] = (Sample)sin(2 * PI * (1 / 5) * i);
}

TEST(test_double,
     check_process)
{
    DoubleConverter double_converter({"20", "67"});

    SampleVector default_samples(2);
    SampleBuffer squeak;
    FillSqueak(squeak);

    srandom(time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        FillSampleVector(default_samples);
        SampleBuffer work_sample = default_samples[0];
        double_converter.Process(work_sample,
                                 default_samples);

        for (int j = 0; j < work_sample.size() / 2; ++j)
        {
            EXPECT_EQ(work_sample[i],
                      (i >= 20 && i <= 67) ?
                      default_samples[0][2 * i] :
                      default_samples[0][i]);
            EXPECT_EQ(work_sample[work_sample.size() / 2 + i],
                      (i >= 20 && i <= 67) ?
                      default_samples[0][2 * i] :
                      default_samples[0][i]);
        }
    }
}

TEST(test_double,
     check_get_file_links)
{
    DoubleConverter double_converter({"20", "67"});
    FileLinks file_links = double_converter.GetFileLinks();
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