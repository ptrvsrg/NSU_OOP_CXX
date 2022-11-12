#ifndef TASK3_WAV_H
#define TASK3_WAV_H

#include <cstdint>
#include <fstream>
#include <vector>

using FormatType = uint32_t;
const uint32_t RIFF = 0x46464952;
const uint32_t WAVE = 0x45564157;
const uint32_t FMT_ = 0x20746d66;
const uint32_t DATA = 0x61746164;
const uint16_t AUDIO_FORMAT_PCM = 0x0001;
const int BITS_PER_BYTE = 8;

struct SampleBuffer
{
    std::vector<int8_t> buffer_;
    uint16_t num_channels_;
    uint16_t bits_per_sample_;
};

struct FMTData
{
    uint16_t audio_format_ = AUDIO_FORMAT_PCM;                   // Audio format
    uint16_t num_channels_ = 1;                                  // Channels number
    uint32_t sampling_rate_ = 44100;                             // Sampling rate in Hz
    uint32_t byte_rate_ = sizeof(int16_t) * 44100 * 1;           // Bytes number transmitted per second of playback.
    uint16_t block_align_ = sizeof(int16_t) * 1;                 // Bytes number per sample
    uint16_t bits_per_sample_ = sizeof(int16_t) * BITS_PER_BYTE; // Bits number in the sample (depth)
};

struct ChunkHeader
{
    uint32_t ID_;
    uint32_t size_;
};

class WAV
{
public:
    explicit WAV(const std::string & file_name,
                 std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out,
                 FMTData fmt_data = FMTData());
    size_t ReadSampleBuffer(SampleBuffer & sample_buffer);
    void WriteSampleBuffer(SampleBuffer sample_buffer);
    ~WAV();
private:
    std::string file_name_;
    std::fstream stream_;
    std::ios_base::openmode mode_;
    FMTData fmt_data_;

    void ReadHeader();
    void WriteHeader(FMTData fmt_data);
    void FixHeader();
    void SearchChunk(uint32_t chunk_ID);
};

#endif //TASK3_WAV_H
