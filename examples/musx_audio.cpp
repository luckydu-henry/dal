//! project musx's example
//! example of musx::source_manager.
//! All rights serverd 2022/7/10.
//! Copyright (c) 2022.
//! License: BSL.
//! Version: 2.0.0
#include <musx/musx.hpp>
#include <iostream>
#include "helper.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "Usage: musx_audio <filepath>" << std::endl;
        return 1;
    }

    else if (argc == 2)
    {
        try
        {
            musx::oaudiostream oas;
            musx::isndstream iss(argv[argc - 1]);
            if (!iss.is_open())
            {
                std::cerr << "File can't open." << std::endl;
                return -1;
            }
            auto audio = musx::buft->copy_from_stream(iss);
            musx::source_manager sm;
            sm.bind(audio);
            std::cout << GREEN << "Playing: " << argv[argc - 1] << std::endl;
            oas << sm; //! Playback.
            std::cout << RED << "Finished" << std::endl;
            iss.close();
        }
        catch (std::exception& e)
        {
            std::cerr << RED << e.what() << std::endl;
            return -1;
        }
    }
}