#include "iostream_errors.h"

FileNotOpen::FileNotOpen(std::string file_path)
    : std::ios_base::failure(file_path + " : File is not open ") {}

FileNotWrite::FileNotWrite(std::string file_path)
    : std::ios_base::failure(file_path + " : Can not write to a file ") {}