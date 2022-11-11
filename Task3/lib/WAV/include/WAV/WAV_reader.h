#ifndef TASK3_WAV_READER_H
#define TASK3_WAV_READER_H

#include "WAV.h"

class WAVReader : public WAV
{
public:
    explicit WAVReader(const std::string & file_name);
    bool ReadSample(Sample & sample);
private:
    void FindChunk(uint32_t chunk_ID);
};

#endif //TASK3_WAV_READER_H
