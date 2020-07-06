#include "Texture.h"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(const std::string& path, bool alpha, bool flip, const std::string& type) : m_Path(path), m_Type(type)
{
	stbi_set_flip_vertically_on_load(flip);
	m_TextureData = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (m_TextureData)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		if (alpha)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(m_TextureData);
	}
	else
	{
		std::cout << "Failed to load texture: " << m_Path << std::endl;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const
{
	return m_Width;
}

int Texture::GetHeight() const
{
	return m_Height;
}

std::string Texture::GetPath() const
{
	return m_Path;
}

std::string Texture::GetType() const
{
	return m_Type;
}
