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
    stream_.write((const char *)&RIFF_header,
                  sizeof(RIFF_header));

    // write format type
    FormatType format_type;
    stream_.write((const char *)&format_type,
                  sizeof(format_type));

    // write FMT header
    ChunkHeader FMT_header = {
        FMT_,
        sizeof(FMTChunkData)
    };
    stream_.write((const char *)&FMT_header,
                  sizeof(FMT_header));

    // write FMT data
    FMTChunkData fmt_data;
    stream_.write((const char *)&fmt_data,
                  sizeof(fmt_data));

    // write DATA header
    ChunkHeader data_header = {
        DATA,
        0
    };
    stream_.write((const char *)&data_header,
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
    stream_.write((const char *)&file_size,
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
    stream_.write((char *)&file_size,
                  sizeof(file_size));
}

bool WAVWriter::WriteSample(Sample sample)
{
    stream_.write((const char *)&sample,
                  sizeof(sample));
    return stream_.good();
}
