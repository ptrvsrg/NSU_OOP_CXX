#include "WAV_errors.h"
#include "WAV_writer.h"

WAVWriter::WAVWriter(const std::string & file_name)
    : WAV(file_name)
{
    // file opening
    stream_.open(file_name,
                 std::ios_base::binary | std::ios_base::out);
    if (!stream_.good()) throw FileOpeningException(file_name_);

    // write RIFF header
    ChunkHeader RIFF_header = {
        RIFF,
        0
    };
    Write((const char *)&RIFF_header,
          sizeof(RIFF_header));

    // write format type
    FormatType format_type = {
        WAVE
    };
    Write((const char *)&format_type,
          sizeof(format_type));

    // write FMT header
    ChunkHeader FMT_header = {
        FMT_,
        sizeof(FMTChunkData)
    };
    Write((const char *)&FMT_header,
          sizeof(FMT_header));

    // write FMT data
    FMTChunkData fmt_data;
    Write((const char *)&fmt_data,
          sizeof(fmt_data));

    // write DATA header
    ChunkHeader data_header = {
        DATA,
        0
    };
    Write((const char *)&data_header,
          sizeof(data_header));
}

WAVWriter::~WAVWriter()
{
    // get file size
    stream_.seekp(0,
                  std::ios_base::end);
    uint32_t file_size = stream_.tellp();

    // get RIFF header size position
    stream_.seekp(sizeof(RIFF),             // RIFF ID size
                  std::ios_base::beg);
    file_size -= sizeof(ChunkHeader);       // RIFF header
    Write((const char *)&file_size,
          sizeof(file_size));

    // get DATA header size position
    file_size -= sizeof(FormatType)         // Format type size
            + sizeof(ChunkHeader)           // FMT chunk header size
            + sizeof(FMTChunkData)          // FMT chunk data size
            + sizeof(ChunkHeader);          // DATA chunk data size
    stream_.seekp(sizeof(ChunkHeader)       // RIFF header size
                  + sizeof(FormatType)      // Format type size
                  + sizeof(ChunkHeader)     // FMT header size
                  + sizeof(FMTChunkData)    // FMT data size
                  + sizeof(DATA),           // DATA ID size
                  std::ios_base::beg);
    Write((char *)&file_size,
          sizeof(file_size));
}

void WAVWriter::Write(const char * buffer,
                      size_t count)
{
    stream_.write((const char *)buffer,
                  static_cast<std::streamsize>(count));
    if (!stream_.good()) {
        throw WritingException(file_name_); }
}
