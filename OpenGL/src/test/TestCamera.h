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
	class TestCamera : public Test
	{
	public:
		TestCamera();
		~TestCamera();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void SetView();
		void SetProj();

	private:
		GLFWwindow* m_Window;
		
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;

		std::unique_ptr<Camera> m_Camera;

		glm::vec3 cubePos[10] = 
		{
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		//View Matrix
		glm::mat4 m_View;

		glm::vec3 Pos;


		//Projection Matrix
		glm::mat4 m_Proj;
	};
}