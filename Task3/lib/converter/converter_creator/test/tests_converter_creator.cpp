#include <gtest/gtest.h>
#include "converter_interface.h"
#include "converter_creator_errors.h"

struct CreatorArgs
{
    ConverterCommand converter_command_;
    bool exception_;

    CreatorArgs(ConverterCommand converter_command,
                bool exception)
    :   converter_command_(std::move(converter_command)),
        exception_(exception) {}
};

class CreatorTest : public ::testing::TestWithParam<CreatorArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_converter_creator,
    CreatorTest,
    ::testing::Values
    (
        CreatorArgs({"double", "0", "10"},
                    false),
        CreatorArgs({"mute", "0", "10"},
                    false),
        CreatorArgs({"mix", "$1", "10"},
                    false),
        CreatorArgs({"compress"},
                    true)
    )
);

TEST_P(CreatorTest,
       check_create)
{
    CreatorArgs params = GetParam();

    if (params.exception_)
        EXPECT_THROW
        (
            {
                ConverterPtr converter_ptr = ConverterInterface::Create(params.converter_command_);
            },
            IncorrectConverterNameException
        );
    else

        EXPECT_NO_THROW
        (
            {
                ConverterPtr converter_ptr = ConverterInterface::Create(params.converter_command_);
            }
        );
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}