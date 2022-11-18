#include "WAV.h"

WAV::WAV(std::string file_path)
:   file_path_(std::move(file_path)) {}

WAV::~WAV()
{
    if (!stream_.is_open()) stream_.close();
}
