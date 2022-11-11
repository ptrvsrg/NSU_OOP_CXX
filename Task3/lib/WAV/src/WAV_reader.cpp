#include "WAV_reader.h"
#include "WAV_errors.h"

WAVReader::WAVReader(const std::string & file_name)
    : WAV(file_name)
{
    // file opening
    stream_.open(file_name,
                 std::ios_base::binary | std::ios_base::in);
    if (!stream_.good()) throw FileOpeningException(file_name_);

    // check header
    WAVHeader wav_header;
    stream_.read((char *)&wav_header,
                 sizeof(wav_header));
    if (!stream_.good()) throw FileFormatException(file_name_);

    if (wav_header.ID_ != RIFF ||
        wav_header.format_ != WAVE) throw FileFormatException(file_name_);

    // check format
    FindChunk(FMT_);

    FMTChunkData fmt_chunk_data;
    stream_.read((char *)&fmt_chunk_data,
                 sizeof(fmt_chunk_data));
    if (!stream_.good()) throw FileFormatException(file_name_);

    if (fmt_chunk_data.audio_format_ != AUDIO_FORMAT_PCM)   throw AudioFormatException(file_name_);
    if (fmt_chunk_data.num_channels_ != 1)                  throw ChannelsNumberException(file_name_);
    if (fmt_chunk_data.bits_per_sample_ != 16)              throw SampleBitsException(file_name_);
    if (fmt_chunk_data.samples_rate_ != SAMPLING_RATE)      throw SampleRateException(file_name_);

    // get data chunk
    ChunkHeader data_header = FindChunk(DATA);
    size_ = data_header.size_;
}

size_t WAVReader::Read(char * buffer,
                       size_t count)
{
    if (size_ >= count) size_ -= count;
    else count = size_;
    stream_.read(buffer,
                 static_cast<std::streamsize>(count));
    return count;
}

WAV::ChunkHeader WAVReader::FindChunk(uint32_t chunk_ID)
{
    ChunkHeader chunk_header{};
    while (true)
    {
        stream_.read((char *)&chunk_header,
                     sizeof(chunk_header));
        if (!stream_.good()) throw FileFormatException(file_name_);
        if (chunk_header.ID_ == chunk_ID) break;
        stream_.seekg(chunk_header.size_,
                      std::fstream::cur);
    }

    return chunk_header;
}
