#pragma once
#include "VertexBuffer.h"
#include "VertexBufferAttLayout.h"
#include <glad/glad.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddAtt(const VertexBuffer& VBO, const VertexBufferAttLayout& layout);
private:
	unsigned int m_VAO;
};