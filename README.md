# Musx
## 介绍
Musx 是一个免费开源音频播放库，只有一个 .h 和 .cpp 文件； 基于 OpenAL 和 libsndfile.
## 更新
Musx v1.1 版本迎来了重大更新：
1. 更换的文件名 —— musx.h 更新到了 Musx.h 以更好的区分与标准库。
2. Linux支持 —— Musx 已经在 Ubuntu22.04LTS 版本上通过测试。
3. 更新的项目结构 —— 使用 CMake 作为项目管理器，兼具跨平台与灵活性。
4. 优化的性能 —— Musx::Engine 已经支持智能指针管理，同时 Engine::init 和 Engine::destroy 函数已经弃用。
5. 便捷的操作 —— 新的 Musx::LoadAudios 和 Musx::DeleteAudios 函数可以更加快捷的批量创建 Audio_t 对象，但你
仍然可以选择使用 Musx::SoundBuffer::get()->load_from_file 或 Musx::SoundBuffer::get()->unload 函数，虽然这不被建议。

## 计划
1. MacOSX 支持。
2. 跨平台库预支持。
3. 更多的 OpenAL 功能如 alEffects...

## 构建
你需要手动下载两个依赖库 openal-soft 和 libsndfile 来进行构建，如果是 Linux 平台，请确保安装 libasound2-dev 库。
Ubuntu 下可以使用 
```bash
sudo apt install libasound2-dev
```
来进行安装，因为 Musx 使用 ALSA。
同时，请确保你的 openal-soft 是静态库，可以使用 
```cmake
cmake -DLIBTYPE=STATIC 
```
来生成静态库。

## 文档
Musx 之前的文档是英文的，且存在一些问题，这并不利于项目的开发，所以现在，这个例子被更新并使用最新的 API 和全中文注释。
```C++
//! Musx example.
//! Last Update: 2022/5/14.
//! Author: Henry Du.

#include <Musx.h>
#include <iostream>
#include <memory>


int main(int argc, char* argv[])
{
    try
    {
        auto engine = std::make_unique<Musx::Engine>();
        if(argc == 1)
        {
            std::cout << "用法： Musx <文件名>" << std::endl;
            engine.~unique_ptr();
            std::exit(0);
        }
        if (argc == 2)
        {
            std::string arg = argv[1];
            Musx::Audio_t audio;
    
            Musx::LoadAudios(&audio,&arg,1);
            {

                Musx::SoundPlayer player;
                std::cout << "正在播放：" << arg << std::endl;
                player.play(audio);
            }
    
            Musx::DeleteAudios(&audio,1);
        }
        
        return 0;

    }
    catch(const char* _msg)
    {
        std::cerr << _msg << '\n';
    }
    
}
```
你也可以在 main.cpp 中找到它。

## 感谢
Musx 使用了 openal-soft 和 libsndfile; 同时，感谢 YouTube 上的免费课程：
- **OpenAL-soft     : https://github.com/kcat/openal-soft**
- **libsndfile      : https://github.com/libsndfile/libsndfile**
- **YouTube Tutorial: https://www.youtube.com/watch?v=fG2veGWNPJY&list=PLalVdRk2RC6r7-4zciZ3LKc96ikviw6BS**
## 许可
Musx 使用 LGPL 许可，取自开源，回馈开源。

## Musx 为游戏而生，它的未来属于一个更强的游戏引擎...

