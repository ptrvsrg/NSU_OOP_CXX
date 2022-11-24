#ifndef TASK3_WAV_ERRORS_H
#define TASK3_WAV_ERRORS_H

#include <stdexcept>

class IncorrectFileFormat : public std::invalid_argument
{
protected:
    explicit IncorrectFileFormat(const std::string & file_path,
                                 const std::string & desc);
};

class IncorrectExtension : public IncorrectFileFormat
{
public:
    explicit IncorrectExtension(const std::string & file_path);
};

class IncorrectRIFFHeader : public IncorrectFileFormat
{
public:
    explicit IncorrectRIFFHeader(const std::string & file_path);
};

class IncorrectFormatType : public IncorrectFileFormat
{
public:
    explicit IncorrectFormatType(const std::string & file_path);
};

class IncorrectFormatData : public IncorrectFileFormat
{
public:
    explicit IncorrectFormatData(const std::string & file_path);
};


class IncorrectAudioFormat : public IncorrectFileFormat
{
public:
    explicit IncorrectAudioFormat(const std::string & file_path);
};

class IncorrectChannelsNumber : public IncorrectFileFormat
{
public:
    explicit IncorrectChannelsNumber(const std::string & file_path);
};

class IncorrectSampleBits : public IncorrectFileFormat
{
public:
    explicit IncorrectSampleBits(const std::string & file_path);
};

class IncorrectSamplingRate : public IncorrectFileFormat
{
public:
    explicit IncorrectSamplingRate(const std::string & file_path);
};

class ChunkNotFound : public IncorrectFileFormat
{
public:
    explicit ChunkNotFound(const std::string & file_path,
                           uint32_t chunk_ID);
};

#endif //TASK3_WAV_ERRORS_H