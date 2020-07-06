#include "TestCamera.h"
#include "VertexBufferAttLayout.h"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;
float m_FOV = 45.0f;

namespace test
{
	TestCamera::TestCamera() :
		m_Window(glfwGetCurrentContext()),
		m_View(1.0f),
		m_Proj(glm::perspective(glm::radians(m_FOV), (float)WIDTH / HEIGHT, 0.1f, 100.0f))
	{
		Pos = glm::vec3(.0f, .0f, 3.0f);
		
		//OPENGL
		glEnable(GL_DEPTH_TEST);

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

		m_ShaderProgram = std::make_unique<ShaderProgram>("res/shaders/TestCamera.glsl");
		m_ShaderProgram->Bind();
		m_ShaderProgram->setUniformMat4f("u_View", m_View);
		m_ShaderProgram->setUniformMat4f("u_Proj", m_Proj);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();

		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddAtt(*m_VBO, layout);

		m_Texture1 = std::make_unique<Texture>("res/textures/container.jpg");
		m_Texture2 = std::make_unique<Texture>("res/textures/awesomeface.png");

		m_Texture1->Bind(0);
		m_ShaderProgram->setUniform1i("u_Texture1", 0);

		m_Texture2->Bind(1);
		m_ShaderProgram->setUniform1i("u_Texture2", 1);

		//CAMERA TRANSFORMATION
		//m_Camera = std::make_unique<Camera>(false, glm::vec3(.0f, .0f, 3.0f), glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, 1.0f, .0f), -90.0f);
		m_Camera = std::make_unique<Camera>(false, glm::vec3(.0f, .0f, 3.0f), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.0f, .0f), -90.0f);
	}

	TestCamera::~TestCamera()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestCamera::OnUpdate(float deltaTime)
	{
		m_Camera->KeyboardMove(deltaTime);
		m_Camera->MouseMove();

		//Mouse scroll zoom
		glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xoff, double yoff) 
		{
			if (m_FOV >= 1.0f && m_FOV <= 45.0f)
				m_FOV -= (float)yoff;
			else if (m_FOV <= 1.0f)
				m_FOV = 1.0f;
			else if (m_FOV >= 45.0f)
				m_FOV = 45.0f;
		});
	}

	void TestCamera::OnRender()
	{
		SetView();
		SetProj();

		glClear(GL_DEPTH_BUFFER_BIT);//Z-Buffer

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePos[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			m_ShaderProgram->setUniformMat4f("u_Model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void TestCamera::OnImGuiRender()
	{
		if (ImGui::InputFloat3("Pos", &Pos[0]))
		{
			m_Camera->SetCamPos(Pos);
			m_View = m_Camera->GetViewMatrix();
			m_ShaderProgram->setUniformMat4f("u_View", m_View);
		}
	}

	void TestCamera::SetView()
	{
		m_View = m_Camera->GetViewMatrix();
		m_ShaderProgram->setUniformMat4f("u_View", m_View);
	}

	void TestCamera::SetProj()
	{
		m_Proj = glm::perspective(glm::radians(m_FOV), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		m_ShaderProgram->setUniformMat4f("u_Proj", m_Proj);
	}
}