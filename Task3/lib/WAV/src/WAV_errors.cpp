#include "WAV_errors.h"

OpeningException::OpeningException(const std::string & file_name)
    : std::logic_error(file_name + ": File opening error") {}

WritingException::WritingException(const std::string & file_name)
    : std::logic_error(file_name + ": Writing error") {}

FileFormatException::FileFormatException(const std::string & file_name,
                                         const std::string & desc)
    : std::logic_error(file_name + ": Wrong file format : " + desc) {}

ExtensionException::ExtensionException(const std::string & file_name)
    :   FileFormatException(file_name,
                            "Incorrect file extension") {}

RIFFHeaderException::RIFFHeaderException(const std::string & file_name)
    :   FileFormatException(file_name,
                            "Incorrect RIFF header") {}

FormatTypeException::FormatTypeException(const std::string &file_name)
:   FileFormatException(file_name,
                        "Incorrect format type") {}

FormatDataException::FormatDataException(const std::string &file_name)
:   FileFormatException(file_name,
                        "Reading format data error") {}

ChunkSearchException::ChunkSearchException(const std::string &file_name,
                                       int32_t chunk_ID)
:   FileFormatException(file_name,
                        "Searching chunk " + std::to_string(chunk_ID) + " error") {}