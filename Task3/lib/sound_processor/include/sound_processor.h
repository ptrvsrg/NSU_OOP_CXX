#ifndef TASK3_SOUND_PROCESSOR_H
#define TASK3_SOUND_PROCESSOR_H

#include <string>
#include <vector>

#include "config_parser.h"
#include "converter_interface.h"
#include "WAV_reader.h"
#include "WAV_writer.h"

using WAVReaderVector = std::vector<WAVReader>;
using ConverterVector = std::vector<ConverterPtr>;

class SoundProcessor
{
public:
    SoundProcessor(std::string config_file,
                   std::string output_file,
                   std::vector<std::string> input_files);
    void Convert();

private:
    std::string config_file_;
    std::string output_file_;
    std::vector<std::string> input_files_;

    ConverterVector CreatePipeline(ConfigParser & config);
    FileLinks GetFileLinks(const ConverterVector & pipeline);
    WAVReaderVector OpenWAVReaders(const FileLinks & file_links);
    bool UpdateSamplesVector(WAVReaderVector & wav_reader_vector,
                             SampleVector & default_samples);
};

#endif //TASK3_SOUND_PROCESSOR_H
