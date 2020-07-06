#pragma once
#include <glad/glad.h>
#include <vector>

struct AttElements
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}

		return 0;
	}
};

class VertexBufferAttLayout
{
public:
	VertexBufferAttLayout() : m_Stride(0) {}
	
	//Push
	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += AttElements::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += AttElements::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += AttElements::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	//Add
	template<typename T>
	void AddStride(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void AddStride<float>(unsigned int count)
	{
		m_Stride += AttElements::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void AddStride<unsigned int>(unsigned int count)
	{
		m_Stride += AttElements::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void AddStride<unsigned char>(unsigned int count)
	{
		m_Stride += AttElements::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	//Getters
	inline const std::vector<AttElements> GetElements() const
	{
		return m_Elements;
	}

	inline unsigned int GetStride() const
	{
		return m_Stride;
	}

private:
	std::vector<AttElements> m_Elements;
	unsigned int m_Stride;
};