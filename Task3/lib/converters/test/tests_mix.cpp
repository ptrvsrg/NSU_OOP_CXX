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
        INCORRECT_FILE_LINK_EXCEPTION
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
                    MixArgs::ExceptionType::INCORRECT_FILE_LINK_EXCEPTION)
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

TEST(test_mix,
     check_process)
{
    MixConverter mix_converter({"$3", "20"});

    std::vector<Sample> default_samples(2);

    EXPECT_THROW
    (
        {
            Sample working_sample;
            mix_converter.Process(working_sample,
                                  default_samples);
        },
        IncorrectFileLink
    );

    default_samples.resize(4);
    srandom(time(nullptr));
    for (int i = 0; i < 100 * 44100; ++i)
    {
        FillSampleVector(default_samples);
        Sample working_sample = default_samples[0];
        mix_converter.Process(working_sample,
                              default_samples);
        EXPECT_EQ(working_sample,
                  (i >= 20 * 44100) ?
                  (default_samples[0] + default_samples[3]) / 2 :
                  default_samples[0]);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}