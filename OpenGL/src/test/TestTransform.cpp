#include "TestTransform.h"
#include "VertexBufferAttLayout.h"
#include "Renderer.h"

#include <imgui/imgui.h>

namespace test
{
	TestTransform::TestTransform() : m_TranfomMatrix(1.0f),
		m_X(0.0f), m_Y(0.0f),
		m_Angle(0.0f), 
		m_Scale(1.0f),
		m_Color{0.0f, 0.5f, 0.3f, 1.0f}
	{
		glm::mat4 vertices
		{
			-0.5f, -0.5f, 0.0f, 1.0f,//bottom left
			 0.5f, -0.5f, 0.0f, 1.0f,//bottom right
			 0.5f,  0.5f, 0.0f, 1.0f,//top right
			-0.5f,  0.5f, 0.0f, 1.0f //top left
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_ShaderProgram = std::make_unique<ShaderProgram>("res/shaders/TestTransform.glsl");
		m_ShaderProgram->Bind();
		m_ShaderProgram->setUniformMat4f("u_Transform", m_TranfomMatrix);
		m_ShaderProgram->setUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();

		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(4);
		m_VAO->AddAtt(*m_VBO, layout);

		m_EBO = std::make_unique<IndexBuffer>(&indices, 6);
		m_EBO->Bind();
	}

	TestTransform::~TestTransform()
	{
	}

	void TestTransform::OnRender()
	{
		Renderer render;
		render.Draw(*m_ShaderProgram, *m_VAO, *m_EBO);
	}

	void TestTransform::OnImGuiRender()
	{
		if (ImGui::ColorEdit4("Change Color", m_Color))
		{
			m_ShaderProgram->setUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		}

		if (ImGui::SliderFloat("Translate X", &m_X, -1.5f, 1.5f))
		{
			SetTranformMatrix();
		}

		if (ImGui::SliderFloat("Translate Y", &m_Y, -1.5f, 1.5f))
		{
			SetTranformMatrix();
		}

		if (ImGui::SliderAngle("Change Angle", &m_Angle))
		{
			SetTranformMatrix();
		}

		if (ImGui::SliderFloat("Change Scale", &m_Scale, 0.0f, 5.0f))
		{
			SetTranformMatrix();
		}
	}

	void TestTransform::SetTranformMatrix()
	{
		
		//Scale -> Rotate -> Translate
		m_TranfomMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_X, m_Y, 0.0f));
		m_TranfomMatrix = glm::rotate(m_TranfomMatrix, m_Angle, glm::vec3(0.0, 0.0, 1.0));
		m_TranfomMatrix = glm::scale(m_TranfomMatrix, glm::vec3(m_Scale, m_Scale, m_Scale));
		m_ShaderProgram->setUniformMat4f("u_Transform", m_TranfomMatrix);
	}
}