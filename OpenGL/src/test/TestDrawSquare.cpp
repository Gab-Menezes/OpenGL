#include "TestDrawSquare.h"
#include "VertexBufferAttLayout.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace test
{
	TestDrawSquare::TestDrawSquare()
	{
		float vertices[12] =
		{
			-0.5f, -0.5f, 0.0f,//bottom left
			 0.5f, -0.5f, 0.0f,//bottom right
			 0.5f,  0.5f, 0.0f,//top right
			-0.5f,  0.5f, 0.0f //top left
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};
		
		m_ShaderProgram = std::make_unique<ShaderProgram>("res/shaders/TestDrawSquare.glsl");
		m_ShaderProgram->Bind();

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();

		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		m_VAO->AddAtt(*m_VBO, layout);

		m_EBO = std::make_unique<IndexBuffer>(&indices, 6);
		m_EBO->Bind();
	}

	TestDrawSquare::~TestDrawSquare()
	{
	}

	void TestDrawSquare::OnRender()
	{
		m_ShaderProgram->setUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		glDrawElements(GL_TRIANGLES, m_EBO->GetCount(), GL_UNSIGNED_INT, 0);
	}
	void TestDrawSquare::OnImGuiRender()
	{
		ImGui::ColorEdit4("Square color", m_Color);
	}
}