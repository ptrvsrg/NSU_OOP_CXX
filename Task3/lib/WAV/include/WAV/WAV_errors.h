#ifndef TASK3_WAV_ERRORS_H
#define TASK3_WAV_ERRORS_H

#include <stdexcept>

class FileOpeningException : public std::logic_error
{
public:
    explicit FileOpeningException(const std::string & file_name);
};

class FileFormatException : public std::logic_error
{
public:
    explicit FileFormatException(const std::string & file_name);
};

class WritingException : public std::logic_error
{
public:
    explicit WritingException(const std::string & file_name);
};

class AudioFormatException : public std::runtime_error
{
public:
    explicit AudioFormatException(const std::string & file_name);
};

class ChannelsNumberException : public std::runtime_error
{
public:
    explicit ChannelsNumberException(const std::string & file_name);
};

class SampleBitsException : public std::runtime_error
{
public:
    explicit SampleBitsException(const std::string & file_name);
};

class SampleRateException : public std::runtime_error
{
public:
    explicit SampleRateException(const std::string & file_name);
};

#endif //TASK3_WAV_ERRORS_H
