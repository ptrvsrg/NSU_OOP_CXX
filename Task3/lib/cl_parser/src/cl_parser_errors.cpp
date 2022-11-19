#include "cl_parser_errors.h"

NoConfigFileException::NoConfigFileException()
    : std::invalid_argument("Configuration file is skipped") {}

NoOutputFileException::NoOutputFileException()
    : std::invalid_argument("Output file is skipped") {}

NoInputFilesException::NoInputFilesException()
    : std::invalid_argument("Input files is skipped") {}
