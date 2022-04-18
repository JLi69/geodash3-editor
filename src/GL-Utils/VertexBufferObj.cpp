#include "VertexBufferObj.h"
#ifndef INCLUDE_GLAD
#include <glad/glad.h>
#endif

void VertexBufferObj::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);	
}

void VertexBufferObj::Enable()
{
	glVertexAttribPointer(0, vertSize, GL_FLOAT, false, sizeof(float) * vertSize, (void*)0);
	glEnableVertexAttribArray(0);
}

void VertexBufferObj::Data(float *dat, int size, int vSize)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, size, dat, GL_STATIC_DRAW);
	this->vertSize = vSize;
}

unsigned int VertexBufferObj::GetId()
{
	return this->id;
}

VertexBufferObj::VertexBufferObj()
{
	glGenBuffers(1, &this->id);
}
