#include "level.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>

Geodash3::Level Geodash3::LoadLevel(std::string levelFilePath, bool &success)
{
	std::ifstream levelFile(levelFilePath); //Open the file that contains the level data

	Geodash3::Level loaded; //Level to be loaded
	loaded.levelEnd = -32.0f;

	//File failed to open
	//If failed, try to open file in HOME/.config/geodash3
#ifndef WINDOWS	
	if(!levelFile.is_open())
	{	
		const char* home = getenv("HOME");
		std::stringstream newPath;
		newPath << home << "/.config/geodash3/" << levelFilePath;
		levelFile = std::ifstream(newPath.str());
	}
#endif
	if(!levelFile.is_open())
	{
		std::cout << "Failed to open file: " << levelFilePath << '\n';
		success = false;
		return loaded; //Return empty level	
	}

	//Read the level file
	//levels are 4 wide, 80 long, and 12 high
	std::string line;
	int currentLine = 0,
		end = 0;
	//Read the file
	while(std::getline(levelFile, line))
	{
		//Ignore empty lines
		if(line.size() == 0)
			continue;
		if((int)line[0] == 13)
			continue;

		end = line.size() > end ? line.size() : end;

		//Read the line	
		for(int i = 0; i < line.size(); i++)
		{
			switch(line[i])
			{
			//Block 1
			case '#':
				loaded.blocks.push_back(Geodash3::Block(glm::vec3(floorf((float)currentLine / 12.0f) * 0.5f - 0.75f,
																  -1.75f + 0.5f * (float)(11 - currentLine % 12),
																  -(float)i * 0.5f - 4.0f)));
				break;
			//Block 2
			case '$':
				loaded.blocks.push_back(Geodash3::Block(glm::vec3(floorf((float)currentLine / 12.0f) * 0.5f - 0.75f,
																  -1.75f + 0.5f * (float)(11 - currentLine % 12),
																  -(float)i * 0.5f - 4.0f)));
				loaded.blocks.at(loaded.blocks.size() - 1).blockType = 1;	
				break;
			//Block 3
			case '%':
				loaded.blocks.push_back(Geodash3::Block(glm::vec3(floorf((float)currentLine / 12.0f) * 0.5f - 0.75f,
																  -1.75f + 0.5f * (float)(11 - currentLine % 12),
																  -(float)i * 0.5f - 4.0f)));
				loaded.blocks.at(loaded.blocks.size() - 1).blockType = 2;		
				break;
			//Spike
			case '^':
				loaded.spikes.push_back(Geodash3::Spike(glm::vec3(floorf((float)currentLine / 12.0f) * 0.5f - 0.75f,
														-1.75f + 0.5f * (float)(11 - currentLine % 12),
														-(float)i * 0.5f - 4.0f)));	
				break;
			//Empty space
			case '.':	
				break;
			//Unkown char!
			default:
				std::cout << "[line:" << currentLine + 1 << "]" <<  " Unknown char: " << (int)line[i] << '\n'; 
				break;
			}
		}

		currentLine++;
	}

	loaded.levelEnd -= (float)end * 0.5f;
	
	//Close the file
	levelFile.close();

	success = true;
	return loaded;
}
