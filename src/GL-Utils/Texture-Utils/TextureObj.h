#define TEXTUREOBJ_INCLUDE
#ifndef INCLUDE_GLAD
#include <glad/glad.h>
#endif
#include <string>

class TextureObj
{
	unsigned int m_id;	
public:
	//Loads a texture into memory
	//If the file cannot be opened, the function will return false
	//If the file is successfully opened, the function will return true
	bool OpenTexture(std::string texPath);

	//Activate the texture
	void ActivateTexture(GLenum tex);

	//Returns the texture ID of the object
	unsigned int GetId();

	//Constructor (Default)
	TextureObj();

	//Constructor
	TextureObj(std::string texPath);
};
