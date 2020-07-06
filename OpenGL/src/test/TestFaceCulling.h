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
	class TestFaceCulling : public Test
	{
	public:
		TestFaceCulling();
		~TestFaceCulling();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<ShaderProgram> m_Shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Model;
		Camera m_Camera;
		glm::mat4 m_Proj;
	};
}