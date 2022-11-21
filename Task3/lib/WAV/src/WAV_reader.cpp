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
    if (file_path_.find(".wav") == std::string::npos) throw ExtensionException(file_path_);

    // file opening
    open(file_path_,
         std::ios_base::binary);
    if (!good()) throw std::ios_base::failure(file_path_ + " ");

    ReadHeader();
}

bool WAVReader::ReadSample(SampleBuffer & sample_buffer)
{
    read((char *)&sample_buffer[0],
         sizeof(sample_buffer[0]) * sample_buffer.size());
    if (gcount() == 0) sample_buffer.fill(0);
    return (bool)gcount();
}

void WAVReader::SearchChunk(uint32_t chunk_ID)
{
    ChunkHeader chunk_header{};
    while (true)
    {
        read((char *)&chunk_header,
                     sizeof(chunk_header));
        if (!good()) throw ChunkSearchException(file_path_,
                                                        chunk_ID);
        if (chunk_header.ID_ == chunk_ID) break;
        seekg(chunk_header.size_,
              std::fstream::cur);
    }
}

void WAVReader::ReadHeader()
{
    // check RIFF header
    ChunkHeader RIFF_header{};
    read((char *)&RIFF_header,
         sizeof(RIFF_header));
    if (!good() || RIFF_header.ID_ != RIFF) throw RIFFHeaderException(file_path_);

    // check format type
    FormatType format_type;
    read((char *)&format_type,
         sizeof(format_type));
    if (!good() || format_type != WAVE) throw FormatTypeException(file_path_);

    // check FMT data
    SearchChunk(FMT_);
    FMTChunkData fmt_chunk_data;
    read((char *)&fmt_chunk_data,
         sizeof(fmt_chunk_data));
    if (!good()) throw FormatDataException(file_path_);

    if (fmt_chunk_data.audio_format_ != AUDIO_FORMAT_PCM)   throw AudioFormatException(file_path_);
    if (fmt_chunk_data.num_channels_ != 1)                  throw ChannelsNumberException(file_path_);
    if (fmt_chunk_data.bits_per_sample_ != 16)              throw SampleBitsException(file_path_);
    if (fmt_chunk_data.sampling_rate_ != SAMPLING_RATE)     throw SamplingRateException(file_path_);

    // find DATA data
    SearchChunk(DATA);
}
