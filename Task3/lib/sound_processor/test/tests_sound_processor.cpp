#include <gtest/gtest.h>
#include "sound_processor.h"

std::string test_dir = "/home/acer/NSU_OOP_CXX/Task3/lib/sound_processor/test/files/";

TEST(test_sound_processor,
     check_convert)
{
    SoundProcessor sound_processor(test_dir + "config.txt",
                                   test_dir + "output.wav",
                                   {test_dir + "input1.wav",
                                    test_dir + "input2.wav"});
    sound_processor.Convert();
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}