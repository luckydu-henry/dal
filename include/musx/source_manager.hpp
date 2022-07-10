#ifndef _MUSX_SOURCE_HPP_
#define _MUSX_SOURCE_HPP_

#include "basic_manager.hpp"

PROJECT_NAMESPACE_BEGIN


class source_manager : public basic_manager
{
public:
    source_manager()
        :__buffer__(0)
    {
        alGenSources(1, &__Msource__);
        alSourcei(__Msource__, AL_BUFFER, __buffer__);
    }
    
    source_manager& bind(const buffer_t _buf)
    {
        if (_buf != __buffer__)
        {
            __buffer__ = _buf;
            alSourcei(__Msource__, AL_BUFFER, (ALint)__buffer__);

            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_SET_ERR, setBufferToPlay);
        }
        return *this;
    }
    source_manager& set(const gain& _g)
    {
        alSourcef(__Msource__, AL_GAIN, (ALfloat)_g.volume);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_SET_ERR, setGain);
        return *this;
    }
    source_manager& set(const position& _p)
    {
        alSource3f(__Msource__, AL_POSITION, (ALfloat)_p.x, (ALfloat)_p.y, (ALfloat)_p.z);
        if (alGetError() != AL_NO_ERROR)
            throw "Error setting position!";
        return *this;
    }
    source_manager& set(const velocity& _v)
    {
        alSource3f(__Msource__, AL_VELOCITY, (ALfloat)_v.x, (ALfloat)_v.y, (ALfloat)_v.z);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_SET_ERR, setVelocity);
        return *this;
    }
    source_manager& set(const looping& _loop )
    {
        alSourcei(__Msource__, AL_LOOPING, (ALint)_loop);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_SET_ERR, setLooping);
        return *this;
    }
    virtual basic_manager& __Mstreamout__() override
    {
        alSourcePlay(__Msource__);
        ALenum state = AL_PLAYING;
        while (alGetError != AL_NO_ERROR && state == AL_PLAYING)
        {
            alGetSourcei(__Msource__, AL_SOURCE_STATE, &state);
        }
        return *this;
    }
    ~source_manager() = default;
private:
    buffer_t __buffer__;
};
PROJECT_NAMESPACE_END
#endif //!_MUSX_SOURCE_HPP_