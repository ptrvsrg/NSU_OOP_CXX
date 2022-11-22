#include "WAV_errors.h"
#include "WAV_writer.h"

WAVWriter::WAVWriter(std::string file_path)
{
    Open(std::move(file_path));
}

WAVWriter::~WAVWriter()
{
    FixHeader();
}

void WAVWriter::Open(std::string file_path)
{
    file_path_ = std::move(file_path);

    // file opening
    fout_.open(file_path_,
               std::ios_base::binary);
    if (!fout_.good())
        throw std::ios_base::failure(file_path_ + " ");

    WriteHeader();
}

void WAVWriter::WriteSample(SampleBuffer sample_buffer)
{
    fout_.write((const char *)&sample_buffer[0],
                sizeof(sample_buffer[0]) * sample_buffer.size());

    if (!fout_.good())
        throw std::ios_base::failure(file_path_ + " ");
}

void WAVWriter::WriteHeader()
{
    // write RIFF header
    ChunkHeader RIFF_header = {
        RIFF,
        0
    };
    fout_.write((const char *)&RIFF_header,
                sizeof(RIFF_header));

    // write format type
    FormatType format_type = WAVE;
    fout_.write((const char *)&format_type,
                sizeof(format_type));

    // write FMT header
    ChunkHeader FMT_header = {
        FMT_,
        sizeof(FMTChunkData)
    };
    fout_.write((const char *)&FMT_header,
                sizeof(FMT_header));

    // write FMT data
    FMTChunkData fmt_data;
    fout_.write((const char *)&fmt_data,
                sizeof(fmt_data));

    // write DATA header
    ChunkHeader data_header = {
        DATA,
        0
    };
    fout_.write((const char *)&data_header,
                sizeof(data_header));
}

void WAVWriter::FixHeader()
{
    // get file size
    fout_.seekp(0,
                std::ios_base::end);
    uint32_t file_size = fout_.tellp();

    // get RIFF header size position
    fout_.seekp(sizeof(RIFF),               // RIFF ID size
                std::ios_base::beg);
    file_size -= sizeof(ChunkHeader);       // RIFF header
    fout_.write((const char *)&file_size,
                sizeof(file_size));

    // get DATA header size position
    file_size -= sizeof(FormatType)         // Format type size
                 + sizeof(ChunkHeader)      // FMT chunk header size
                 + sizeof(FMTChunkData)     // FMT chunk data size
                 + sizeof(ChunkHeader);     // DATA chunk data size
    fout_.seekp(sizeof(ChunkHeader)         // RIFF header size
                + sizeof(FormatType)        // Format type size
                + sizeof(ChunkHeader)       // FMT header size
                + sizeof(FMTChunkData)      // FMT data size
                + sizeof(DATA),             // DATA ID size
                std::ios_base::beg);
    fout_.write((char *)&file_size,
                sizeof(file_size));
}
