#ifndef _MUSX_SNDBUFFER_HPP_
#define _MUSX_SNDBUFFER_HPP_

#include "exception.hpp"
#include "isndstream.hpp"
#include "ios.hpp"
#include <vector>
#include <string>
#include <AL/al.h>

PROJECT_NAMESPACE_BEGIN

class buffer_tool : public ios_base
{
public:
	//! summary:
	//! The get() function of this singleton class.
	//! returns:
    //! Returns the class ptr.
	static buffer_tool* get()
    {
        static buffer_tool* sndbuf = new buffer_tool();
        return sndbuf;
    }
	//! summary:
	//! This function can load audio from file and push it in the buffer vector.
	//! param _path:
    //! Your audio path.
	//! returns:
    //! Returns the buffer.
    buffer_t copy_from_stream(isndstream& _stream)
    {
        return __Mstream_gen__(_stream);
    }
    void extract_from_stream(buffer_t& _buf, isndstream& _stream)
    {
        _buf = __Mstream_gen__(_stream);
    }
	//! summary:
	//! Unload buffer from vector. (This is neccesarry if you don't want to use a buffer)
	bool del(const buffer_t& _bid)
    {
        auto it = __Mbuffers__.begin();
        while (it != __Mbuffers__.end())
        {
            if (*it == _bid)
            {
                alDeleteBuffers(1, &(*it));
                it = __Mbuffers__.erase(it);
                return true;
            }
            else ++it;
        }
        return true;
    }
private:
    std::vector<buffer_t> __Mbuffers__;
	buffer_tool(){ __Mbuffers__.clear();}
	~buffer_tool()
    {
        alDeleteBuffers((ALuint)__Mbuffers__.size(), __Mbuffers__.data());
        __Mbuffers__.clear();
    }
    buffer_t __Mstream_gen__(isndstream& _stream)
    {
        ios_base::format format = 0;
        //! Check the extention format.
        bool ext_fmt = _stream.command(isndstream::wavex_get_ambisonic) 
                                    == isndstream::ambisonic_bformat ? true : false;
        switch(_stream.info.channels)
        {
            case 1:
                format = ios_base::mono_16;
                break;
            case 2:
                format = ios_base::stereo_16;
                break;
            case 3:
                if (ext_fmt)
                format = ios_base::bformat2d_16;
            case 4:
                if (ext_fmt)
                format = ios_base::bformat3d_16;
        }
        short* membuf;
        int bps;

        membuf = new short[(_stream.info.frames * _stream.info.channels) << 1];
        std::size_t num_frames = _stream.read(membuf, _stream.info.frames);
        if (num_frames < 1)
        {
            delete membuf;
            _stream.close();
            MUSX_THROW("Error reading frames", read);
        }
        bps = (num_frames * _stream.info.channels) << 1;

        ALuint buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, membuf, bps, _stream.info.samplerate);

        //! Check AL error occured, and clean up if so.
        ALenum err = alGetError();
        if (err != AL_NO_ERROR)
        {
            if (buffer && alIsBuffer(buffer))
                alDeleteBuffers(1, &buffer);
            MUSX_THROW(alGetString(err), alGetError);
        }

        delete membuf;
        return buffer;
    }
};

PROJECT_NAMESPACE_END
#endif //! _MUSX_SNDBUFFER_HPP_