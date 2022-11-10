#include "cl_parser_errors.h"

NoConfigFileException::NoConfigFileException()
    : std::logic_error("Configuration file is skipped") {}

NoOutputFileException::NoOutputFileException()
    : std::logic_error("Output file is skipped") {}

NoInputFilesException::NoInputFilesException()
    : std::logic_error("Input files is skipped") {}
