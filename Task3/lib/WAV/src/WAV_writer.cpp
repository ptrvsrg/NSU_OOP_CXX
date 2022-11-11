#include "WAV_errors.h"
#include "WAV_writer.h"

WAVWriter::WAVWriter(const std::string & file_name)
    : WAV(file_name)
{
    // file opening
    stream_.open(file_name,
                 std::ios_base::binary | std::ios_base::out);
    if (!stream_.good()) throw FileOpeningException(file_name_);

    // write header
    WAVHeader wav_header;
    Write((const char *)&wav_header,
          sizeof(wav_header));

    // write FMT chunk
    ChunkHeader fmt_header = {
        FMT_,
        sizeof(FMTChunkData)
    };
    Write((const char *)&fmt_header,
          sizeof(fmt_header));

    FMTChunkData fmt_data;
    Write((const char *)&fmt_data,
          sizeof(fmt_data));

    // write DATA chunk header
    ChunkHeader data_header = {
        DATA,
        0
    };
    Write((const char *)&data_header,
          sizeof(data_header));
}

WAVWriter::~WAVWriter()
{
    // get header size position
    stream_.seekp(sizeof(RIFF),
                  std::ios_base::beg);
    size_ -= sizeof(ChunkHeader);
    Write((char *)&size_,
          sizeof(size_));

    // get DATA size position
    size_ -= sizeof(WAVE) ;           // WAVE size
    size_ -= sizeof(ChunkHeader) ;    // FMT chunk header size
    size_ -= sizeof(FMTChunkData);    // FMT chunk data size
    size_ -= sizeof(ChunkHeader),    // DATA chunk data size
    stream_.seekp(size_,
                  std::ios_base::beg);
    Write((char *)&size_,
          sizeof(size_));
}

void WAVWriter::Write(const char * buffer,
                      size_t count)
{
    if (!stream_.is_open()) throw ClosedFileException(file_name_);
    stream_.write((const char *)buffer,
                  static_cast<std::streamsize>(count));
    if (!stream_.good()) throw WritingException(file_name_);
    size_ += count;
}
