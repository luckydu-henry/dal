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
        if (argc == 1)
        {
            std::cout << "用法: Musx <文件名>" << std::endl;
            engine.~unique_ptr();
            std::exit(0);
        }
        if (argc == 2)
        {
            std::string arg = argv[1];
            Musx::Audio_t audio;

            Musx::LoadAudios(&audio, &arg, 1);
            {

                Musx::SoundPlayer player;
                std::cout << "正在播放: " << arg << std::endl;
                player.play(audio);
            }

            Musx::DeleteAudios(&audio, 1);
        }

        return 0;

    }
    catch (const char* _msg)
    {
        std::cerr << _msg << '\n';
    }

}