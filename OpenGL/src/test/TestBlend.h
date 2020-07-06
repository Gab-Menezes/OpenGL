#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include "Camera.h"

#include <memory>

namespace test
{
	class TestBlend : public Test
	{
	public:
		TestBlend();
		~TestBlend();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<ShaderProgram> m_Shader;
		std::unique_ptr<VertexArray> m_VAOWindow, m_VAOBox;
		std::unique_ptr<VertexBuffer> m_VBOWindow, m_VBOBox;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<Texture> m_TextureWindow, m_TextureBox;

		glm::vec3 m_PosWindow[5] =
		{
			glm::vec3(-1.5f,  0.0f, -0.48f),
			glm::vec3(1.5f,  0.0f,  0.51f),
			glm::vec3(0.0f,  0.0f,  0.7f),
			glm::vec3(-0.3f,  0.0f, -2.3f),
			glm::vec3(0.5f,  0.0f, -0.6f)
		};

		glm::vec3 m_PosBox[2] =
		{
			glm::vec3(2.0f,  0.0f, -1.0f),
			glm::vec3(-1.5f,  0.0f, -1.5f)
		};

		glm::mat4 m_Model;
		Camera m_Camera;
		glm::mat4 m_Proj;
	};
}