#ifndef _MUSX_BASIC_SSTREAM_HPP_
#define _MUSX_BASIC_SSTREAM_HPP_

#include "ios.hpp"
PROJECT_NAMESPACE_BEGIN
class basic_sndstream : public ios_base
{
protected:
    typedef int sfc;
    typedef int sf;
public:
    static const sfc wavex_get_ambisonic = 4609;
    static const sf  ambisonic_bformat   = 65;
};
PROJECT_NAMESPACE_END

#endif //! _MUSX_BASIC_SSTREAM_HPP_