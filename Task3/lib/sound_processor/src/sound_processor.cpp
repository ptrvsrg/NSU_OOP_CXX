#include "sound_processor.h"
#include "sound_processor_errors.h"

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

    // create converters for the pipeline
    ConverterVector pipeline = std::move(CreatePipeline(config));

    // open only necessary WAV files for reading
    WAVReaderVector wav_reader_vector = std::move(OpenWAVReaders(GetFileLinks(pipeline)));

    // open WAV file for writing
    WAVWriter wav_writer(output_file_);

    // create sample vector to run on the pipeline
    SampleVector default_samples(input_files_.size());
    while (UpdateSamplesVector(wav_reader_vector,
                               default_samples))
    {
        // create a working sample and
        // initialize with a sample from the main WAV file
        SampleBuffer working_sample = default_samples[0];

        for (ConverterPtr & converter : pipeline)
            converter->Process(working_sample,
                               default_samples);

        wav_writer.WriteSample(working_sample);
    }
}

ConverterVector SoundProcessor::CreatePipeline(ConfigParser & config)
{
    ConverterCreator converter_creator;
    ConverterVector pipeline;
    while (true)
    {
        // get converter command from config file
        ConverterCommand converter_command = config.GetConverterCommand();
        if (converter_command.empty())
            break;

        // create converter
        ConverterPtr converter_ptr = converter_creator.Create(converter_command);

        // add converter to pipeline
        pipeline.push_back(std::move(converter_ptr));
    }

    return pipeline;
}

FileLinks SoundProcessor::GetFileLinks(const ConverterVector & pipeline)
{
    FileLinks file_links;
    for (const ConverterPtr & converter : pipeline)
        file_links.merge(converter->GetFileLinks());

    return file_links;
}

WAVReaderVector SoundProcessor::OpenWAVReaders(const FileLinks & file_links)
{
    WAVReaderVector wav_reader_vector(input_files_.size());
    for (int i : file_links)
    {
        if (i >= input_files_.size())
            throw NonExistentLink(i);
        wav_reader_vector[i].Open(input_files_[i]);
    }

    return wav_reader_vector;
}

bool SoundProcessor::UpdateSamplesVector(WAVReaderVector & wav_reader_vector,
                                         SampleVector & default_samples)
{
    // update main sample stream and check end of file
    if (!wav_reader_vector[0].ReadSample(default_samples[0]))
        return false;

    // update additional sample streams
    for (int i = 1; i < wav_reader_vector.size(); ++i)
        wav_reader_vector[i].ReadSample(default_samples[i]);

    return true;
}
