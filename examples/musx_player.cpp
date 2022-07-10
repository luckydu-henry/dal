//! project musx's example
//! example of musx::streaming_manager.
//! All rights serverd 2022/7/10.
//! Copyright (c) 2022.
//! License: BSL.
//! Version: 2.0.0
#include <musx/musx.hpp>
#include <iostream>
#include <chrono>
#include "helper.h"

//! Brand new example of the new version of musx.
int main(int argc, char* argv[])
{
	try
	{
		std::string path;
		std::cout << WHITE <<"Input file path: ";
		std::cin >> path;

		musx::oaudiostream as;
		musx::streaming_manager sm(path.c_str());

		sm.to_play();
		auto begin = std::chrono::high_resolution_clock::now();

		std::cout << GREEN << "Playing: " << path << std::endl;
		while (sm.playing == sm.state())
		{
			std::cout << CLL; //! Clear line.
			as << sm;
			auto end = std::chrono::high_resolution_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::seconds>( end - begin );

			std::cout << GREEN << "Played: " << time.count() << " sec." << std::flush;
		} //! while.
		std::cout << std::endl << RED << "Finished" << std::endl << NONE;
	} //! try
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << '\n';
	}
	return 1;
}