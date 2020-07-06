#include "TestMVP.h"
#include "VertexBufferAttLayout.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

namespace test
{
	TestMVP::TestMVP() : 
		m_Model(1.0f), m_MTranslate{ 0.f, 0.f, 0.f }, m_MAngle(glm::radians(-55.0f)), m_Scale(1.0f),
		m_View(1.0f), m_VTranslate{ 0.f, 0.f, 3.0f }, m_VAngle(0.f),
		m_Proj(1.0f), m_FOV(glm::radians(45.0f))
	{
		glEnable(GL_DEPTH_TEST);

		/*float vertices[] =
		{
			//left
			-0.5f,-0.5f,-0.5f,	0.0f, 0.0f,//0
			-0.5f,-0.5f, 0.5f,	1.0f, 0.0f,//1
			-0.5f, 0.5f, 0.5f,	1.0f, 1.0f,//2
			-0.5f, 0.5f,-0.5f,	0.0f, 1.0f,//3

			 //bottom
			 0.5f,-0.5f,-0.5f,	0.0f, 0.0f,//4
			 0.5f, 0.5f,-0.5f,	1.0f, 0.0f,//5

			 //top
			 0.5f,-0.5f, 0.5f,	0.0f, 1.0f,//6
			 0.5f, 0.5f, 0.5f,	1.0f, 1.0f //7
		};


		unsigned int indices[] =
		{
			//left
			0, 1, 2,
			2, 3, 0,

			//right
			4, 5, 7,
			7, 6, 4,

			//top
			1, 6, 7,
			7, 2, 1,

			//bottom
			0, 4, 5,
			5, 3, 0,

			//front
			0, 4, 6,
			6, 1, 0,

			//back
			3, 5, 7,
			7, 2, 3
		};*/


		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		m_ShaderProgram = std::make_unique<ShaderProgram>("res/shaders/TestMVP.glsl");
		m_ShaderProgram->Bind();
		m_ShaderProgram->setUniformMat4f("u_Model", m_Model);
		m_ShaderProgram->setUniformMat4f("u_View", m_View);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();

		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddAtt(*m_VBO, layout);

		/*m_EBO = std::make_unique<IndexBuffer>(&indices, 36);
		m_EBO->Bind();*/

		m_Texture1 = std::make_unique<Texture>("res/textures/container.jpg");
		m_Texture2 = std::make_unique<Texture>("res/textures/awesomeface.png");

		m_Texture1->Bind(0);
		m_ShaderProgram->setUniform1i("u_Texture1", 0);
		
		m_Texture2->Bind(1);
		m_ShaderProgram->setUniform1i("u_Texture2", 1);
	}

	TestMVP::~TestMVP()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestMVP::OnRender()
	{
		SetModel();
		SetView();
		SetProj();

		glClear(GL_DEPTH_BUFFER_BIT);//Z-Buffer
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//Renderer render;
		//render.Draw(*m_ShaderProgram, *m_VAO, *m_EBO);
	}

	void TestMVP::OnImGuiRender()
	{
		//Model
		ImGui::SliderFloat3("Model Translate(X, Y, Z)", m_MTranslate, -5.0f, 5.0f);
		ImGui::SliderAngle("Model Angle", &m_MAngle);
		ImGui::SliderFloat("Model Scale", &m_Scale, 0.0f, 3.0f);

		//View
		ImGui::SliderFloat3("Camera Translate(X, Y, Z)", m_VTranslate, -5.0f, 5.0f);
		ImGui::SliderAngle("Camera Angle", &m_VAngle);

		//Proj
		ImGui::SliderAngle("Proj FOV", &m_FOV, 0.0f, 90.0f);
	}

	void TestMVP::SetModel()
	{
		m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_MTranslate[0], m_MTranslate[1], m_MTranslate[2]));
		m_Model = glm::rotate(m_Model, m_MAngle, glm::vec3(1.0f, 0.0f, 0.0f));
		m_Model = glm::scale(m_Model, glm::vec3(m_Scale, m_Scale, m_Scale));
		m_ShaderProgram->setUniformMat4f("u_Model", m_Model);
	}

	void TestMVP::SetView()
	{
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(-m_VTranslate[0], -m_VTranslate[1], -m_VTranslate[2]));
		m_View = glm::rotate(m_View, -m_VAngle, glm::vec3(1.0f, 0.0f, 0.0f));
		m_ShaderProgram->setUniformMat4f("u_View", m_View);
	}

	void TestMVP::SetProj()
	{
		m_Proj = glm::perspective(m_FOV, 800.0f / 800.0f, 0.1f, 100.0f);
		m_ShaderProgram->setUniformMat4f("u_Proj", m_Proj);
	}
}