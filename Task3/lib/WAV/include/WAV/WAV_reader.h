#ifndef TASK3_WAV_READER_H
#define TASK3_WAV_READER_H

#include "WAV.h"

class WAVReader : public WAV
{
public:
    explicit WAVReader(const std::string & file_name);
    size_t Read(char * buffer,
              size_t count);
private:
    WAV::ChunkHeader FindChunk(uint32_t chunk_ID);
};

#endif //TASK3_WAV_READER_H
