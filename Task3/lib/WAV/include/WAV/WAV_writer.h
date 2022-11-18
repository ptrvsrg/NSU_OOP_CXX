#ifndef TASK3_WAV_WRITER_H
#define TASK3_WAV_WRITER_H

#include "WAV.h"

class WAVWriter : public WAV
{
public:
    explicit WAVWriter(const std::string & file_name);
    ~WAVWriter();
    bool WriteSample(Sample sample);
private:
    void WriteHeader();
    void FixHeader();
};

#endif //TASK3_WAV_WRITER_H
