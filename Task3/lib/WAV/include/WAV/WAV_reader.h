#ifndef TASK3_WAV_READER_H
#define TASK3_WAV_READER_H

#include "WAV.h"

class WAVReader : public WAV
{
public:
    explicit WAVReader(std::string file_path);
    size_t ReadSample(Sample & sample);

private:
    void SearchChunk(uint32_t chunk_ID);
    void ReadHeader();
};

#endif //TASK3_WAV_READER_H
