#include "TestBlend.h"
#include "VertexBufferAttLayout.h"
#include "Renderer.h"
#include <map>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestBlend::TestBlend() : 
		m_Model(1.0f),
		m_Camera(false, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(0.0f, 1.0f, 0.0f), -90.0f),
		m_Proj(glm::perspective(45.0f, (float)WIDTH/HEIGHT, 0.1f, 100.0f))
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float verticesWindow[] =
		{
			//vertices				//texture
		   -0.5f, -0.5f, 0.0f,	 	0.0f, 0.0f, //lower left
			0.5f, -0.5f, 0.0f,		1.0f, 0.0f, //lowe right
			0.5f,  0.5f, 0.0f,		1.0f, 1.0f, //top right
		   -0.5f,  0.5f, 0.0f,		0.0f, 1.0f	//top left
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		float verticesBox[] =
		{
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


		m_Shader = std::make_unique<ShaderProgram>("res/shaders/TestBlend.glsl");

		m_TextureWindow = std::make_unique<Texture>("res/textures/window.png", true);
		m_TextureBox = std::make_unique<Texture>("res/textures/woodBox.png");

		//Window
		m_VAOWindow = std::make_unique<VertexArray>();
		m_VAOWindow->Bind();
		m_VBOWindow = std::make_unique<VertexBuffer>(&verticesWindow, sizeof(verticesWindow));
		m_VBOWindow->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAOWindow->AddAtt(*m_VBOWindow, layout);
		m_EBO = std::make_unique<IndexBuffer>(&indices, 6);
		m_EBO->Bind();

		//Box
		m_VAOBox = std::make_unique<VertexArray>();
		m_VAOBox->Bind();
		m_VBOBox = std::make_unique<VertexBuffer>(&verticesBox, sizeof(verticesBox));
		m_VBOBox->Bind();
		m_VAOBox->AddAtt(*m_VBOBox, layout);
	}

	TestBlend::~TestBlend()
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	void TestBlend::OnUpdate(float deltaTime)
	{
		m_Camera.MouseMove();
		m_Camera.KeyboardMove(deltaTime);
	}

	void TestBlend::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);

		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_View", m_Camera.GetViewMatrix());
		m_Shader->setUniformMat4f("u_Proj", m_Proj);

		//Box
		m_TextureBox->Bind();
		m_Shader->setUniform1i("u_Texture", 0);
		for (int i = 0; i < 2; i++)
		{
			m_Model = glm::translate(glm::mat4(1.0f), m_PosBox[i]);
			m_Shader->setUniformMat4f("u_Model", m_Model);

			m_VAOBox->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Window
		std::map<float, glm::vec3> sort;
		for (int i = 0; i < 5; i++)
		{
			float dist = glm::length(m_Camera.GetCamPos() - m_PosWindow[i]);
			sort[dist] = m_PosWindow[i];
		}
		m_TextureWindow->Bind();
		m_Shader->setUniform1i("u_Texture", 0);
		Renderer render;
		for (auto i = sort.rbegin(); i != sort.rend(); i++)
		{
			m_Model = glm::translate(glm::mat4(1.0f), i->second);
			m_Shader->setUniformMat4f("u_Model", m_Model);
			render.Draw(*m_Shader, *m_VAOWindow, *m_EBO);
		}
	}

	void TestBlend::OnImGuiRender()
	{
	}
}