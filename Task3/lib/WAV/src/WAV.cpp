#include "WAV.h"

WAV::WAV(const std::string & file_name)
    : file_name_(file_name) {}

WAV::~WAV()
{
    stream_.close();
}