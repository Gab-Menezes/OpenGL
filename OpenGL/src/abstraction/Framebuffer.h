#pragma once


class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();

	void AddTexture();
	void AddRenderbuffer();

	void Bind();
	void Unbind();

	void BindTexture();
	void UnbindTexture();

	void Clear(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);

	bool CheckFramebuffer();

private:
	unsigned int m_Framebuffer, m_Texture, m_Renderbuffer;
	bool m_TextureSet, m_RenderbufferSet;
};