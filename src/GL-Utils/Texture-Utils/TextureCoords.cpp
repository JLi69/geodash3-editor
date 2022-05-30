#ifndef INCLUDE_GLAD
#include <glad/glad.h>
#endif
#include "TextureCoords.h"

void TextureCoords::Enable()
{
	this->Bind();
	glVertexAttribPointer(1, this->GetVertSize(), GL_FLOAT, false, sizeof(float) * this->GetVertSize(), (void*)0);
	glEnableVertexAttribArray(1);
}
