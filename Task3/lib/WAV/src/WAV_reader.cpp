#include "WAV_reader.h"
#include "WAV_errors.h"

WAVReader::WAVReader(std::string file_path)
{
    Open(std::move(file_path));
}

void WAVReader::Open(std::string file_path)
{
    file_path_ = std::move(file_path);

    // check file extension
    if (file_path_.find(".wav") == std::string::npos)
        throw IncorrectExtension(file_path_);

    // file opening
    fin_.open(file_path_,
              std::ios_base::binary);
    if (!fin_.good())
        throw std::ios_base::failure(file_path_ + " ");

    ReadHeader();
}

bool WAVReader::ReadSample(SampleBuffer & sample_buffer)
{
    fin_.read((char *)&sample_buffer[0],
              sizeof(sample_buffer[0]) * sample_buffer.size());
    if (fin_.gcount() == 0)
        sample_buffer.fill(0);
    return (bool)fin_.gcount();
}

void WAVReader::SearchChunk(uint32_t chunk_ID)
{
    ChunkHeader chunk_header{};
    while (true)
    {
        fin_.read((char *)&chunk_header,
                  sizeof(chunk_header));
        if (!fin_.good())
            throw ChunkNotFound(file_path_,
                                chunk_ID);
        if (chunk_header.ID_ == chunk_ID)
            break;
        fin_.seekg(chunk_header.size_,
                   std::fstream::cur);
    }
}

void WAVReader::ReadHeader()
{
    // check RIFF header
    ChunkHeader RIFF_header{};
    fin_.read((char *)&RIFF_header,
              sizeof(RIFF_header));
    if (!fin_.good() || RIFF_header.ID_ != RIFF)
        throw IncorrectRIFFHeader(file_path_);

    // check format type
    FormatType format_type;
    fin_.read((char *)&format_type,
              sizeof(format_type));
    if (!fin_.good() || format_type != WAVE)
        throw IncorrectFormatType(file_path_);

    // check FMT data
    SearchChunk(FMT_);
    FMTChunkData fmt_chunk_data;
    fin_.read((char *)&fmt_chunk_data,
              sizeof(fmt_chunk_data));
    if (!fin_.good())
        throw IncorrectFormatData(file_path_);

    if (fmt_chunk_data.audio_format_ != AUDIO_FORMAT_PCM)   throw IncorrectAudioFormat(file_path_);
    if (fmt_chunk_data.num_channels_ != 1)                  throw IncorrectChannelsNumber(file_path_);
    if (fmt_chunk_data.bits_per_sample_ != 16)              throw IncorrectSampleBits(file_path_);
    if (fmt_chunk_data.sampling_rate_ != SAMPLING_RATE)     throw IncorrectSamplingRate(file_path_);

    // find DATA data
    SearchChunk(DATA);
}
