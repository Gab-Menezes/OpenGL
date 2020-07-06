#include "TestStencilTesting.h"
#include "VertexBufferAttLayout.h"
#include <glad/glad.h>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestStencilTesting::TestStencilTesting() :
		m_Proj(glm::perspective(glm::radians(45.f), (float)WIDTH/HEIGHT, 0.1f, 100.f))
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

		m_Camera = std::make_unique<Camera>(false, glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), -90.f);
		
		m_ShaderBox = std::make_unique<ShaderProgram>("res/shaders/TestStencilTesting/Box.glsl");
		m_ShaderBox->Bind();
		m_ShaderBox->setUniformMat4f("u_Proj", m_Proj);

		m_ShaderOutline = std::make_unique<ShaderProgram>("res/shaders/TestStencilTesting/Outline.glsl");
		m_ShaderOutline->Bind();
		//m_ShaderBox->setUniformMat4f("u_Model", glm::scale(glm::mat4(1.f), glm::vec3(1.05f)));
		m_ShaderOutline->setUniformMat4f("u_Proj", m_Proj);

		m_VAOBox = std::make_unique<VertexArray>();
		m_VAOBox->Bind();
		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAOBox->AddAtt(*m_VBO, layout);

		m_VAOOutline = std::make_unique<VertexArray>();
		m_VAOOutline->Bind();
		m_VBO->Bind();
		VertexBufferAttLayout layout1;
		layout1.Push<float>(3);
		layout1.AddStride<float>(2);
		m_VAOOutline->AddAtt(*m_VBO, layout1);


		m_ShaderBox->Bind();
		m_Texture = std::make_unique<Texture>("res/textures/woodBox.png");
		m_Texture->Bind();
		m_ShaderBox->setUniform1i("u_Texture", 0);
	}

	TestStencilTesting::~TestStencilTesting()
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
	}

	void TestStencilTesting::OnUpdate(float deltaTime)
	{
		m_Camera->KeyboardMove(deltaTime);
		m_Camera->MouseMove();
	}

	void TestStencilTesting::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		for (int i = 0; i < 2; i++)
		{
			m_ModelBox = glm::translate(glm::mat4(1.f), m_BoxPos[i]);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			m_ShaderBox->Bind();
			m_ShaderBox->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
			m_ShaderBox->setUniformMat4f("u_Model", m_ModelBox);
			m_VAOBox->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glDisable(GL_DEPTH_TEST);
		for (int i = 0; i < 2; i++)
		{
			m_ModelOutline = glm::translate(glm::mat4(1.f), m_BoxPos[i]);
			m_ModelOutline = glm::scale(m_ModelOutline, glm::vec3(1.05f));
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			m_ShaderOutline->Bind();
			m_ShaderOutline->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
			m_ShaderOutline->setUniformMat4f("u_Model", m_ModelOutline);
			m_VAOOutline->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glStencilMask(0xFF);
		}
		glEnable(GL_DEPTH_TEST);
	}

	void TestStencilTesting::OnImGuiRender()
	{
	}
}