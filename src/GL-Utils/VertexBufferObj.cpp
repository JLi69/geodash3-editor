#include "VertexBufferObj.h"
#ifndef INCLUDE_GLAD
#include <glad/glad.h>
#endif

void VertexBufferObj::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_id);	
}

void VertexBufferObj::Enable()
{
	this->Bind();
	glVertexAttribPointer(0, m_vertSize, GL_FLOAT, false, sizeof(float) * m_vertSize, (void*)0);
	glEnableVertexAttribArray(0);
}

void VertexBufferObj::Data(const float *dat, int size, int vSize)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, size, dat, GL_STATIC_DRAW);
	this->m_vertSize = vSize;
}

unsigned int VertexBufferObj::GetId()
{
	return this->m_id;
}

void VertexBufferObj::GenBuffer()
{
	glGenBuffers(1, &this->m_id);
}
