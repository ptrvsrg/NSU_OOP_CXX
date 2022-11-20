#include <gtest/gtest.h>
#include "WAV_errors.h"
#include "WAV_reader.h"
#include "WAV_writer.h"

struct WAVReaderArgs
{
    std::string file_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        EXTENSION_EXCEPTION,
        OPENING_EXCEPTION,
        RIFF_HEADER_EXCEPTION,
        FORMAT_TYPE_EXCEPTION,
        FORMAT_DATA_EXCEPTION,
        AUDIO_FORMAT_EXCEPTION,
        CHANNELS_NUMBER_EXCEPTION,
        SAMPLE_BITS_EXCEPTION,
        SAMPLE_RATE_EXCEPTION,
        CHUNK_SEARCH_EXCEPTION
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
            WAVReaderArgs("files/correct.wav",
                          WAVReaderArgs::ExceptionType::NO_EXCEPTION),
            WAVReaderArgs("files/incorrect_extension.txt",
                          WAVReaderArgs::ExceptionType::EXTENSION_EXCEPTION),
            WAVReaderArgs("files/non_existent.wav",
                          WAVReaderArgs::ExceptionType::OPENING_EXCEPTION),
            WAVReaderArgs("files/empty.wav",
                          WAVReaderArgs::ExceptionType::RIFF_HEADER_EXCEPTION),
            WAVReaderArgs("files/incorrect_RIFF_header.wav",
                          WAVReaderArgs::ExceptionType::RIFF_HEADER_EXCEPTION),
            WAVReaderArgs("files/no_format_type.wav",
                          WAVReaderArgs::ExceptionType::FORMAT_TYPE_EXCEPTION),
            WAVReaderArgs("files/incorrect_format_type.wav",
                          WAVReaderArgs::ExceptionType::FORMAT_TYPE_EXCEPTION),
            WAVReaderArgs("files/incorrect_fmt_chunk.wav",
                          WAVReaderArgs::ExceptionType::FORMAT_DATA_EXCEPTION),
            WAVReaderArgs("files/adpcm_audio_format.wav",
                          WAVReaderArgs::ExceptionType::AUDIO_FORMAT_EXCEPTION),
            WAVReaderArgs("files/stereo.wav",
                          WAVReaderArgs::ExceptionType::CHANNELS_NUMBER_EXCEPTION),
            WAVReaderArgs("files/8_sample_bits.wav",
                          WAVReaderArgs::ExceptionType::SAMPLE_BITS_EXCEPTION),
            WAVReaderArgs("files/8000_hz.wav",
                          WAVReaderArgs::ExceptionType::SAMPLE_RATE_EXCEPTION),
            WAVReaderArgs("files/without_DATA_chunk.wav",
                          WAVReaderArgs::ExceptionType::CHUNK_SEARCH_EXCEPTION)
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
        case WAVReaderArgs::ExceptionType::EXTENSION_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                ExtensionException
            );
            break;
        case WAVReaderArgs::ExceptionType::OPENING_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                std::ios_base::failure
            );
            break;
        case WAVReaderArgs::ExceptionType::RIFF_HEADER_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                RIFFHeaderException
            );
            break;
        case WAVReaderArgs::ExceptionType::FORMAT_TYPE_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                FormatTypeException
            );
            break;
        case WAVReaderArgs::ExceptionType::FORMAT_DATA_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                FormatDataException
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
                SamplingRateException
            );
            break;
        case WAVReaderArgs::ExceptionType::CHUNK_SEARCH_EXCEPTION:
            EXPECT_THROW
            (
                {
                    WAVReader wav_reader(params.file_);
                },
                ChunkSearchException
            );
            break;
    }
}

TEST(test_WAV_writer,
     check_constructor)
{
    EXPECT_NO_THROW
    (
        {
            WAVWriter wav_writer("files/without_DATA_data.wav");
        }
    );
}

TEST(test_WAV,
     copy)
{
    Sample original_sample;
    {
        WAVReader original_reader("files/correct.wav");
        WAVWriter copy_writer("files/correct_copy.wav");


        while (true)
        {
            if (original_reader.ReadSample(original_sample) == 0) break;
            copy_writer.WriteSample(original_sample);
        }
    }

    WAVReader original_reader("files/correct.wav");
    WAVReader copy_reader("files/correct_copy.wav");

    Sample copy_sample;

    while (true)
    {
        size_t status = original_reader.ReadSample(original_sample);

        EXPECT_EQ(status,
                  copy_reader.ReadSample(copy_sample));

        if (status == 0) break;

        EXPECT_EQ(original_sample,
                  copy_sample);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}