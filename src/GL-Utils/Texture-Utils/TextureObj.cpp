#include "TextureObj.h"
#include <SOIL/SOIL.h>
#include <iostream>
#include <cstdlib>
#include <sstream>

bool TextureObj::OpenTexture(std::string texPath)
{
	//Load the opngl texture
	this->m_id = SOIL_load_OGL_texture(texPath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//Failed to open image file	
#ifndef WINDOWS
	//Try looking in HOME/.config/geodash3-editor on linux
	if(this->m_id == 0)
	{
		const char* home = getenv("HOME");
		std::stringstream newPath;
		newPath << home << "/.config/geodash3-editor/" << texPath;
		this->m_id = SOIL_load_OGL_texture(newPath.str().c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}
	//If failed, try again in /etc/geodash3-editor
	if(this->m_id == 0)
	{
		std::stringstream newPath;
		newPath << "/etc/geodash3-editor/" << texPath;
		this->m_id = SOIL_load_OGL_texture(newPath.str().c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}
#endif
	//Output error message
	if(this->m_id == 0)
		std::cout << "Failed to open image file: " << texPath << '\n';
	//If the file can't be loaded, the id will be 0
	//Therefore, if the id is 0 then we should return false
	//Otherwise, we should return true
	return this->m_id != 0;
}

void TextureObj::ActivateTexture(GLenum tex)
{
	glActiveTexture(tex);
	glBindTexture(GL_TEXTURE_2D, this->m_id);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
}

unsigned int TextureObj::GetId()
{
	return this->m_id;	
}

TextureObj::TextureObj()
{
	this->m_id = 0;
}

TextureObj::TextureObj(std::string texPath)
{
	this->OpenTexture(texPath);
}
