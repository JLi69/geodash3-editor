#include "Engine.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

bool Geodash3::Engine::Read(std::string path)
{
	this->m_path = path; //Set the path to be the specified path
	bool success; //Whether or not the file loaded
	this->m_level = Geodash3::LoadLevel(this->m_path, success); //Load the level
	return success;
}

void Geodash3::Engine::Write()
{
	std::vector<std::pair<glm::vec3, char>> objects[48];

	for(auto block : this->m_level.blocks)
	{
		int tempX = (int)((block.position.x + 0.75f) / 0.5f),
			tempY = (int)((block.position.y + 1.75f) / 0.5f) * -1 + 11;
		objects[tempX * 12 + tempY].push_back({ block.position, '#' });
	}
	for(auto spike : this->m_level.spikes)
	{	
		int tempX = (int)((spike.position.x + 0.75f) / 0.5f),
			tempY = (int)((spike.position.y + 1.75f) / 0.5f) * -1 + 11;
		objects[tempX * 12 + tempY].push_back({ spike.position, '^' });
	}	

	//Sort the objects
	for(int i = 0; i < 48; i++)
	{
		std::sort(objects[i].begin(), objects[i].end(),
				[](std::pair<glm::vec3, char> a, std::pair<glm::vec3, char> b)
				{
					return a.first.z > b.first.z;
				});
	}

	//Open the save file
	std::ofstream saveFile(this->m_path, std::ios::trunc);

	if(!saveFile.is_open())
		std::cout << "Failed to open save file!\n";

	//Set the start of the level to be at z = 0
	float start = -9999.0f;
	for(int i = 0; i < 48; i++)
		for(auto obj : objects[i])
			start = std::max(obj.first.z, start);

	for(int i = 0; i < 48; i++)
		for(auto &obj : objects[i])
			obj.first.z -= start; 

	int currentZ = 0;

	//The lines that represent the file
	std::stringstream lines[48];

	for(int i = 0; i < 48; i++)
		lines[i] << '.';

	for(int i = 0; i < 48; i++)
	{
		for(auto obj : objects[i])
		{	
			int tempZ = (int)((-obj.first.z) / 0.5f) + 1;

			for(int j = 0; j < tempZ - currentZ - 1; j++)
				lines[i] << '.';
			lines[i] << obj.second;

			currentZ = tempZ;
		}
		currentZ = 0;
	}

	for(int i = 0; i < 48; i++)
	{
		saveFile << lines[i].str() << '\n';

		if(i % 12 == 11)
			saveFile << '\n';
	}

	saveFile.close(); //Close the save file
}
