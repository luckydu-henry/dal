#ifndef _MUSX_CONFIG_HPP_
#define _MUSX_CONFIG_HPP_

#define PROJECT_NAMESPACE_BEGIN namespace musx{
#define PROJECT_NAMESPACE_END  } 

//! This macro is to enable all OpenAL extention features.
#define AL_ALEXT_PROTOTYPES

#ifdef _WIN32
#pragma warning(disable: 4996)
#endif //! _WIN32


PROJECT_NAMESPACE_BEGIN
using buffer_t = unsigned int;
using source_t = unsigned int;

struct gain{ float volume; };
struct orientation{
    struct {float x, y, z;} at;
    struct {float x, y, z;} up;
};
struct location{ float x, y, z; };
struct position{ float x, y, z; };
struct velocity{ float x, y, z; };

enum looping {
    on = 0x0001, off = 0x0000
};
//! Attunation states.
enum attunation
{
    inverse_dist = 0xD001,
    inverse_dist_clamped = 0xD002,
    linear_dist = 0xD003,
    linear_dist_clamped = 0xD004,
    exponent_dist = 0xD005,
    exponent_dist_clamped = 0xD006
};
class ios_base
{
protected:
    typedef int openmode;
    typedef int context_attr;
    typedef int manager_state; 
    typedef int format;
    //! Format for inside use.
    static const format mono_16 = 0x1101;
    static const format stereo_16 = 0x1103;
    static const format bformat2d_16 = 0x20022;
    static const format bformat3d_16 = 0x20032;
public:
    //! Sndfile openmode.
    static const openmode in  = 0x0010;
    static const openmode out = 0x0020; 
    //! Context attributes.
    static const context_attr to_default = 0;
    static const context_attr frequency  = 0x1007;
    static const context_attr refresh    = 0x1008;
    static const context_attr sync       = 0x1009;
    static const context_attr mono_src   = 0x1010;
    static const context_attr stereo_src = 0x1011;
    //! Source state check.
	static const manager_state playing = 0x1012;
	static const manager_state paused  = 0x1013;
	static const manager_state stopped = 0x1014;
    virtual bool is_open() { return true; }
};
PROJECT_NAMESPACE_END
#endif //! _MUSX_CONFIG_HPP_