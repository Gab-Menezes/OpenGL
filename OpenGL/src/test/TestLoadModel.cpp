#include "TestLoadModel.h"
#include "VertexBufferAttLayout.h"
#include "Renderer.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestLoadModel::TestLoadModel() :
		m_Proj(glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f)),
		m_Amb(0.4f), m_Diff(0.8f), m_Spec(1.0f)
	{
		//Light
		float vertices[] =
		{
			//left
			-0.5f,-0.5f,-0.5f,//0
			-0.5f,-0.5f, 0.5f,//1
			-0.5f, 0.5f, 0.5f,//2
			-0.5f, 0.5f,-0.5f,//3

			 //bottom
			 0.5f,-0.5f,-0.5f,//4
			 0.5f, 0.5f,-0.5f,//5

			 //top
			 0.5f,-0.5f, 0.5f,//6
			 0.5f, 0.5f, 0.5f //7
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
		};
		
		m_Light.Color = glm::vec3(1.0f);
		m_Light.Pos = glm::vec3(0.0f, 1.5f, 1.0f);
		m_Light.AmbientStrength = glm::vec3(m_Amb);
		m_Light.DiffuseStrength = glm::vec3(m_Diff);
		m_Light.SpecularStrength = glm::vec3(m_Spec);
		m_Light.SetLightVecs();
		m_Light.Constante = 1.0f;
		m_Light.Linear = 0.09f;
		m_Light.Quadratic = 0.032f;

		glEnable(GL_DEPTH_TEST);

		//MODEL
		m_ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.75f, 0.0f));
		m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.2f));

		m_Camera = std::make_unique<Camera>(false, glm::vec3(0.f, 0.f, 3.0f), glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, 1.0f, .0f), -90.0f);

		m_ModelShader = std::make_unique<ShaderProgram>("res/shaders/TestLoadModel/TestLoadModel.glsl");
		m_ModelShader->Bind();
		m_ModelShader->setUniformMat4f("u_Model", m_ModelMatrix);
		m_ModelShader->setUniformMat4f("u_Proj", m_Proj);
		m_ModelShader->setUniformLight<LightPoint>("u_Light", m_Light);

		m_Model = std::make_unique<Model>("res/models/nanosuit/nanosuit.obj", "u_Map");

		//LIGHT
		m_LightMatrix = glm::translate(glm::mat4(1.0f), m_Light.Pos);
		m_LightMatrix = glm::scale(m_LightMatrix, glm::vec3(0.2f));

		m_LightShader = std::make_unique<ShaderProgram>("res/shaders/TestLoadModel/Light.glsl");
		m_LightShader->Bind();
		m_LightShader->setUniform3f("u_ColorLight", m_Light.Color);
		m_LightShader->setUniformMat4f("u_Proj", m_Proj);
		m_LightShader->setUniformMat4f("u_Model", m_LightMatrix);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();
		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		m_VAO->AddAtt(*m_VBO, layout);
		m_EBO = std::make_unique<IndexBuffer>(&indices, 36);
		m_EBO->Bind();
	}

	TestLoadModel::~TestLoadModel()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestLoadModel::OnUpdate(float deltaTime)
	{
		m_Camera->MouseMove();
		m_Camera->KeyboardMove(deltaTime);
	}

	void TestLoadModel::OnRender()
	{
		m_Proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		glClear(GL_DEPTH_BUFFER_BIT);

		m_ModelShader->Bind();
		m_ModelShader->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ModelShader->setUniformMat4f("u_Proj", m_Proj);
		m_ModelShader->setUniform3f("u_CamPos", m_Camera->GetCamPos());
		m_Model->Draw(*m_ModelShader);

		m_LightShader->Bind();
		m_LightShader->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_LightShader->setUniformMat4f("u_Proj", m_Proj);
		Renderer render;
		render.Draw(*m_LightShader, *m_VAO, *m_EBO);
	}

	void TestLoadModel::OnImGuiRender()
	{
		if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_Light.Color)))
		{
			m_Light.SetLightVecs();
			m_ModelShader->Bind();
			m_ModelShader->setUniformLight<LightPoint>("u_Light", m_Light);

			m_LightShader->Bind();
			m_LightShader->setUniform3f("u_ColorLight", m_Light.Color);
		}
		if (ImGui::DragFloat3("Light Pos", glm::value_ptr(m_Light.Pos), 0.1f))
		{
			m_ModelShader->Bind();
			m_ModelShader->setUniformLight<LightPoint>("u_Light", m_Light);

			m_LightMatrix = glm::translate(glm::mat4(1.0f), m_Light.Pos);
			m_LightMatrix = glm::scale(m_LightMatrix, glm::vec3(0.2f));
			m_LightShader->Bind();
			m_LightShader->setUniformMat4f("u_Model", m_LightMatrix);
		}
		if (ImGui::SliderFloat("Ambient Strength", &m_Amb, 0.0f, 1.0f))
		{
			m_Light.AmbientStrength = glm::vec3(m_Amb);
			m_Light.SetLightVecs();
			m_ModelShader->Bind();
			m_ModelShader->setUniformLight<LightPoint>("u_Light", m_Light);
		}
		if (ImGui::SliderFloat("Diffuse Strength", &m_Diff, 0.0f, 1.0f))
		{
			m_Light.DiffuseStrength = glm::vec3(m_Diff);
			m_Light.SetLightVecs();
			m_ModelShader->Bind();
			m_ModelShader->setUniformLight<LightPoint>("u_Light", m_Light);
		}
		if (ImGui::SliderFloat("Specular Strength", &m_Spec, 0.0f, 1.0f))
		{
			m_Light.SpecularStrength = glm::vec3(m_Spec);
			m_Light.SetLightVecs();
			m_ModelShader->Bind();
			m_ModelShader->setUniformLight<LightPoint>("u_Light", m_Light);
		}
	}
}