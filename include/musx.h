//! Brief:
//! ------------------------------------------------------------------
//! Musx is a free open-source C++ audio library based on OpenAL.
//! You can play audio easily just in less than 10 lines of codes.
//! It contains two parts: engine and FXs.
//! engine part is the devices and contexts manager.
//! Its mission is to create and delete a OpenAL context easily.
//! FX part can actual play the sound fxs/
//! It has "sound" and "music"(for now, I'll extend it in the future).
//! ------------------------------------------------------------------
//! Purpose:
//! ------------------------------------------------------------------
//! Why would I make this library? simply because the other library I can
//! found are too weak or not for free or not open-source. So I made this
//! one and it's completly free and open-source.
//! ------------------------------------------------------------------
//! Thanks:
//! ------------------------------------------------------------------
//! 3rd-parties:
//! 
//! OpenAL-soft: https://github.com/kcat/openal-soft
//! libsndfile:  https://github.com/libsndfile/libsndfile
//! 
//! I can not make this library without them.
//! 
//! Also thanks to some useful tutorials, they gave me the ability to do it:
//! 1. https://www.youtube.com/watch?v=fG2veGWNPJY&list=PLalVdRk2RC6r7-4zciZ3LKc96ikviw6BS
//! 2. https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
//! ------------------------------------------------------------------
//! I got this from open-source so I will return it under the LGPL license
//! Copyright (C) 2022/4/30 Henry Du <mailto:wotsukoroga94@gmail.com>
//! ------------------------------------------------------------------


#ifndef _LIB_MUSX_
#define _LIB_MUSX_

#define AL_ALEXT_PROTOTYPES

#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>
#include <AL/efx-creative.h>
#include <AL/efx-presets.h>
#include <sndfile.h>

#include <string>
#include <vector>


namespace Musx
{
	/// <summary>
	/// The vector3 type.
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	template <typename _T> struct MuVec3
	{
		_T x, y, z;
	};


	using MuVec3f = MuVec3<float>;
	using MuVec3i = MuVec3<int>;

	class Engine
	{
	public:

		//! Begin:-------------------------- [Enviroment functions] --------------------------
		//! ----------------------------------------------------------------------------------
		/// <summary>
		/// The initialize function of Musx::Engine.
		/// </summary>
		/// <param name="_DeviceName">The name of audio device, you can use "get_avalible_devices"
		/// function to get proper names (default to nullptr).
		/// </param>
		/// <param name="_AttrList">This one doesn't seem to be neccesarry.</param>
		/// <returns>Returns a pointer to the engine, which you can use methods.</returns>
		static Engine* init(const char* _DeviceName = nullptr, const int* _AttrList = nullptr);
		/// <summary>
		/// This method can destroy engine, asign devices and contexts to nullptr.
		/// </summary>
		void destroy();
		/// <summary>
		/// This can get engine's state, which include "running" and "closing".
		/// </summary>
		/// <returns>Returns engine state.</returns>
		int state();
		//! End:-------------------------- [Enviroment functions] ----------------------------
		//! ----------------------------------------------------------------------------------


		//! Begin:-------------------------- [Enviroment methods] ----------------------------
		//! ----------------------------------------------------------------------------------
		/// <summary>
		/// Get all available devices you can use in the "init()" function.
		/// </summary>
		/// <param name="_devicesVec">Pass in a std::vector to get the list of devices.</param>
		void get_available_devices(std::vector<std::string>& _devicesVec);
		/// <summary>
		/// Get all supported extentions.
		/// </summary>
		/// <param name="_str">Pass in a std::string to get the list of extentions.</param>
		void get_extention_list(std::string& _str);
		/// <summary>
		/// Get all devices specifier.
		/// </summary>
		/// <param name="_str">Pass in a std::string to get the devices specifier.</param>
		void get_all_devices_specifier(std::string& _str);
		//! End:-------------------------- [Enviroment methods] ------------------------------
		//! ----------------------------------------------------------------------------------



		//! Begin:-------------------------- [OpenAL get methods] ----------------------------
		//! ----------------------------------------------------------------------------------
		/// <summary>
		/// Get the listener location.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void get_location(float& x, float& y, float& z);
		/// <summary>
		/// Get the listener location.
		/// </summary>
		/// <param name="_location"></param>
		void get_location(MuVec3f& _location);
		/// <summary>
		/// Get the listener orientation.(方向)
		/// </summary>
		/// <param name="ori"></param>
		void get_orientation(float& ori);
		/// <summary>
		/// Get gain.
		/// </summary>
		/// <param name="ori"></param>
		void get_gain(float& ori);
		//! End:-------------------------- [OpenAL get methods] ------------------------------
		//! ----------------------------------------------------------------------------------

		//! Begin:-------------------------- [OpenAL set methods] ----------------------------
		//! ----------------------------------------------------------------------------------
		/// <summary>
		/// Sets the Attunation Model.(衰减)
		/// </summary>
		/// <param name="key">
		///#define AL_INVERSE_DISTANCE                      0xD001
		///#define AL_INVERSE_DISTANCE_CLAMPED              0xD002
		///#define AL_LINEAR_DISTANCE                       0xD003
		///#define AL_LINEAR_DISTANCE_CLAMPED               0xD004
		///#define AL_EXPONENT_DISTANCE                     0xD005
		///#define AL_EXPONENT_DISTANCE_CLAMPED             0xD006
		/// </param>
		void set_attunation(int key);
		/// <summary>
		/// Set the listener location.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void set_location(const float& x, const float& y, const float& z);
		/// <summary>
		/// Set the listener location.
		/// </summary>
		/// <param name="_location"></param>
		void set_location(const MuVec3f _location);
		/// <summary>
		/// Sets the orientation(方向) of listener using 'look at' (or foward vector) and 'up' direction
		/// </summary>
		/// <param name="atx"></param>
		/// <param name="aty"></param>
		/// <param name="atz"></param>
		/// <param name="upx"></param>
		/// <param name="upy"></param>
		/// <param name="upz"></param>
		void set_orientaion(const float& atx, const float& aty, const float& atz,
			const float& upx, const float& upz, const float& upy);
		/// <summary>
		/// Sets the orientation of listener using 'look at' (or foward vector) and 'up' direction
		/// </summary>
		/// <param name="_at"></param>
		/// <param name="_up"></param>
		void set_orientaion(const MuVec3f _at, const MuVec3f _up);
		/// <summary>
		/// Sets the master volume of our listeners. capped between 0 and 5 for now.
		/// </summary>
		/// <param name="_val"></param>
		void set_gain(const float& _val);
		//! End:-------------------------- [OpenAL set methods] ------------------------------
		//! ----------------------------------------------------------------------------------

	public:
		/// <summary>
		/// bind with enine->state(), engine is running.
		/// </summary>
		const static int running = true;
		/// <summary>
		/// bind with enine->state(), engine is closed.
		/// </summary>
		const static int closing = false;
	private:

		/// <summary>
		/// Singleton constructor.
		/// </summary>
		/// <param name="_DeviceName"></param>
		/// <param name="_AtrrList"></param>
		Engine(const char* _DeviceName = nullptr, const int* _AtrrList = nullptr);
		~Engine() = delete;

		const ALCchar* p_deviceName;
		const ALCint* p_attrList;

		ALCdevice* p_device;
		ALCcontext* p_context;

	};
	/// <summary>
	/// Judge the play_state with this class.
	/// </summary>
	enum class States
	{
		PLAYING = AL_PLAYING,
		PAUSED = AL_PAUSED,
		STOPPED = AL_STOPPED
	};


	using Buffer_t = ALuint;
	using Source_t = ALuint;
	using Audio_t = ALuint;

	/// <summary>
	/// This is a singleton class so you must use the get() function.
	/// </summary>
	class SoundBuffer
	{
	public:
		/// <summary>
		/// The get() function of this singleton class.
		/// </summary>
		/// <returns>Returns the class ptr.</returns>
		static SoundBuffer* get();
		/// <summary>
		/// This function can load audio from file and push it in the buffer vector.
		/// </summary>
		/// <param name="_path">Your audio path</param>
		/// <returns>Returns the buffer</returns>
		Audio_t load_from_file(const char* _path);
		/// <summary>
		/// Unload buffer from vector.
		/// </summary>
		/// <param name="_bid">buffer</param>
		/// <returns>Returns state.</returns>
		bool unload(const Audio_t& _bid);
	private:
		SoundBuffer();
		~SoundBuffer();

		/// <summary>
		/// Bufffers vector.
		/// </summary>
		std::vector<Audio_t> m_SoundFXBuffers;
	};

	/// <summary>
	/// Music buffer, you can play background music with it.
	/// </summary>
	class MusicBuffer
	{
	public:
		/// <summary>
		/// Play the music.
		/// </summary>
		void play();
		/// <summary>
		/// Pause the music.
		/// </summary>
		void pause();
		/// <summary>
		/// Stop the music.
		/// </summary>
		void stop();
		/// <summary>
		/// Resume the music.
		/// </summary>
		void resume();

		/// <summary>
		/// Update stream, for more usage, see the documentation.
		/// </summary>
		void update_stream();
		/// <summary>
		/// Get the source.
		/// </summary>
		/// <returns>source</returns>
		Source_t get_source();

		/// <summary>
		/// Set the music's gain.
		/// </summary>
		/// <param name="_val"></param>
		void set_gain(const float& _val);
		/// <summary>
		/// Set the music's loop.
		/// </summary>
		/// <param name="_loop"></param>
		void set_loop(const bool& _loop);

		/// <summary>
		/// The play state.
		/// </summary>
		/// <returns>A states enum.</returns>
		States play_state();

		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="_path">file path</param>
		MusicBuffer(const char* _path);
		~MusicBuffer();

	private:

		ALuint p_Source;
		static const int BUFFER_SAMPLES = 8192;
		static const int NUM_BUFFERS = 4;
		ALuint p_Buffers[NUM_BUFFERS];
		SNDFILE* p_Sndfile;
		SF_INFO p_Sfinfo;
		short* p_Membuf;
		ALenum p_Format;

		MusicBuffer() = delete;
	};

	/// <summary>
	/// This class is used to play the audio.
	/// </summary>
	class SoundPlayer
	{
	public:
		SoundPlayer();
		~SoundPlayer();

		/// <summary>
		/// Play the audio
		/// </summary>
		/// <param name="_buf">Audio you want to play.</param>
		void play(Audio_t& _buf);
		/// <summary>
		/// Stop current audio.
		/// </summary>
		void stop();
		/// <summary>
		/// Pause the current audio.
		/// </summary>
		void pause();
		/// <summary>
		/// Resume the current audio.
		/// </summary>
		void resume();
		/// <summary>
		/// Push the buffer and ready to play.
		/// </summary>
		/// <param name="_buf">Audio want to push</param>
		void set_buffer_to_play(const Audio_t& _buf);

		/// <summary>
		/// Set pitch.
		/// </summary>
		/// <param name="_pitch"></param>
		void set_pitch(const float& _pitch = 0.f);
		/// <summary>
		/// Set gain.
		/// </summary>
		/// <param name="_gain"></param>
		void set_gain(const float& _gain = 0.f);
		/// <summary>
		/// Set position.
		/// </summary>
		/// <param name="px"></param>
		/// <param name="py"></param>
		/// <param name="pz"></param>
		void set_position(const float& px = 0.f, const float& py = 0.f, const float& pz = 0.f);
		/// <summary>
		/// Set velocity.
		/// </summary>
		/// <param name="vx"></param>
		/// <param name="vy"></param>
		/// <param name="vz"></param>
		void set_velocity(const float& vx = 0.f, const float& vy = 0.f, const float& vz = 0.f);
		/// <summary>
		/// Set looping.
		/// </summary>
		/// <param name="_loop"></param>
		void set_looping(const bool& _loop = false);

		/// <summary>
		/// Get play state.
		/// </summary>
		/// <returns></returns>
		States play_state();

	private:

		Source_t source;
		Buffer_t buffer = 0;
	};

} // !namespace Musx 

#endif // !_LIB_MUSX_

