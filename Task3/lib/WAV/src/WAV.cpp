#include "WAV.h"
#include "WAV_errors.h"

WAV::WAV(const std::string & file_name,
         std::ios_base::openmode mode,
         FMTData fmt_data)
:   file_name_(file_name),
    mode_(mode),
    fmt_data_(fmt_data)
{
    if (file_name_.find(".wav") == std::string::npos) throw ExtensionException(file_name_);
    stream_.open(file_name,
                 std::ios_base::binary | mode);
    if (!stream_.good()) throw OpeningException(file_name_);

    if (mode_ & std::ios_base::in)  ReadHeader();
    if (mode_ & std::ios_base::out) WriteHeader(fmt_data_);
}

WAV::~WAV()
{
    if (mode_ & std::ios_base::out) FixHeader();
    stream_.close();
}
