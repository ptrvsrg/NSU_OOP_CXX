#include <gtest/gtest.h>
#include "WAV_errors.h"
#include "WAV_reader.h"
#include "WAV_writer.h"

std::string test_dir = "/home/acer/NSU_OOP_CXX/Task3/lib/WAV/test/files/";

struct WAVReaderArgs
{
    std::string file_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        FILE_OPENING_EXCEPTION,
        FILE_FORMAT_EXCEPTION,
        AUDIO_FORMAT_EXCEPTION,
        CHANNELS_NUMBER_EXCEPTION,
        SAMPLE_BITS_EXCEPTION,
        SAMPLE_RATE_EXCEPTION
    } exception_type_;

    WAVReaderArgs(std::string file,
                  ExceptionType exception_type)
    :   file_(std::move(file)),
        exception_type_(exception_type) {}
};

class WAVReaderTest : public ::testing::TestWithParam<WAVReaderArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_WAV_reader,
    WAVReaderTest,
    ::testing::Values
        (
            WAVReaderArgs(test_dir + "correct.wav",
                          WAVReaderArgs::ExceptionType::NO_EXCEPTION),
            WAVReaderArgs(test_dir + "mp3_file_format.mp3",
                          WAVReaderArgs::ExceptionType::FILE_FORMAT_EXCEPTION),
            WAVReaderArgs(test_dir + "non_existent.wav",
                          WAVReaderArgs::ExceptionType::FILE_OPENING_EXCEPTION),
            WAVReaderArgs(test_dir + "wrong_header.wav",
                          WAVReaderArgs::ExceptionType::FILE_FORMAT_EXCEPTION),
            WAVReaderArgs(test_dir + "wrong_fmt_chunk.wav",
                          WAVReaderArgs::ExceptionType::FILE_FORMAT_EXCEPTION),
            WAVReaderArgs(test_dir + "adpcm_audio_format.wav",
                          WAVReaderArgs::ExceptionType::AUDIO_FORMAT_EXCEPTION),
            WAVReaderArgs(test_dir + "stereo.wav",
                          WAVReaderArgs::ExceptionType::CHANNELS_NUMBER_EXCEPTION),
            WAVReaderArgs(test_dir + "8_sample_bits.wav",
                          WAVReaderArgs::ExceptionType::SAMPLE_BITS_EXCEPTION),
            WAVReaderArgs(test_dir + "8000_hz.wav",
                          WAVReaderArgs::ExceptionType::SAMPLE_RATE_EXCEPTION)
        )
);

TEST_P(WAVReaderTest,
       check_constructor)
{
    WAVReaderArgs params = GetParam();
    switch (params.exception_type_)
    {
        case WAVReaderArgs::ExceptionType::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                }
            );
            break;
        case WAVReaderArgs::ExceptionType::FILE_OPENING_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                FileOpeningException
            );
            break;
        case WAVReaderArgs::ExceptionType::FILE_FORMAT_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                FileFormatException
            );
            break;
        case WAVReaderArgs::ExceptionType::AUDIO_FORMAT_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                AudioFormatException
            );
            break;
        case WAVReaderArgs::ExceptionType::CHANNELS_NUMBER_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                ChannelsNumberException
            );
            break;
        case WAVReaderArgs::ExceptionType::SAMPLE_BITS_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                SampleBitsException
            );
            break;
        case WAVReaderArgs::ExceptionType::SAMPLE_RATE_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                SampleRateException
            );
            break;
    }
}

TEST(test_WAV_reader,
     check_find_chunk)
{
    EXPECT_THROW
    (
        {
            WAVReader wav_reader(test_dir + "without_data.wav");
        },
        FileFormatException
    );
}

struct WAVWriterArgs
{
    std::string file_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        FILE_OPENING_EXCEPTION,
    } exception_type_;

    WAVWriterArgs(std::string file,
                  ExceptionType exception_type)
        :   file_(std::move(file)),
            exception_type_(exception_type) {}
};

class WAVWriterTest : public ::testing::TestWithParam<WAVWriterArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_WAV_writer,
    WAVWriterTest,
    ::testing::Values
        (
            WAVWriterArgs(test_dir + "writer.wav",
                          WAVWriterArgs::ExceptionType::NO_EXCEPTION)
        )
);

TEST_P(WAVWriterTest,
       check_constructor)
{
    WAVWriterArgs params = GetParam();
    switch (params.exception_type_)
    {
        case WAVWriterArgs::ExceptionType::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                {
                    WAVWriter wav_writer(params.file_);
                }
            );
            break;
        case WAVWriterArgs::ExceptionType::FILE_OPENING_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVWriter wav_writer(params.file_);
                },
                FileOpeningException
            );
            break;
    }
}

//TEST(test_WAV_reader_writer, copy)
//{
//    {
//        WAVReader wav_reader(test_dir + "sample-3s.wav");
//        WAVWriter wav_writer(test_dir + "sample-3s-copy.wav");
//
//        char buffer;
//        while (wav_reader.Read(&buffer,
//                               1) == 1)
//        {
//            wav_writer.Write(&buffer,
//                             1);
//        }
//    }
//
////    WAVReader original_reading(test_dir + "sample-3s.wav");
////    WAVReader copy_reading(test_dir + "sample-3s-copy.wav");
////
////    char original_buffer;
////    char copy_buffer;
////    while (original_reading.Read(&original_buffer, 1) == 1 ||
////           copy_reading.Read(&copy_buffer, 1) == 1)
////    {
////        EXPECT_EQ(original_buffer,
////                  copy_buffer);
////    }
//}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}