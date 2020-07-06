#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include <memory>

namespace test
{
	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture() override;

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<Texture> m_Texture;


		std::vector<std::string> m_SItens;
		std::vector<const char*> m_CItens;
		std::vector<std::string> m_SringPaths;
		int m_CurrentTextureIndex;
	};
}