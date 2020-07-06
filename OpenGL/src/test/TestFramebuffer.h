#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Framebuffer.h"

#include <memory>

namespace test
{
	class TestFramebuffer : public Test
	{
	public:
		TestFramebuffer();
		~TestFramebuffer() override;


		void OnRender() override;
		void OnImGuiRender() override;
	private:
		bool m_Sobel;

		std::unique_ptr<Framebuffer> m_FBGray, m_FBGaussianH, m_FBGaussianV, m_FBSobel;

		std::unique_ptr<ShaderProgram> m_ShaderText, m_ShaderFBGray, m_ShaderFBGaussian, m_ShaderFBSobel;
		std::unique_ptr<VertexArray> m_VAOText;
		std::unique_ptr<VertexBuffer> m_VBOText;
		std::unique_ptr<IndexBuffer> m_EBOText;
		std::unique_ptr<Texture> m_Texture;
	};
}
