#include <gtest/gtest.h>
#include "mix.h"
#include "converter_errors.h"

struct MixArgs
{
    std::vector<std::string> params_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        INCORRECT_PARAMS_NUM_EXCEPTION,
        INCORRECT_FILE_LINK_EXCEPTION,
        INCORRECT_NUMERICAL_PARAM_EXCEPTION
    } exception_type_;

    MixArgs(std::vector<std::string> params,
             ExceptionType exception_type)
        :   params_(std::move(params)),
            exception_type_(exception_type) {}
};

class MixTest : public ::testing::TestWithParam<MixArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_mix,
    MixTest,
    ::testing::Values
        (
            MixArgs({"$1", "12"},
                    MixArgs::ExceptionType::NO_EXCEPTION),
            MixArgs({"12", "8", "14"},
                    MixArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION),
            MixArgs({"8"},
                    MixArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION),
            MixArgs({"8", "12"},
                    MixArgs::ExceptionType::INCORRECT_FILE_LINK_EXCEPTION),
            MixArgs({"$1", "8g"},
                    MixArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION)
        )
);

TEST_P(MixTest,
       check_constructor)
{
    MixArgs params = GetParam();

    switch (params.exception_type_)
    {
        case MixArgs::ExceptionType::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                {
                    MixConverter mix_converter(params.params_);
                }
            );
            break;
        case MixArgs::ExceptionType::INCORRECT_PARAMS_NUM_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MixConverter mix_converter(params.params_);
                },
                IncorrectParamsNum
            );
            break;
        case MixArgs::ExceptionType::INCORRECT_FILE_LINK_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MixConverter mix_converter(params.params_);
                },
                IncorrectFileLink
            );
            break;
        case MixArgs::ExceptionType::INCORRECT_NUMERICAL_PARAM_EXCEPTION:
            EXPECT_THROW
            (
                {
                    MixConverter mix_converter(params.params_);
                },
                IncorrectNumericalParam
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

TEST(test_mix,
     check_process)
{
    MixConverter mix_converter({"$3", "20"});

    SampleVector default_samples(4);
    srandom(time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        FillSampleVector(default_samples);
        SampleBuffer working_sample = default_samples[0];
        mix_converter.Process(working_sample,
                              default_samples);

        for (int j = 0; j < working_sample.size(); ++j)
            EXPECT_EQ(working_sample[j],
                      (i >= 20) ?
                      (default_samples[0][j] + default_samples[3][j]) / 2 :
                      default_samples[0][j]);
    }
}

TEST(test_mix,
     check_get_file_links)
{
    MixConverter mix_converter({"$1", "67"});
    FileLinks file_links = mix_converter.GetFileLinks();
    EXPECT_EQ(file_links.size(),
              2);
    EXPECT_EQ(*file_links.cbegin(),
              0);
    EXPECT_EQ(*std::next(file_links.cbegin(), 1),
              1);
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}