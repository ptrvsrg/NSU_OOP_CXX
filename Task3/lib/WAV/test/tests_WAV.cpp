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
            WAVReader wav_reader(test_dir + "without_DATA_chunk.wav");
        },
        FileFormatException
    );
}

TEST(test_WAV_writer,
     check_constructor)
{
    EXPECT_NO_THROW
    (
        {
            WAVWriter wav_writer(test_dir + "without_DATA_data.wav");
        }
    );
}

TEST(test_WAV_reader_writer,
     copy)
{
    EXPECT_NO_THROW
    (
        {
            {
                WAVReader wav_reader(test_dir + "correct.wav");
                WAVWriter wav_writer(test_dir + "correct_copy.wav");

                char buffer[256];
                while (true)
                {
                    size_t read_count = wav_reader.Read(buffer,
                                                        sizeof(buffer));
                    if (read_count == 0) break;
                    wav_writer.Write(buffer,
                                     read_count);
                }
            }

            WAVReader original_reading(test_dir + "correct.wav");
            WAVReader copy_reading(test_dir + "correct_copy.wav");

            char original_buffer;
            char copy_buffer;
            while (true)
            {
                size_t original_reading_count = original_reading.Read(&original_buffer,
                                                                      sizeof(original_buffer));
                size_t copy_reading_count = copy_reading.Read(&copy_buffer,
                                                              sizeof(copy_buffer));
                if (original_reading_count == 0 && copy_reading_count == 0) break;

                EXPECT_EQ(original_buffer,
                          copy_buffer);
                EXPECT_EQ(original_reading_count,
                          copy_reading_count);
            }
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