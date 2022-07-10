#ifndef _MUSX_BASIC_MANAGER_HPP_
#define _MUSX_BASIC_MANAGER_HPP_

#include "ios.hpp"
#include "exception.hpp"
#include <AL/al.h>

PROJECT_NAMESPACE_BEGIN


class basic_manager : public ios_base
{
public:
    basic_manager() : __Msource__(0) {}
    virtual inline void stop()
    {
        alSourceStop(__Msource__);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_SET_ERR, Stop);
    }
    virtual inline void pause()
    {
        alSourcePause(__Msource__);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_SET_ERR, Pause);
    }
    virtual inline void resume()
    {
        alSourceStop(__Msource__);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_SET_ERR, Resume);
    }
    manager_state inline state()
    {
        ALint state;
        alGetSourcei(__Msource__, AL_SOURCE_STATE, &state);
        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW(MUSX_GET_ERR, getState);

        return state == AL_PLAYING ? playing : paused;
    }
    ~basic_manager(){ alDeleteSources(1, &__Msource__); }

    virtual basic_manager& __Mstreamout__() = 0;
protected:
    source_t __Msource__;
};
PROJECT_NAMESPACE_END

#endif //! _MUSX_BASIC_MANAGER_HPP_