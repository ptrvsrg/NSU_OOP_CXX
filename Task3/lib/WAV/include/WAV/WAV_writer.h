#ifndef TASK3_WAV_WRITER_H
#define TASK3_WAV_WRITER_H

#include "WAV.h"

class WAVWriter : public WAV
{
public:
    explicit WAVWriter(const std::string & file_name);
    ~WAVWriter();
    void Write(const char * buffer,
               size_t count);
private:
};

#endif //TASK3_WAV_WRITER_H
