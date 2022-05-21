#include "Engine.h"

bool Geodash3::Engine::Read(std::string path)
{
	this->m_path = path; //Set the path to be the specified path
	bool success; //Whether or not the file loaded
	this->m_level = Geodash3::LoadLevel(this->m_path, success); //Load the level
	return success;
}

void Geodash3::Engine::Write()
{
	
}
