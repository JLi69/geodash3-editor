#include "OpenFile.h"
#include <cstdlib>
#include <sstream>
#include <iostream>

std::ifstream Geodash3::OpenFile(std::string path, bool &success)
{
	//Attempt to open the file in the directory the program was run in
	std::ifstream file(path);
	
	//Linux
#ifndef WINDOWS
	//If you can't find it, then try to look in HOME/.config
	if(!file.is_open())
	{
		std::stringstream newPath;
		//get user's home directory	
		const char* home = getenv("HOME");
		newPath << home << "/.geodash3/" << path;
		file = std::ifstream(newPath.str());
	}
	//If you still can't find it, then try to look in etc/geodash3
	if(!file.is_open())
	{
		std::stringstream newPath;
		newPath << "/usr/share/games/geodash3/" << path;
		file = std::ifstream(newPath.str());
	}
#endif

	//If you can't open it, output an error message:
	if(!file.is_open())
	{
		std::cout << "Failed to open file: " << path << '\n';
		success = false; //Failed to open file
	}
	else
		success = true; //Opened file
	
	return file;
}
