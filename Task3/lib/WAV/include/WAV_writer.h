#ifndef TASK3_WAV_WRITER_H
#define TASK3_WAV_WRITER_H

#include <fstream>
#include <string>
#include "WAV_types.h"

class WAVWriter
{
public:
    WAVWriter() = default;
    explicit WAVWriter(std::string file_path);
    ~WAVWriter();
    void Open(std::string file_path);
    void WriteSample(SampleBuffer sample_buffer);

private:
    std::ofstream fout_;
    std::string file_path_;

    void WriteHeader();
    void FixHeader();
};

#endif //TASK3_WAV_WRITER_H
