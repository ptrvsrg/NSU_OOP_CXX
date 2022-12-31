#include <gtest/gtest.h>
#include "mode_creator.h"

TEST(test_mode_creator,
     test_create)
{
    EXPECT_THROW
    (
        {
            ModePtr mode_ptr = ModeCreator::Create({},
                                                   "very_fast",
                                                   0,
                                                   "",
                                                   Matrix());
        },
        ModeNameException
    );

    EXPECT_NO_THROW
    (
        ModePtr mode_ptr = ModeCreator::Create({},
                                               "detailed",
                                               0,
                                               "",
                                               Matrix());
    );

    EXPECT_NO_THROW
    (
        ModePtr mode_ptr = ModeCreator::Create({},
                                               "fast",
                                               0,
                                               "",
                                               Matrix());
    );

    EXPECT_NO_THROW
    (
        ModePtr mode_ptr = ModeCreator::Create({},
                                               "tournament",
                                               0,
                                               "",
                                               Matrix());
    );
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}