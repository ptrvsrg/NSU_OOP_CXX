#include <gtest/gtest.h>
#include "WAV.h"
#include "WAV_errors.h"

std::string test_dir = "/home/acer/NSU_OOP_CXX/Task3/lib/WAV/test/files/";

TEST(test_WAV,
     check_constructor)
{
    EXPECT_NO_THROW
    (
        {
            WAV wav_reader(test_dir + "correct.wav",
                           std::ios_base::in);
        }
    );

    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "incorrect_extension.txt",
                           std::ios_base::in);
        },
        ExtensionException
    );

    EXPECT_THROW
    (
        {
            WAV wav_reader("non_existent.wav",
                           std::ios_base::in);
        },
        OpeningException
    );
}

TEST(test_WAV,
     check_read_header)
{
    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "empty.wav",
                           std::ios_base::in);
        },
        RIFFHeaderException
    );

    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "incorrect_RIFF_header.wav",
                           std::ios_base::in);
        },
        RIFFHeaderException
    );

    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "without_format_type.wav",
                           std::ios_base::in);
        },
        FormatTypeException
    );

    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "incorrect_format_type.wav",
                           std::ios_base::in);
        },
        FormatTypeException
    );

    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "without_fmt_data.wav",
                           std::ios_base::in);
        },
        FormatDataException
    );
}

TEST(test_WAV,
     check_search_chunk)
{
    EXPECT_THROW
    (
        {
            WAV wav_reader(test_dir + "without_DATA_chunk.wav");
        },
        ChunkSearchException
    );
}

TEST(test_WAV_writer,
     check_constructor)
{
    EXPECT_NO_THROW
    (
        {
            WAV wav_writer(test_dir + "without_DATA_data.wav",
                           std::ios_base::out);
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