#ifndef _MUSX_DRIVER_HPP_
#define _MUSX_DRIVER_HPP_

#include "exception.hpp"
#include "basic_manager.hpp"
//#include "streaming_manager.hpp"
#include "ios.hpp"
#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>

PROJECT_NAMESPACE_BEGIN
class oaudiostream : public ios_base
	{
	public:
		oaudiostream(const char* _Name = nullptr, const context_attr _List = to_default)
        {
            __pDeviceName__ = _Name;
            __pAttrList__   = &_List;
            __pDevice__ = alcOpenDevice(__pDeviceName__);
            if (!__pDevice__) 
                MUSX_THROW("Faild to open device", oaudiostream);
            __pContext__ = alcCreateContext(__pDevice__, __pAttrList__);
            if (!__pContext__) 
                MUSX_THROW("Faild to create context", oaudiostream);
            if (!alcMakeContextCurrent(__pContext__)) 
                MUSX_THROW("Faild to make context", oaudiostream);

            std::string name;
            name.clear();

            if (alcIsExtensionPresent(__pDevice__, "ALC_ENUMERATE_ALL_EXT"))
                name = alcGetString(__pDevice__, ALC_ALL_DEVICES_SPECIFIER);
            if (!name.c_str() || alcGetError(__pDevice__) != AL_NO_ERROR)
                name = alcGetString(__pDevice__, ALC_DEVICE_SPECIFIER);

        }
		//! summary:
		//! This can get engine's state, which include "running" and "closing".
		//! returns:
        //! Returns engine state.
        virtual bool is_open() override
        {
            bool state = __pDevice__ == nullptr || __pContext__ == nullptr ? false : true;
            return state;
        }
		//! summary:
		//! Get all available devices you can use.
		//! param _devicesVec: 
        //! Pass in a std::vector to get the list of devices.
		void getAvailableDevices(std::vector<std::string>& _DevicesVec)
        {
            const ALCchar* devices = alcGetString(__pDevice__, ALC_DEVICE_SPECIFIER);
            if (!devices)
                MUSX_THROW("Faild to get device", getAvailableDevices);
            const char* ptr = devices;
            _DevicesVec.clear();
            do
            {
                _DevicesVec.push_back(std::string(ptr));
                ptr += _DevicesVec.back().size() + 1;
            } while (*(ptr + 1) != '\0');
            return;
        }
		/// summary:
		/// Get all supported extentions.
		/// param _str:
        //! Pass in a std::string to get the list of extentions.
		void getExtentionList(std::string& _Str)
        {
            _Str.clear();
            _Str = alcGetString(__pDevice__, ALC_EXTENSIONS);
            return;
	    }
		//! summary:
		//! Get all devices specifier.
		//! param _str: 
        //! Pass in a std::string to get the devices specifier.
		void getAllSpecifier(std::string& _Str)
        {
            _Str.clear();
            alcIsExtensionPresent(__pDevice__, "ALC_ENUMERATE_ALL_EXT");
            _Str = alcGetString(__pDevice__, ALC_ALL_DEVICES_SPECIFIER);
            return;
        }
		//! summary:
		//! Get the listener location.
		void get(location& _loc)
        {
            alGetListener3f(AL_POSITION, &_loc.x, &_loc.y, &_loc.z);
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_GET_ERR, getLocation);
        }
		//! summary:
		//! Get the listener orientation.
		void get(float& _Ori)
        {
            alGetListenerfv(AL_ORIENTATION, &_Ori);
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_GET_ERR, getOrientation);
        }
		//! summary: 
        //! Get gain.
		//! param ori:
        //! Pass a float value to get.
		void get(gain& _g)
        {
            alGetListenerf(AL_GAIN, &_g.volume);
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_GET_ERR, getGain);
        }
		//! summary:
		//! Sets the Attunation Model.
		oaudiostream& set(const attunation& _Key)
        {
            alDistanceModel(static_cast<int>(_Key));
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW("Calculate error!", setAttunation);
            return *this;
        }
		//! summary:
		//! Set the listener location.
		oaudiostream& set(const location& _loc)
        {
            alListener3f(AL_POSITION, _loc.x, _loc.y, _loc.z);
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_SET_ERR, setLocation);
            return *this;
        }
		//! summary:
		//! Sets the orientation, of listener using 'look at' (or foward vector) and 'up' direction
		oaudiostream& set(const orientation& _Ori)
        {
            float Ori[6] = {
                _Ori.at.x, _Ori.at.y, _Ori.at.z,
                _Ori.up.x, _Ori.up.y, _Ori.up.z
            };

            alListenerfv(AL_ORIENTATION, Ori);
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_SET_ERR, setOrientaion);
            return *this;
	    }
		//! summary:
		//! Sets the master volume of our listeners. capped between 0 and 5 for now.
		oaudiostream& set(const gain& _G)
        {
            float NewVol = _G.volume;
            if (NewVol < 0.0f) NewVol = 0.0f;
            else if (NewVol > 5.0f) NewVol = 5.0f;

            alListenerf(AL_GAIN, NewVol);
            if (alGetError() != AL_NO_ERROR)
                MUSX_THROW(MUSX_SET_ERR, setGain);
            return *this;
        }
        //! summary:
        //! The destructor of this oaudiostream class.
        ~oaudiostream()
        {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(__pContext__);
            __pContext__    = nullptr;
            if (!alcCloseDevice(__pDevice__)) std::exit(-1);
            __pDevice__     = nullptr;
            __pDeviceName__ = nullptr;
            __pAttrList__   = nullptr;
        }
        oaudiostream& operator<<(basic_manager& _man)
        {
            _man.__Mstreamout__();
            return *this;
        }

        oaudiostream& paly_back(buffer_t& _buf)
        {
            return *this;
        }
	private:
		const ALCchar* __pDeviceName__;
		const ALCint* __pAttrList__;
		ALCdevice* __pDevice__;
		ALCcontext* __pContext__;
};

PROJECT_NAMESPACE_END
#endif //! _MUSX_DRIVER_HPP_
