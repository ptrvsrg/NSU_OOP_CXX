#include <gtest/gtest.h>
#include "sound_processor.h"
#include "sound_processor_errors.h"

TEST(tests_sound_processor,
     check_OpenWAVReaders)
{
    EXPECT_THROW
    (
        {
            SoundProcessor sound_processor("file/config.txt",
                                           "file/output.wav",
                                           {"file/input0.wav"});
            sound_processor.Convert();
        },
        NonExistentLink
    );
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}