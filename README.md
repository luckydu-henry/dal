# Musx
## 介绍
Musx 是一个免费开源音频播放库，只有一个 .h 和 .cpp 文件； 基于 OpenAL 和 libsndfile. 只需添加两个文件到项目中即可快速使用！
作者：Henry Du.
最后更新: 2022/5/22
联系方式:
(国内)13552325266@163.com
(国外)wotsukoroga94@gmail.com
## 更新
#### Musx v1.1.1 更新 2022/5/22:
1. 优化的构建和项目结构 —— 构建方法和目录结构变得更加简便，构建文档也更加的详细。
### Musx v1.1 更新:
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
**现在不再需要手动的构建依赖库了！**
**CMake 可以直接构建参考案例**
### 完整的构建流程
#### Windows
```pws
git clone https://github.com/luckydu-henry/lib_musx.git Musx
cd Musx
mkdir build
cd build
cmake ..
```
打开 VisualStudio 生成解决方案之后进入 bin 文件夹下复制 OpenAL32.dll 和 sndfile.dll 到 Release/Debug 目录下然后直接运行。
#### Linux
构建之前请确保已经安装 libasound2-dev 和 GNUMake. Ubuntu下指令如下
```bash
sudo apt install libasound2-dev
sudo apt install gcc
sudo apt install make
git clone https://github.com/luckydu-henry/lib_musx.git Musx
cd Musx
mkdir build
cd build
cmake ..
make
cd bin
./Musx
```
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

