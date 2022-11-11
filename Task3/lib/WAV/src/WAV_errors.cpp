#include "WAV_errors.h"

FileOpeningException::FileOpeningException(const std::string & file_name)
    : std::logic_error(file_name + ": File opening error\n") {}

FileFormatException::FileFormatException(const std::string & file_name)
    : std::logic_error(file_name + ": Wrong file format\n") {}

WritingException::WritingException(const std::string & file_name)
    : std::logic_error(file_name + ": Writing error") {}

AudioFormatException::AudioFormatException(const std::string & file_name)
    : std::runtime_error(file_name + ": Wrong audio format\n") {}

ChannelsNumberException::ChannelsNumberException(const std::string & file_name)
    : std::runtime_error(file_name + ": Wrong channels number\n") {}

SampleBitsException::SampleBitsException(const std::string & file_name)
    : std::runtime_error(file_name + ": Wrong bits number in the sample\n") {}

SampleRateException::SampleRateException(const std::string & file_name)
    : std::runtime_error(file_name + ": Wrong sampling frequency\n") {}