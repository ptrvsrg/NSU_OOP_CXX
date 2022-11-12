#include "WAV.h"
#include "WAV_errors.h"

void WAV::ReadHeader()
{
    // check RIFF header
    ChunkHeader RIFF_header{};
    stream_.read((char *)&RIFF_header,
                 sizeof(RIFF_header));
    if (!stream_.good()) throw RIFFHeaderException(file_name_);
    if (RIFF_header.ID_ != RIFF) throw RIFFHeaderException(file_name_);

    // check format type
    FormatType format_type;
    stream_.read((char *)&format_type,
                 sizeof(format_type));
    if (!stream_.good()) throw FormatTypeException(file_name_);
    if (format_type != WAVE) throw FormatTypeException(file_name_);

    // check FMT data
    SearchChunk(FMT_);
    FMTData fmt_chunk_data;
    stream_.read((char *)&fmt_chunk_data,
                 sizeof(fmt_chunk_data));
    if (!stream_.good()) throw FormatDataException(file_name_);

    // find DATA data
    SearchChunk(DATA);
}

void WAV::SearchChunk(uint32_t chunk_ID)
{
    ChunkHeader chunk_header{};
    while (true)
    {
        stream_.read((char *)&chunk_header,
                     sizeof(chunk_header));
        if (!stream_.good()) throw ChunkSearchException(file_name_,
                                                        chunk_ID);
        if (chunk_header.ID_ == chunk_ID) break;
        stream_.seekg(chunk_header.size_,
                      std::fstream::cur);
    }
}

size_t WAV::ReadSampleBuffer(SampleBuffer & sample_buffer)
{
    stream_.read((char *)sample_buffer.buffer_.data(),
                 sample_buffer.buffer_.size());
    return stream_.gcount();
}