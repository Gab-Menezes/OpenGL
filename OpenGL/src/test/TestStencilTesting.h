#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <memory>

namespace test
{
	class TestStencilTesting : public Test
	{
	public:
		TestStencilTesting();
		~TestStencilTesting();


		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<ShaderProgram> m_ShaderBox;
		std::unique_ptr<ShaderProgram> m_ShaderOutline;

		std::unique_ptr<VertexArray> m_VAOBox;
		std::unique_ptr<VertexArray> m_VAOOutline;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_ModelBox, m_ModelOutline;
		glm::vec3 m_BoxPos[2] =
		{
			glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-1.f, 0.f, -1.f)
		};
		std::unique_ptr<Camera> m_Camera;
		glm::mat4 m_Proj;
	};
}