#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& path, bool alpha = false, bool flip = true, const std::string& type = "");
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const;
	int GetHeight() const;
	std::string GetPath() const;
	std::string GetType() const;
private:
	unsigned int m_TextureID;
	std::string m_Path;
	std::string m_Type;
	unsigned char* m_TextureData;
	int m_Width, m_Height, m_BPP;
};