#ifndef INCLUDE_VERTEXBUFFOBJ
#include "../VertexBufferObj.h"
#endif

//Texture coordinates inherite from the Vertex Buffer Object
class TextureCoords : public VertexBufferObj
{
public:
	//Changed glEnableVertexAttribArray(0) to be glEnableVertexAttribArray(1)
	void Enable() override;	
};
