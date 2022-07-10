#ifndef _MUSX_STREAMING_M_HPP_
#define _MUSX_STREAMING_M_HPP_

#include "basic_manager.hpp"
#include "isndstream.hpp"
#include <cstdlib>
PROJECT_NAMESPACE_BEGIN
class streaming_manager : public basic_manager
{
private:
	static const int BUFFER_SAMPLES = 8192;
	static const int NUM_BUFFERS = 4;
	ALuint p_Buffers[NUM_BUFFERS];
    isndstream snd;
	short* p_Membuf;
	ALenum p_Format;
public:
    streaming_manager(const char* _path)
        :snd()
    {
        alGenSources(1, &__Msource__);
        alGenBuffers(NUM_BUFFERS, p_Buffers);

        std::size_t frame_size;
        snd.open(_path, ios_base::in);

        bool ext_fmt = snd.command(isndstream::wavex_get_ambisonic) == isndstream::ambisonic_bformat
                    == isndstream::ambisonic_bformat ? true : false;

        switch (snd.info.channels)
        {
            case 1:
                p_Format = ios_base::mono_16;
                break;
            case 2:
                p_Format = ios_base::stereo_16;
                break;
            case 3:
                if (ext_fmt == true) p_Format = ios_base::bformat2d_16;
                break;
            case 4:
                if (ext_fmt == true) p_Format = ios_base::bformat3d_16;
                break;
        }
        if (!p_Format)
        {
            snd.close();
            MUSX_THROW("Unsoupported channel count from file.", streaming_manager);
        }

        frame_size = ((size_t)BUFFER_SAMPLES * (size_t)snd.info.channels) * sizeof(short);
        p_Membuf = static_cast<short*>(malloc(frame_size));

    }

    ~streaming_manager()
    {
        alDeleteSources(1, &__Msource__);
        if (snd.is_open())
            snd.close();
        free(p_Membuf);
        alDeleteBuffers(NUM_BUFFERS, p_Buffers);
    }

    void to_play()
    {
        ALsizei i;

        alGetError();
        alSourceRewind(__Msource__);
        alSourcei(__Msource__, AL_BUFFER, 0);

        for (i = 0; i < NUM_BUFFERS; i++)
        {
            sf_count_t slen = snd.read(p_Membuf, BUFFER_SAMPLES);


            slen *= snd.info.channels * (sf_count_t)sizeof(short);
            alBufferData(p_Buffers[i], p_Format, p_Membuf, (ALsizei)slen, snd.info.samplerate);
        }

        if (alGetError() != AL_NO_ERROR) MUSX_THROW("Error buffering for playback.", to_play);

        alSourceQueueBuffers(__Msource__, i, p_Buffers);
        alSourcePlay(__Msource__);

        if (alGetError() != AL_NO_ERROR)
            MUSX_THROW("Error setting playback.", to_play);

    }

    virtual basic_manager& __Mstreamout__() override
    {
        ALint processed, state;

        alGetError();

        alGetSourcei(__Msource__, AL_SOURCE_STATE, &state);
        alGetSourcei(__Msource__, AL_BUFFERS_PROCESSED, &processed);

        while (processed > 0)
        {
            ALuint bufid;
            sf_count_t slen;

            alSourceUnqueueBuffers(__Msource__, 1, &bufid);
            processed--;

            slen = snd.read(p_Membuf, BUFFER_SAMPLES);
            if (slen > 0)
            {
                slen *= snd.info.channels * (sf_count_t)sizeof(short);
                alBufferData(bufid, p_Format, p_Membuf, (ALsizei)slen, snd.info.samplerate);
                alSourceQueueBuffers(__Msource__, 1, &bufid);
            }
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW("Error buffering music data", __Mstreamout__);
            return *this;
        }

        if (state != AL_PLAYING && state != AL_PAUSED)
        {
            ALint queued;

            alGetSourcei(__Msource__, AL_BUFFERS_QUEUED, &queued);
            if (queued == 0)
                return *this;
            alSourcePlay(__Msource__);
        }
        return *this;
    }

    source_t get_source() { return __Msource__; }

    void set(const gain& _val)
    {
        float new_val = _val.volume;
        if (new_val < 0)
            new_val = 0;
        alSourcef(__Msource__, AL_GAIN, new_val);
    }

    void set(const looping& _loop)
    {
        alSourcei(__Msource__, AL_LOOPING, _loop);
    }
};
PROJECT_NAMESPACE_END
#endif //!_MUSX_STREAMING_M_HPP_