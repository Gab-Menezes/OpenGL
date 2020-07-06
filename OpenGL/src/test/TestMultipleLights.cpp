#include "TestMultipleLights.h"
#include "VertexBufferAttLayout.h"

#include <string>
#include <glm/gtc/matrix_transform.hpp>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestMultipleLights::TestMultipleLights() :
		m_Proj(glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f))
	{
		m_Map.DiffuseIndex = 0;
		m_Map.SpecularIndex = 1;
		m_Map.Shininess = 32.0f;

		m_LightDir.Color = glm::vec3(1.0f);
		m_LightDir.Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		m_LightDir.AmbientStrength = glm::vec3(0.05f);
		m_LightDir.DiffuseStrength = glm::vec3(0.4f);
		m_LightDir.SpecularStrength = glm::vec3(0.5f);
		m_LightDir.SetLightVecs();

		m_LightPoint.Color = glm::vec3(1.0f);
		//m_LightPoint.Pos
		m_LightPoint.AmbientStrength = glm::vec3(0.05f);
		m_LightPoint.DiffuseStrength = glm::vec3(0.8f);
		m_LightPoint.SpecularStrength = glm::vec3(1.0f);
		m_LightPoint.SetLightVecs();
		m_LightPoint.Constante = 1.0f;
		m_LightPoint.Linear = 0.09f;
		m_LightPoint.Quadratic = 0.032f;
	
		//m_LightSpot.Pos
		//m_LightSpot.Direction
		m_LightSpot.Color = glm::vec3(1.0f);
		m_LightSpot.AmbientStrength = glm::vec3(0.f);
		m_LightSpot.DiffuseStrength = glm::vec3(1.f);
		m_LightSpot.SpecularStrength = glm::vec3(1.f);
		m_LightSpot.SetLightVecs();
		m_LightSpot.Constante = 1.0f;
		m_LightSpot.Linear = 0.09f;
		m_LightSpot.Quadratic = 0.032f;
		m_LightSpot.InnerCutOff = cos(glm::radians(12.5f));
		m_LightSpot.OutCutOff = cos(glm::radians(15.0f));

		
		glEnable(GL_DEPTH_TEST);
		//Data
		float vertices[] = {
			// positions			 // normals				// texture coords
			-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f
		};

		//Matrix
		m_Camera = std::make_unique<Camera>(false, glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(.0f, 1.0f, .0f), -90.0f);

		//Light Map
		m_Map.DiffMap = std::make_unique<Texture>("res/textures/woodBox.png");
		m_Map.SpecMap = std::make_unique<Texture>("res/textures/woodBox_Specular.png");

		//OpenGL
		//Shader
		m_ShaderObj = std::make_unique<ShaderProgram>("res/shaders/TestMultipleLights/Boxes.glsl");
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
		m_ShaderObj->setUniformMaterial<MaterialMap>("u_Map", m_Map);
		m_ShaderObj->setUniformLight<LightDirectional>("u_DirLight", m_LightDir);
		for (int i = 0; i < 4; i++)
		{
			m_LightPoint.Pos = m_PointLightPositions[i];
			std::string name = "u_PointLight[" + std::to_string(i) + "]";
			m_ShaderObj->setUniformLight<LightPoint>(name, m_LightPoint);
		}

		m_ShaderLight = std::make_unique<ShaderProgram>("res/shaders/TestMultipleLights/PointLight.glsl");
		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_Proj", m_Proj);
		m_ShaderLight->setUniform3f("u_ColorLight", m_LightPoint.Color);

		//Obj
		m_VAOObj = std::make_unique<VertexArray>();
		m_VAOObj->Bind();
		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout objLayout;
		objLayout.Push<float>(3);
		objLayout.Push<float>(3);
		objLayout.Push<float>(2);
		m_VAOObj->AddAtt(*m_VBO, objLayout);

		//Light
		m_VAOLight = std::make_unique<VertexArray>();
		m_VAOLight->Bind();
		m_VBO->Bind();
		VertexBufferAttLayout lightLayout;
		lightLayout.Push<float>(3);
		lightLayout.AddStride<float>(3);
		lightLayout.AddStride<float>(2);
		m_VAOLight->AddAtt(*m_VBO, lightLayout);
	}

	TestMultipleLights::~TestMultipleLights()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestMultipleLights::OnUpdate(float deltaTime)
	{
		m_Camera->MouseMove();
		m_Camera->KeyboardMove(deltaTime);
	}

	void TestMultipleLights::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);

		m_LightSpot.Pos = m_Camera->GetCamPos();
		m_LightSpot.Direction = m_Camera->GetCamFront();

		m_VAOObj->Bind();
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ShaderObj->setUniform3f("u_CamPos", m_Camera->GetCamPos());
		m_ShaderObj->setUniformLight<LightSpotlight>("u_SpotLight", m_LightSpot);
		for (int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;
			m_ModelObj = glm::translate(glm::mat4(1.0f), m_CubePos[i]);
			m_ModelObj = glm::rotate(m_ModelObj, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			m_ShaderObj->setUniformMat4f("u_Model", m_ModelObj);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		for (int i = 0; i < 4; i++)
		{
			m_ModelLight = glm::translate(glm::mat4(1.0f), m_PointLightPositions[i]);
			m_ModelLight = glm::scale(m_ModelLight, glm::vec3(0.2f)); // Make it a smaller cube
			m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void TestMultipleLights::OnImGuiRender()
	{
	}
}