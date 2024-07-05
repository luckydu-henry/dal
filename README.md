# DAL is a C++20 digital audio library

<div align = center>
<img src = "logo.png" width = "40%" height = "40%">
</div>

## Work with modern C++
C++ has no raw audio module, so that's why I am tending to write this project.

If you are familiar with STL, you are going to love this library. The library contains a light weight **audio_view** container, which can view raw byte buffers in any sequence and any stride with least performance lost. I also provided a variety of algorithms and functions to generate or process audio signals: **fundamental_waves** implemented a high-efficient sin function with a good approximation, square-wave triangular-wave and sawtooth-wave are also implemented; 
**oscillator** provides algorithms to sample from contigious data.
**amplitude** and **frequency** allows you to do calculation under a clear unit system.
**filter** and **envelope** helps you to generate any kind of effects you want.

Above all are under a clear simple straight-forward C++ framework, I think you will definetely enjoy this kind of experience.

For more information **look through the source code and play with examples.**
## Build
This library is header-only so just simply copy all files under *include* folder to your own project then you are ready to rock.
## License
This library is licensed under  the *Boost Software License* like most "deep-C++" libraries do.
