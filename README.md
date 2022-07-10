# musx
## 介绍
musx 是一个免费开源音频播放库， 基于 OpenAL 和 libsndfile. 只需添加包含到项目中即可快速使用！
作者：Henry Du.
最后更新: 2022/7/10
联系方式:
(国内)13552325266@163.com
(国外)wotsukoroga94@gmail.com
## 更新
### MUSX v2.0.0 更新
重大更新 musx 的编程风格以及 API 都得到了大幅更新！
受到 boost 和标准库的启发，musx 的命名空间重新改为小写，
单一文件取消，现在是多个 hpp 文件。
musx 改用 conan 作为依赖管理，简化了构建流程。
---
#### 新的 API:
1. oaudiostream: 设备以及 playback 管理.
2. isndstream  : 音频文件读取（目前不支持 mpeg 格式）.
3. buffer_tool : 生成 buffer, 包含两个模式 copy 和 extract.
4. source_manager: 管理音频元.
5. streaming_manager: 管理音乐元.
---
#### 弃用
1. genAudioList 和 delAudioList, musx 现在更关注核心功能。
2. play 和 update_stream 函数，现在使用 oaudiostream::operator<< 来直接输出.

## 计划
1. MacOSX 支持。
2. 更多的 OpenAL 功能如 alEffects...
3. 音频录制以及文件写入支持。
4. mpeg 格式支持。

## 构建
如果不需要案例直接将 include 目录下的所有内容复制到自己的项目即可，
需要自行安装 openal-soft 和 libsndfile 两个依赖。
### 构建例子
直接运行 build.sh/build.bat 即可 (需要先安装 python3 conan 以及 cmake)
## 文档
examples 文件夹下的两个例子基本足够。
## 感谢
Musx 使用了 openal-soft 和 libsndfile; 同时，感谢 YouTube 上的免费课程：
- **OpenAL-soft     : https://github.com/kcat/openal-soft**
- **libsndfile      : https://github.com/libsndfile/libsndfile**
- **YouTube Tutorial: https://www.youtube.com/watch?v=fG2veGWNPJY&list=PLalVdRk2RC6r7-4zciZ3LKc96ikviw6BS**
## 许可
musx 改用 BSL 许可(boost-library-license)，取自开源，回馈开源, 向标准库致敬。

## Musx 为游戏而生，它的未来属于一个更强的游戏引擎...

