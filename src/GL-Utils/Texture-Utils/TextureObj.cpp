#include "TextureObj.h"
#include <SOIL/SOIL.h>
#include <iostream>

bool TextureObj::OpenTexture(std::string texPath)
{
	//Load the opngl texture
	this->m_id = SOIL_load_OGL_texture(texPath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//Failed to open image file
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
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
