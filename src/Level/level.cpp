#include "level.h"
#include <fstream>
#include <iostream>

Geodash3::Level Geodash3::LoadLevel(std::string levelFilePath)
{
	std::ifstream levelFile(levelFilePath); //Open the file that contains the level data

	Geodash3::Level loaded; //Level to be loaded

	//File failed to open
	if(!levelFile.is_open())
	{
		std::cout << "Failed to open file: " << levelFilePath << '\n';	
		return loaded; //Return empty level	
	}

	//Read the level file
	//levels are 4 wide, 80 long, and 12 high
	std::string line;
	int currentLine = 0;
	//Read the file
	while(std::getline(levelFile, line))
	{
		//Ignore empty lines
		if(line.size() == 0)
			continue;

		//Read the line
		for(int i = 0; i < line.size(); i++)
		{
			switch(line[i])
			{
			//Block
			case '#':
				loaded.blocks.push_back(Geodash3::Block(glm::vec3(glm::floor((float)currentLine / 12.0f) * 0.5f - 0.75f,
																  -1.75f + 0.5f * (float)(11 - currentLine % 12),
																  -(float)i * 0.5f - 32.0f)));
				break;
			//Spike
			case '^':
				loaded.spikes.push_back(Geodash3::Spike(glm::vec3(glm::floor((float)currentLine / 12.0f) * 0.5f - 0.75f,
														-1.75f + 0.5f * (float)(11 - currentLine % 12),
														-(float)i * 0.5f - 32.0f)));
				break;
			//Nothing
			default:
				break;
			}
		}

		currentLine++;
	}
	
	//Close the file
	levelFile.close();

	return loaded;
}
