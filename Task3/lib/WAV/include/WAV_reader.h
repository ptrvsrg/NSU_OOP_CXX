#ifndef TASK3_WAV_READER_H
#define TASK3_WAV_READER_H

#include <fstream>
#include <string>
#include "WAV_types.h"

class WAVReader
{
public:
    WAVReader() = default;
    explicit WAVReader(std::string file_path);
    ~WAVReader() = default;
    void Open(std::string file_path);
    bool ReadSample(SampleBuffer & sample_buffer);

private:
    std::ifstream fin_;
    std::string file_path_;

    void SearchChunk(uint32_t chunk_ID);
    void ReadHeader();
};

#endif //TASK3_WAV_READER_H
