#ifndef _MUSX_SNDFILE_HPP_
#define _MUSX_SNDFILE_HPP_

#include "basic_sndstream.hpp"
#include "exception.hpp"
#include <sndfile.h>

PROJECT_NAMESPACE_BEGIN

class isndstream : public basic_sndstream
{
public:
    isndstream() = default;
    isndstream(const char* _path, openmode _mode = ios_base::in)
    {
        __Mopen__(_path, _mode);
    }
    isndstream& open(const char* _path, openmode _mode = ios_base::in )
    {
        close();
        __Mopen__(_path, _mode);
        return *this;
    }
    inline int command(sfc _enum, void* _data = nullptr, int _datasize = 0)
    {
        return sf_command(__Mfile__, _enum, _data, _datasize);
    }
    inline std::size_t read(short* _membuf, std::size_t _frames)
    {
        std::size_t num_frames = sf_readf_short(__Mfile__, _membuf, _frames);
        return num_frames;
    }
    isndstream& close(){
        if (__Mfile__) sf_close(__Mfile__);
        return *this;
    }
    ~isndstream(){ close(); __Mfile__ = nullptr; }
    virtual bool is_open() override
    {
        return !__Mfile__ ? false : true;
    }
    //! Info for the audio.
    SF_INFO info;
private:
    inline void __Mopen__(const char* _path, openmode _mode)
    {
        __Mfile__ = sf_open(_path, _mode, &info);
        if (!__Mfile__)
            MUSX_THROW(MUSX_ARG_ERR, sf_open);
        if (info.frames < 1 ||
         info.frames > (0x7FFFFFFF >> 1) / info.channels)
        {
            sf_close(__Mfile__);
            MUSX_THROW("Bad sample.", sf_open);
        }
    }
    SNDFILE* __Mfile__;
};

PROJECT_NAMESPACE_END



#endif //!_MUSX_SNDFILE_HPP_
