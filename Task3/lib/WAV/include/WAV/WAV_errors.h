#ifndef TASK3_WAV_ERRORS_H
#define TASK3_WAV_ERRORS_H

#include <stdexcept>

class OpeningException : public std::logic_error
{
public:
    explicit OpeningException(const std::string & file_path);
};

class FileFormatException : public std::logic_error
{
protected:
    explicit FileFormatException(const std::string & file_path,
                                 const std::string & desc);
};

class ExtensionException : public FileFormatException
{
public:
    explicit ExtensionException(const std::string & file_path);
};

class RIFFHeaderException : public FileFormatException
{
public:
    explicit RIFFHeaderException(const std::string & file_path);
};

class FormatTypeException : public FileFormatException
{
public:
    explicit FormatTypeException(const std::string & file_path);
};

class FormatDataException : public FileFormatException
{
public:
    explicit FormatDataException(const std::string & file_path);
};


class AudioFormatException : public FileFormatException
{
public:
    explicit AudioFormatException(const std::string & file_path);
};

class ChannelsNumberException : public FileFormatException
{
public:
    explicit ChannelsNumberException(const std::string & file_path);
};

class SampleBitsException : public FileFormatException
{
public:
    explicit SampleBitsException(const std::string & file_path);
};

class SamplingRateException : public FileFormatException
{
public:
    explicit SamplingRateException(const std::string & file_path);
};

class ChunkSearchException : public FileFormatException
{
public:
    explicit ChunkSearchException(const std::string & file_path,
                                  uint32_t chunk_ID);
};

class WritingException : public std::logic_error
{
public:
    explicit WritingException(const std::string & file_path);
};

#endif //TASK3_WAV_ERRORS_H