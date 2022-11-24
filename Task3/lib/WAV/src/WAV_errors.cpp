#include "WAV_errors.h"

IncorrectFileFormat::IncorrectFileFormat(const std::string & file_path,
                                         const std::string & desc)
    : std::invalid_argument(file_path + ": Wrong file format : " + desc) {}

IncorrectExtension::IncorrectExtension(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect file extension") {}

IncorrectRIFFHeader::IncorrectRIFFHeader(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect RIFF header") {}

IncorrectFormatType::IncorrectFormatType(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect format type") {}

IncorrectFormatData::IncorrectFormatData(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Reading format data error") {}

IncorrectAudioFormat::IncorrectAudioFormat(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect audio format") {}

IncorrectChannelsNumber::IncorrectChannelsNumber(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect channels number") {}

IncorrectSampleBits::IncorrectSampleBits(const std::string & file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect number of sample bits") {}

IncorrectSamplingRate::IncorrectSamplingRate(const std::string &file_path)
    : IncorrectFileFormat(file_path,
                          "Incorrect sampling rate") {}

ChunkNotFound::ChunkNotFound(const std::string & file_path,
                             uint32_t chunk_ID)
    : IncorrectFileFormat(file_path,
                            "Searching chunk " + std::to_string(chunk_ID) + " error") {}
