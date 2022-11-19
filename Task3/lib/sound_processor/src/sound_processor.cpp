#include "sound_processor.h"

SoundProcessor::SoundProcessor(std::string config_file,
                               std::string output_file,
                               std::vector<std::string> input_files)
:   config_file_(std::move(config_file)),
    output_file_(std::move(output_file)),
    input_files_(std::move(input_files)) {}

void SoundProcessor::Convert()
{
    // open config file for getting commands
    ConfigParser config(config_file_);

    // open WAV files for reading
    WAVReaderVector wav_reader_vector(input_files_.size());
    for (int i = 0; i < input_files_.size(); ++i)
        wav_reader_vector[i].Open(input_files_[i]);

    // open WAV file for writing
    WAVWriter wav_writer(output_file_);

    // create converters for the pipeline
    ConverterCreator converter_creator;
    ConverterVector pipeline;
    while (true)
    {
        ConverterCommand converter_command = config.GetConverterCommand();
        if (converter_command.empty()) break;

        // create converter
        ConverterPtr converter_ptr = converter_creator.Create(converter_command);

        // add converter to pipeline
        pipeline.push_back(std::move(converter_ptr));
    }

    // create sample vector to run on the pipeline
    SampleVector sample_vector(input_files_.size() + 1);
    while (UpdateSamplesVector(wav_reader_vector,
                               sample_vector))
    {
        for (ConverterPtr & converter : pipeline)
        {
            Sample processed_sample = converter->Process(sample_vector);
            sample_vector[0] = processed_sample;
        }

        wav_writer.WriteSample(sample_vector[0]);
    }
}

bool SoundProcessor::UpdateSamplesVector(WAVReaderVector & wav_reader_vector,
                                         SampleVector & sample_vector)
{
    // update main sample stream and check end of file
    if (wav_reader_vector[0].ReadSample(sample_vector[1]) == 0) return false;

    // update additional sample streams
    for (int i = 1; i < wav_reader_vector.size(); ++i)
        wav_reader_vector[i].ReadSample(sample_vector[i + 1]);

    return true;
}
