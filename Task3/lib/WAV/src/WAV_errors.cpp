#include "WAV_errors.h"

FileFormatException::FileFormatException(const std::string & file_path,
                                         const std::string & desc)
    : std::invalid_argument(file_path + ": Wrong file format : " + desc) {}

ExtensionException::ExtensionException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Incorrect file extension") {}

RIFFHeaderException::RIFFHeaderException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Incorrect RIFF header") {}

FormatTypeException::FormatTypeException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Incorrect format type") {}

FormatDataException::FormatDataException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Reading format data error") {}

AudioFormatException::AudioFormatException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Incorrect audio format") {}

ChannelsNumberException::ChannelsNumberException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Incorrect channels number") {}

SampleBitsException::SampleBitsException(const std::string & file_path)
    :   FileFormatException(file_path,
                            "Incorrect number of sample bits") {}

SamplingRateException::SamplingRateException(const std::string &file_path)
    :   FileFormatException(file_path,
                            "Incorrect sampling rate") {}

ChunkSearchException::ChunkSearchException(const std::string & file_path,
                                           uint32_t chunk_ID)
    :   FileFormatException(file_path,
                            "Searching chunk " + std::to_string(chunk_ID) + " error") {}
