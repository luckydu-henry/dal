//! ------------------------------------------------------------------
//! Musx is a free open-source C++ audio library based on OpenAL.
//! You can play audio easily just in less than 10 lines of codes.
//! It contains two parts: engine and FXs.
//! engine part is the devices and contexts manager.
//! Its mission is to create and delete a OpenhAL context easily.
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
//! conan:       https://github.com/conan-io/conan
//! I can not make this library without them.
//! 
//! Also thanks to some useful tutorials, they gave me the ability to do it:
//! 1. https://www.youtube.com/watch?v=fG2veGWNPJY&list=PLalVdRk2RC6r7-4zciZ3LKc96ikviw6BS
//! 2. https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
//! ------------------------------------------------------------------
//! I got this from open-source so I will return it under the BSL license
//! Copyright (C) 2022/7/10 Henry Du <mailto:wotsukoroga94@gmail.com>
//! ------------------------------------------------------------------
#ifndef _MUSX_ALL_IN_ONE_
#define _MUSX_ALL_IN_ONE_

#include "isndstream.hpp"
#include "oaudiostream.hpp"
#include "source_manager.hpp"
#include "streaming_manager.hpp"
#include "buffer_tool.hpp"

namespace musx{
    using ios = ios_base;
    using baudio = source_manager;
    using bmusic = streaming_manager;

    buffer_tool* buft = buffer_tool::get();
}

#endif //!_MUSX_ALL_IN_ONE_