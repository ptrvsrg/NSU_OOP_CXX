#include <gtest/gtest.h>
#include "converter_creator.h"
#include "converter_creator_errors.h"

TEST(test_converter_creator,
     check_create)
{
    EXPECT_THROW
    (
        {
            ConverterCreator converter_creator;
            ConverterPtr converter = converter_creator.Create({"compress"});
        },
        IncorrectConverterNameException
    );
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}