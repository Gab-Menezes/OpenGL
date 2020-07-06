#include "Framebuffer.h"
#include <iostream>
#include <Glad/glad.h>

extern unsigned int WIDTH, HEIGHT;

Framebuffer::Framebuffer() : m_TextureSet(false), m_RenderbufferSet(false)
{
	glGenFramebuffers(1, &m_Framebuffer);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_Framebuffer);

	if (m_TextureSet)
	{
		glDeleteTextures(1, &m_Texture);
	}

	if (m_RenderbufferSet)
	{
		glDeleteRenderbuffers(1, &m_Renderbuffer);
	}
}

void Framebuffer::AddTexture()
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_TextureSet = true;
}

void Framebuffer::AddRenderbuffer()
{
	glGenRenderbuffers(1, &m_Renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	m_RenderbufferSet = true;
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Framebuffer::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Framebuffer::Clear(float r, float g, float b, float a)
{
	if (m_TextureSet)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	if (m_RenderbufferSet)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}

bool Framebuffer::CheckFramebuffer()
{
	return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}
