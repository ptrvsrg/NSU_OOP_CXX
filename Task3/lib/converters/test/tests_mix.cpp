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
                    MixArgs::ExceptionType::INCORRECT_FILE_LINK_EXCEPTION),
            MixArgs({"$0", "12"},
                    MixArgs::ExceptionType::INCORRECT_FILE_LINK_EXCEPTION)
        )
);

TEST_P(MixTest,
       check_init)
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

    std::vector<Sample> input_samples(2);

    EXPECT_THROW
    (
        {
            mix_converter.Process(input_samples);
        },
        IncorrectFileLink
    );

    input_samples.resize(4);
    srandom(time(nullptr));
    for (int i = 0; i < 100 * 44100; ++i)
    {
        FillSampleVector(input_samples);
        Sample output_sample = mix_converter.Process(input_samples);
        EXPECT_EQ(output_sample,
                  (i >= 20 * 44100) ?
                  (input_samples[0] + input_samples[3]) / 2 :
                  input_samples[0]);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}