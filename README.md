# lib_musx
A single header audio library for games.
Add include, lib, dll and musx.cpp into your own project and starting to use!<br>


The little sample's code:

```C++

#include <musx.h>
#include <iostream>

int main(int argc,char* argv[])
{
   try
   {
       Musx::Engine* engine = Musx::Engine::init();
       if(argc < 1)
       {
           std::cout << "Please enter a filename" << std::endl;
           engine->destroy();
           std::exit(0);
       }
       Musx::MusicBuffer mb(argv[1]);
       
       mb.play();
       std::cout << "Playing: " << argv[1] << std::endl;
       
       while(mb.play_state() == Musx::States::PLAYING)
       {
           mb.update_stream();
       }
       
       std::cout << "Finished" << std::endl;
       engine->destroy();
       
       return 0;
   }
   catch(const char* _msg)
   {
       std::cerr << _msg << std::endl;
       std::exit(-1);
   }
}




```
