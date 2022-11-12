#ifndef TASK3_WAV_ERRORS_H
#define TASK3_WAV_ERRORS_H

#include <stdexcept>

class OpeningException : public std::logic_error
{
public:
    explicit OpeningException(const std::string & file_name);
};

class FileFormatException : public std::logic_error
{
protected:
    explicit FileFormatException(const std::string & file_name,
                                 const std::string & desc);
};

class ExtensionException : public FileFormatException
{
public:
    explicit ExtensionException(const std::string & file_name);
};

class RIFFHeaderException : public FileFormatException
{
public:
    explicit RIFFHeaderException(const std::string & file_name);
};

class FormatTypeException : public FileFormatException
{
public:
    explicit FormatTypeException(const std::string & file_name);
};

class FormatDataException : public FileFormatException
{
public:
    explicit FormatDataException(const std::string & file_name);
};

class ChunkSearchException : public FileFormatException
{
public:
    explicit ChunkSearchException(const std::string & file_name,
                                int32_t chunk_ID);
};

class WritingException : public std::logic_error
{
public:
    explicit WritingException(const std::string & file_name);
};

#endif //TASK3_WAV_ERRORS_H
