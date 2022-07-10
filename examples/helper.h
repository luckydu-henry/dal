#ifndef _HELPER_
#define _HELPER_

//! Custom console out for linux.
#ifdef __unix__
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"
#define SHINE "\033[5m"      //闪烁
#define DASH "\033[9m"       // 中间一道横线
#define QUICKSHINE "\033[6m" //快闪
#define INVERSE "\033[7m"    //反显
#define HIDE "\033[8m"    // 消隐，消失隐藏
#define CLL  "\r\033[K" // 清行
#elif defined _WIN32
#define NONE         "" 
#define RED  ""
#define LIGHT_RED  ""
#define GREEN  ""
#define LIGHT_GREEN  ""
#define BLUE  ""
#define LIGHT_BLUE  ""
#define DARY_GRAY  ""
#define CYAN  ""
#define LIGHT_CYAN  ""
#define PURPLE  ""
#define LIGHT_PURPLE "" 
#define BROWN ""
#define YELLOW ""
#define LIGHT_GRAY ""
#define WHITE ""
#define SHINE ""
#define DASH ""
#define QUICKSHINE ""
#define INVERSE ""
#define HIDE  ""
#define CLL   ""
#endif

#endif //!_HELPER_