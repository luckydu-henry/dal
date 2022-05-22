//! Define the "musx.h"
//! Version 1.0
//! Last update: 2022/4/30

#include <Musx.h>
#include <cinttypes>
#include <iostream>

#define SND_ERRMSG     "[Error @Musx::sndfile]: "
#define AL_ERRMSG      "[Error @Musx::OpenAL]: "
#define ALC_ERRMSG     "[Error @Musx::OpenAL Device]: "

#ifdef _WIN32
#define sprint sprintf_s
#define fprint fprintf_s
#define print printf_s
#elif defined __linux__
#define sprint std::sprintf
#define fprint std::fprintf
#define print  std::printf
#endif



namespace Musx
{
//! ------------------------- This part is the definition of "SoundBuffer" class --------------------------
//! -------------------------------------------------------------------------------------------------------
//! -------------------------------------------------------------------------------------------------------
//! -------------------------------------------------------------------------------------------------------
    static Audio_t LoadSoundFromFile(const char* _path)
    {

        //! Varible defines.
        ALenum err, format;
        Buffer_t buffer;
        SNDFILE* sndfile;
        SF_INFO sfinfo;
        short* membuf;
        sf_count_t num_frames;
        ALsizei num_bytes;
        char Err_Throw[256];


        //! Open the audio file and check if it's useable.
        sndfile = sf_open(_path, SFM_READ, &sfinfo);
        if (!sndfile)
        {
            sprint(Err_Throw, SND_ERRMSG "Could not open audio in %s\n", _path);
            throw Err_Throw;
        }
        if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT32_MAX / sizeof(short)) / sfinfo.channels)
        {
            sprint(Err_Throw, SND_ERRMSG "Bad sample count in %s (%" PRId64 ")\n", _path, sfinfo.frames);
            sf_close(sndfile);
            throw Err_Throw;
        }

        //! Get the sound format, and figure out the OpenAL format.
        format = AL_NONE;
        if (sfinfo.channels == 1)
            format = AL_FORMAT_MONO16;
        else if (sfinfo.channels == 2)
            format = AL_FORMAT_STEREO16;
        else if (sfinfo.channels == 3)
        {
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
                format = AL_FORMAT_BFORMAT2D_16;
        }
        else if (sfinfo.channels == 4)
        {
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
                format = AL_FORMAT_BFORMAT3D_16;
        }

        //! Decode the whole audio file to a buffer.
        membuf = (short*)malloc((size_t)(sfinfo.frames * sfinfo.channels) * (ALsizei)sizeof(short));
        num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
        if (num_frames < 1)
        {
            free(membuf);
            sf_close(sndfile);
            sprint(Err_Throw, SND_ERRMSG "Failed to read samples in %s (%" PRId64 ")\n", _path, num_frames);
            throw Err_Throw;
        }

        num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

        //! Buffer the audio data to a new buffer object. 
        //! Then free the data and close the file.

        buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

        free(membuf);
        sf_close(sndfile);

        //! Check AL error occured, and clean up if so.
        err = alGetError();
        if (err != AL_NO_ERROR)
        {
            sprint(Err_Throw, AL_ERRMSG "%s\n", alGetString(err));
            if (buffer && alIsBuffer(buffer))
                alDeleteBuffers(1, &buffer);
            throw Err_Throw;
        }

        return buffer;
    }

    SoundBuffer* SoundBuffer::get()
    {
        static SoundBuffer* sndbuf = new SoundBuffer();
        return sndbuf;
    }

    Buffer_t SoundBuffer::load_from_file(const char* _path)
    {
        Buffer_t buffer = 0;
        try
        {
            buffer = LoadSoundFromFile(_path);
        }
        catch (const char* _msg)
        {
            fprintf(stderr, "%s",_msg);
            std::exit(-1);
        }

        m_SoundFXBuffers.push_back(buffer);

        return buffer;
    }

    bool SoundBuffer::unload(const Audio_t& _bid)
    {
        auto it = m_SoundFXBuffers.begin();
        while (it != m_SoundFXBuffers.end())
        {
            if (*it == _bid)
            {
                alDeleteBuffers(1, &(*it));
                it = m_SoundFXBuffers.erase(it);
                return true;
            }
            else ++it;
        }
        return false;
    }
    SoundBuffer::SoundBuffer()
    {
        m_SoundFXBuffers.clear();
    }
    SoundBuffer::~SoundBuffer()
    {
        alDeleteBuffers((ALuint)m_SoundFXBuffers.size(), m_SoundFXBuffers.data());
        m_SoundFXBuffers.clear();
    }

    //! ----------------------- This part is the definition of "SoundPlayer" class ----------------------------
    //! -------------------------------------------------------------------------------------------------------
    //! -------------------------------------------------------------------------------------------------------
    //! -------------------------------------------------------------------------------------------------------

    SoundPlayer::SoundPlayer()
    {
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
    }
    SoundPlayer::~SoundPlayer()
    {
        alDeleteSources(1, &source);
    }
    void SoundPlayer::play(Audio_t& _buf)
    {
        if (_buf != buffer)
        {
            buffer = _buf;
            alSourcei(source, AL_BUFFER, (ALint)buffer);
        }

        alSourcePlay(source);

        ALenum state = AL_PLAYING;
        while (alGetError != AL_NO_ERROR && state == AL_PLAYING)
        {
            alGetSourcei(source, AL_SOURCE_STATE, &state);
        }
    }
    void SoundPlayer::stop()
    {
        alSourceStop(source);
        if (alGetError() != AL_NO_ERROR)
            throw "Error stopping playing!";
    }
    void SoundPlayer::pause()
    {
        alSourcePause(source);
        if (alGetError() != AL_NO_ERROR)
            throw "Error pausing playing!";
    }
    void SoundPlayer::resume()
    {
        alSourcePlay(source);
        if (alGetError() != AL_NO_ERROR)
            throw "Error resuming playing!";
    }
    void SoundPlayer::set_buffer_to_play(const Audio_t& _buf)
    {
        if (_buf != buffer)
        {
            buffer = _buf;
            alSourcei(source, AL_BUFFER, (ALint)buffer);

            if (alGetError() != AL_NO_ERROR)
                throw "Error set buffer to play!";
        }
    }
    void SoundPlayer::set_pitch(const float& _pitch)
    {
        alSourcef(source, AL_PITCH, (ALfloat)_pitch);
        if (alGetError() != AL_NO_ERROR)
            throw "Error setting pitch!";
    }
    void SoundPlayer::set_gain(const float& _gain)
    {
        alSourcef(source, AL_GAIN, (ALfloat)_gain);
        if (alGetError() != AL_NO_ERROR)
            throw "Error setting gain!";
    }
    void SoundPlayer::set_position(const float& px, const float& py, const float& pz)
    {
        alSource3f(source, AL_POSITION, (ALfloat)px, (ALfloat)py, (ALfloat)pz);
        if (alGetError() != AL_NO_ERROR)
            throw "Error setting position!";
    }
    void SoundPlayer::set_velocity(const float& vx, const float& vy, const float& vz)
    {
        alSource3f(source, AL_VELOCITY, (ALfloat)vx, (ALfloat)vy, (ALfloat)vz);
        if (alGetError() != AL_NO_ERROR)
            throw "Error setting velocity";
    }
    void SoundPlayer::set_looping(const bool& _loop)
    {
        alSourcei(source, AL_LOOPING, (ALint)_loop);
        if (alGetError() != AL_NO_ERROR)
            throw "Error setting loop";
    }
    States SoundPlayer::play_state()
    {
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        if (alGetError() != AL_NO_ERROR)
            throw "Error checking source";

        return state == AL_PLAYING ? States::PLAYING : States::PAUSED;
    }
    //! ----------------------- This part is the definition of "MusicBuffer" class ----------------------------
    //! -------------------------------------------------------------------------------------------------------
    //! -------------------------------------------------------------------------------------------------------
    //! -------------------------------------------------------------------------------------------------------

    MusicBuffer::MusicBuffer(const char* _path)
    {
        alGenSources(1, &p_Source);
        alGenBuffers(NUM_BUFFERS, p_Buffers);

        std::size_t frame_size;
        p_Sndfile = sf_open(_path, SFM_READ, &p_Sfinfo);
        if (!p_Sndfile) throw "Could not open music file, please check your path!\n";

        if (p_Sfinfo.channels == 1)
            p_Format = AL_FORMAT_MONO16;
        else if (p_Sfinfo.channels == 2)
            p_Format = AL_FORMAT_STEREO16;
        else if (p_Sfinfo.channels == 3)
        {
            if (sf_command(p_Sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
                p_Format = AL_FORMAT_BFORMAT2D_16;
        }
        else if (p_Sfinfo.channels == 4)
        {
            if (sf_command(p_Sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
                p_Format = AL_FORMAT_BFORMAT3D_16;
        }
        if (!p_Format)
        {
            sf_close(p_Sndfile);
            p_Sndfile = nullptr;
            throw("Unsupported channel count from file");
        }

        frame_size = ((size_t)BUFFER_SAMPLES * (size_t)p_Sfinfo.channels) * sizeof(short);
        p_Membuf = static_cast<short*>(malloc(frame_size));


    }

    MusicBuffer::~MusicBuffer()
    {
        alDeleteSources(1, &p_Source);
        if (p_Sndfile)
            sf_close(p_Sndfile);
        p_Sndfile = nullptr;
        free(p_Membuf);
        alDeleteBuffers(NUM_BUFFERS, p_Buffers);
    }

    void MusicBuffer::play()
    {
        ALsizei i;

        alGetError();
        alSourceRewind(p_Source);
        alSourcei(p_Source, AL_BUFFER, 0);

        for (i = 0; i < NUM_BUFFERS; i++)
        {
            sf_count_t slen = sf_readf_short(p_Sndfile, p_Membuf, BUFFER_SAMPLES);
            if (slen < 1)break;

            slen *= p_Sfinfo.channels * (sf_count_t)sizeof(short);
            alBufferData(p_Buffers[i], p_Format, p_Membuf, (ALsizei)slen, p_Sfinfo.samplerate);
        }

        if (alGetError() != AL_NO_ERROR) throw "Error buffering for playback\n";

        alSourceQueueBuffers(p_Source, i, p_Buffers);
        alSourcePlay(p_Source);

        if (alGetError() != AL_NO_ERROR)
        {
            throw "Error starting playback\n";
        }

    }

    void MusicBuffer::pause()
    {
        alSourcePause(p_Source);
        if (alGetError() != AL_NO_ERROR)
            throw "Error while pausing\n";
    }

    void MusicBuffer::stop()
    {
        alSourceStop(p_Source);
        if (alGetError() != AL_NO_ERROR)
            throw "Error while stoping\n";
    }

    void MusicBuffer::resume()
    {
        alSourcePlay(p_Source);
        if (alGetError() != AL_NO_ERROR)
            throw "Error while resuming\n";
    }

    void MusicBuffer::update_stream()
    {
        ALint processed, state;

        alGetError();

        alGetSourcei(p_Source, AL_SOURCE_STATE, &state);
        alGetSourcei(p_Source, AL_BUFFERS_PROCESSED, &processed);

        while (processed > 0)
        {
            ALuint bufid;
            sf_count_t slen;

            alSourceUnqueueBuffers(p_Source, 1, &bufid);
            processed--;

            slen = sf_readf_short(p_Sndfile, p_Membuf, BUFFER_SAMPLES);
            if (slen > 0)
            {
                slen *= p_Sfinfo.channels * (sf_count_t)sizeof(short);
                alBufferData(bufid, p_Format, p_Membuf, (ALsizei)slen, p_Sfinfo.samplerate);
                alSourceQueueBuffers(p_Source, 1, &bufid);
            }
            if (alGetError() != AL_NO_ERROR)
                throw "Error buffering music data\n";

        }

        if (state != AL_PLAYING && state != AL_PAUSED)
        {
            ALint queued;

            alGetSourcei(p_Source, AL_BUFFERS_QUEUED, &queued);
            if (queued == 0)
                return;
            alSourcePlay(p_Source);
        }

    }

    Source_t MusicBuffer::get_source()
    {
        return p_Source;
    }

    States MusicBuffer::play_state()
    {
        ALint state;
        alGetSourcei(p_Source, AL_SOURCE_STATE, &state);

        return state == AL_PLAYING ? States::PLAYING : States::PAUSED;
    }

    void MusicBuffer::set_gain(const float& _val)
    {
        float new_val = _val;
        if (new_val < 0)
            new_val = 0;
        alSourcef(p_Source, AL_GAIN, new_val);
    }

    void MusicBuffer::set_loop(const bool& _loop)
    {
        alSourcei(p_Source, AL_LOOPING, _loop);
    }

//!--------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------

	void Engine::get_available_devices(std::vector<std::string>& _devicesVec)
	{
		const ALCchar* devices = alcGetString(p_device, ALC_DEVICE_SPECIFIER);
		if (!devices) return;

		const char* ptr = devices;
		_devicesVec.clear();

		do
		{
			_devicesVec.push_back(std::string(ptr));
			ptr += _devicesVec.back().size() + 1;
		} while (*(ptr + 1) != '\0');

		return;
	}

	void Engine::get_extention_list(std::string& _str)
	{
		_str.clear();
		_str = alcGetString(p_device, ALC_EXTENSIONS);

		return;
	}

	void Engine::get_all_devices_specifier(std::string& _str)
	{
		_str.clear();

		alcIsExtensionPresent(p_device, "ALC_ENUMERATE_ALL_EXT");
		_str = alcGetString(p_device, ALC_ALL_DEVICES_SPECIFIER);

		return;
	}

	void Engine::get_location(float& x, float& y, float& z)
	{
		alGetListener3f(AL_POSITION, &x, &y, &z);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't get listener location";
	}

	void Engine::get_location(MuVec3f& _location)
	{
		auto x = _location.x;
		auto y = _location.y;
		auto z = _location.z;

		alGetListener3f(AL_POSITION, &x, &y, &z);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't get listener location";

	}

	void Engine::get_orientation(float& ori)
	{
		alGetListenerfv(AL_ORIENTATION, &ori);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't get listener orientation";
	}

	void Engine::get_gain(float& ori)
	{
		alGetListenerf(AL_GAIN, &ori);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't get listener gain";
	}

	void Engine::set_attunation(int key)
	{
		if (key < 0xD001 || key > 0xD006)
			throw "Bad attunation key";

		alDistanceModel(key);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't calculate distance";
	}

	void Engine::set_location(const float& x, const float& y, const float& z)
	{
		alListener3f(AL_POSITION, x, y, z);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't set listener position";
	}

	void Engine::set_location(const MuVec3f _location)
	{
		auto x = _location.x;
		auto y = _location.y;
		auto z = _location.z;

		alListener3f(AL_POSITION, x, y, z);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't set listener position";
	}

	void Engine::set_orientaion(const float& atx, const float& aty, const float& atz, const float& upx, const float& upz, const float& upy)
	{
		std::vector<float> ori;
		ori.push_back(atx);
		ori.push_back(aty);
		ori.push_back(atz);
		ori.push_back(upx);
		ori.push_back(upy);
		ori.push_back(upz);
		alListenerfv(AL_ORIENTATION, ori.data());

		if (alGetError() != AL_NO_ERROR)
			throw "Can't set orientation";

	}

	void Engine::set_orientaion(const MuVec3f _at, const MuVec3f _up)
	{

		std::vector<float> ori;
		ori.push_back(_at.x);
		ori.push_back(_at.y);
		ori.push_back(_at.z);
		ori.push_back(_up.x);
		ori.push_back(_up.y);
		ori.push_back(_up.z);
		alListenerfv(AL_ORIENTATION, ori.data());

		if (alGetError() != AL_NO_ERROR)
			throw "Can't set orientation";
	}

	void Engine::set_gain(const float& _val)
	{
		float newVol = _val;
		if (newVol < 0.0f)
			newVol = 0.0f;
		else if (newVol > 5.0f)
			newVol = 5.0f;
		alListenerf(AL_GAIN, newVol);
		if (alGetError() != AL_NO_ERROR)
			throw "Can't set gain";
	}

	int Engine::state()
	{
		return p_device == nullptr || p_context == nullptr ? false : true;
	}

	Engine::Engine(const char* _DeviceName, const int* _AtrrList)
		:p_deviceName(_DeviceName), p_attrList(_AtrrList)
	{
		p_device = alcOpenDevice(p_deviceName);
		if (!p_device) throw "Faild to open device\n";
		p_context = alcCreateContext(p_device, p_attrList);
		if (!p_context) throw "Faild to create context\n";

		if (!alcMakeContextCurrent(p_context)) throw "Faild to make context";

		std::string name;
		name.clear();

		if (alcIsExtensionPresent(p_device, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(p_device, ALC_ALL_DEVICES_SPECIFIER);
		if (!name.c_str() || alcGetError(p_device) != AL_NO_ERROR)
			name = alcGetString(p_device, ALC_DEVICE_SPECIFIER);

	}
    Engine::~Engine()
    {

		alcMakeContextCurrent(nullptr);
		alcDestroyContext(p_context);

		p_context = nullptr;

		if (!alcCloseDevice(p_device))std::exit(-1);

		p_device = nullptr;

		p_deviceName = nullptr;
		p_attrList = nullptr;
    }
    void LoadAudios(Audio_t* audios, Path_t* paths, size_t count)
    {
        if(count == 1)
        {
            *audios = SoundBuffer::get()->load_from_file(paths->c_str());
            return;
        }
        else
        {
            for (size_t i = 0; i < count; i++)
                audios[i] = SoundBuffer::get()->load_from_file(paths[i].c_str());
            return;
        }
    }
	void DeleteAudios(Audio_t* audios, size_t count)
    {
        if(count == 1)
        {
            SoundBuffer::get()->unload(*audios);
            return;
        }
        else
        {
            for (size_t i = 0; i < count; i++)
                SoundBuffer::get()->unload(audios[i]);
            return;
        }
    }
}