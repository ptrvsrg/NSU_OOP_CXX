#include <iostream>

#include "cl_parser.h"
#include "sound_processor.h"

int main(int argc,
         char ** argv)
{
    try
    {
        Options opts;
        GetOptions(argc,
                   argv,
                   opts);

        SoundProcessor sound_processor(opts.config_file_,
                                       opts.output_file_,
                                       opts.input_files_);
        sound_processor.Convert();
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}