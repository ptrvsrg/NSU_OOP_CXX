#ifndef TASK3_WAV_TYPES_H
#define TASK3_WAV_TYPES_H

#include <cstdint>

using Sample = int16_t;

const uint32_t RIFF = 0x46464952;
const uint32_t WAVE = 0x45564157;
const uint32_t FMT_ = 0x20746d66;
const uint32_t DATA = 0x61746164;

const uint16_t AUDIO_FORMAT_PCM = 0x0001;
const uint16_t NUM_CHANNELS = 1;
const uint32_t SAMPLING_RATE = 44100;
const uint16_t BLOCK_ALIGN = sizeof(int16_t) * NUM_CHANNELS;
const uint32_t BYTE_RATE = BLOCK_ALIGN * SAMPLING_RATE;
const uint16_t BITS_PER_SAMPLE = 8 * sizeof(int16_t);

struct ChunkHeader
{
    uint32_t ID_;
    uint32_t size_;
};

struct FormatType
{
    uint32_t format_ = WAVE;
};

struct FMTChunkData
{
    uint16_t    audio_format_ = AUDIO_FORMAT_PCM;   // Audio format
    uint16_t    num_channels_ = NUM_CHANNELS;       // Channels number
    uint32_t    sampling_rate_ = SAMPLING_RATE;     // Sampling rate in Hz
    uint32_t    byte_rate_ = BYTE_RATE;             // Bytes number transmitted per second of playback.
    uint16_t    block_align_ = BLOCK_ALIGN;         // Bytes number per sample
    uint16_t    bits_per_sample_ = BITS_PER_SAMPLE; // Bits number in the sample (depth)
};

#endif //TASK3_WAV_TYPES_H
