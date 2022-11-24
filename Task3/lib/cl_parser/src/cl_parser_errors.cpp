#include "cl_parser_errors.h"

NoConfigFile::NoConfigFile()
    : std::invalid_argument("Configuration file is skipped") {}

NoOutputFile::NoOutputFile()
    : std::invalid_argument("Output file is skipped") {}

NoInputFiles::NoInputFiles()
    : std::invalid_argument("Input files is skipped") {}
