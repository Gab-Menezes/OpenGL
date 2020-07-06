#include "TestLightCasters.h"
#include "VertexBufferAttLayout.h"

#include <glm/gtc/matrix_transform.hpp>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestLightCasters::TestLightCasters() : 
		m_CasterIndex(CastersName::Directional), m_Casters{"Directional", "Point", "Spotlight"},
		m_Proj(glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.1f, 100.0f)),
		m_Inner(glm::radians(12.5f)), m_Outter(glm::radians(17.5f)), m_LightControl(false)
	{
		m_Map.DiffuseIndex = 0;
		m_Map.SpecularIndex = 1;
		m_Map.Shininess = 32.0f;

		m_LightDir.Color = glm::vec3(1.0f);
		m_LightDir.Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		m_LightDir.AmbientStrength = glm::vec3(0.2f);
		m_LightDir.DiffuseStrength = glm::vec3(0.5f);
		m_LightDir.SpecularStrength = glm::vec3(1.0f);
		m_LightDir.SetLightVecs();

		m_LightPoint.Pos = glm::vec3(1.2f, 1.0f, 2.0f);
		m_LightPoint.Color = glm::vec3(1.0f);
		m_LightPoint.AmbientStrength = glm::vec3(0.2f);
		m_LightPoint.DiffuseStrength = glm::vec3(0.5f);
		m_LightPoint.SpecularStrength = glm::vec3(1.0f);
		m_LightPoint.SetLightVecs();
		m_LightPoint.Constante = 1.0f;
		m_LightPoint.Linear = 0.09f;
		m_LightPoint.Quadratic = 0.032f;

		m_LightSpot.Pos = glm::vec3(0.0f, 0.0f, 2.0f);
		m_LightSpot.Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		m_LightSpot.Color = glm::vec3(1.0f);
		m_LightSpot.AmbientStrength = glm::vec3(0.1f);
		m_LightSpot.DiffuseStrength = glm::vec3(0.8f);
		m_LightSpot.SpecularStrength = glm::vec3(1.0f);
		m_LightSpot.SetLightVecs();
		m_LightSpot.Constante = 1.0f;
		m_LightSpot.Linear = 0.09f;
		m_LightSpot.Quadratic = 0.032f;
		m_LightSpot.InnerCutOff = cos(m_Inner);
		m_LightSpot.OutCutOff = cos(m_Outter);

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
		m_Camera = std::make_unique<Camera>(false, glm::vec3(0.f, 0.f, 3.0f), glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, 1.0f, .0f), -90.0f);

		m_ModelLight = glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, 1.0f, 2.0f));
		m_ModelLight = glm::scale(m_ModelLight, glm::vec3(0.2f));

		//Light Map
		m_Map.DiffMap = std::make_unique<Texture>("res/textures/woodBox.png");
		m_Map.SpecMap = std::make_unique<Texture>("res/textures/woodBox_Specular.png");

		//OpenGL
		//Shader
		m_ShaderObj = std::make_unique<ShaderProgram>("res/shaders/TestLightCasters/Directional.glsl");
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
		m_ShaderObj->setUniformMaterial<MaterialMap>("u_Map", m_Map);
		m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);

		m_ShaderLight = std::make_unique<ShaderProgram>("res/shaders/TestLightCasters/Light.glsl");
		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
		m_ShaderLight->setUniformMat4f("u_Proj", m_Proj);
		m_ShaderLight->setUniform3f("u_ColorLight", m_LightDir.Color);

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
		lightLayout.Push<float>(3);
		lightLayout.AddStride<float>(2);
		m_VAOLight->AddAtt(*m_VBO, lightLayout);
	}

	TestLightCasters::~TestLightCasters()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestLightCasters::OnUpdate(float deltaTime)
	{
		m_Camera->MouseMove();
		m_Camera->KeyboardMove(deltaTime);
	}

	void TestLightCasters::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);

		m_VAOObj->Bind();
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ShaderObj->setUniform3f("u_CamPos", m_Camera->GetCamPos());
		if (m_CasterIndex == CastersName::Spotlight && m_LightControl)
		{
			m_LightSpot.Pos = m_Camera->GetCamPos();
			m_LightSpot.Direction = m_Camera->GetCamFront();

			m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
		}
		for (int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;
			m_ModelObj = glm::translate(glm::mat4(1.0f), m_CubePos[i]);
			m_ModelObj = glm::rotate(m_ModelObj, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			m_ShaderObj->setUniformMat4f("u_Model", m_ModelObj);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//the light draw with the directional light gets awkard
		if ((m_CasterIndex == CastersName::Spotlight && !m_LightControl) || m_CasterIndex == CastersName::Point )
		{
			m_ShaderLight->Bind();
			m_ShaderLight->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
			m_VAOLight->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void TestLightCasters::OnImGuiRender()
	{
		if (ImGui::Combo("Caster type", &m_CasterIndex, m_Casters, IM_ARRAYSIZE(m_Casters)))
		{
			std::string path = "res/shaders/TestLightCasters/";
			std::string ext = ".glsl";
			switch (m_CasterIndex)
			{
			case CastersName::Directional:
				m_ShaderObj = std::make_unique<ShaderProgram>(path + "Directional" + ext);
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
				m_ShaderObj->setUniformMaterial<MaterialMap>("u_Map", m_Map);
				m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);
				break;

			case CastersName::Point:
				SetLightModel(m_LightPoint.Pos);

				m_ShaderObj = std::make_unique<ShaderProgram>(path + "Point" + ext);
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
				m_ShaderObj->setUniformMaterial<MaterialMap>("u_Map", m_Map);
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
				break;

			case CastersName::Spotlight:
				SetLightModel(m_LightSpot.Pos);
				
				m_ShaderObj = std::make_unique<ShaderProgram>(path + "Spotlight" + ext);
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
				m_ShaderObj->setUniformMaterial<MaterialMap>("u_Map", m_Map);
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
				break;
			}
		}
	
		switch (m_CasterIndex)
		{
		case CastersName::Directional:
			if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_LightDir.Color)))
			{
				m_LightDir.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniform3f("u_ColorLight", m_LightDir.Color);
			}
			if (ImGui::ColorEdit3("Light Ambiet Strength", glm::value_ptr(m_LightDir.AmbientStrength)))
			{
				m_LightDir.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);
			}
			if (ImGui::ColorEdit3("Light Diffuse Strength", glm::value_ptr(m_LightDir.DiffuseStrength)))
			{
				m_LightDir.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);
			}
			if (ImGui::ColorEdit3("Light Specular Strength", glm::value_ptr(m_LightDir.SpecularStrength)))
			{
				m_LightDir.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);
			}
			if (ImGui::DragFloat3("Light Direction", glm::value_ptr(m_LightDir.Direction), 0.1f))
			{
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightDirectional>("u_Light", m_LightDir);
			}
			break;

		case CastersName::Point:
			if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_LightPoint.Color)))
			{
				m_LightPoint.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniform3f("u_ColorLight", m_LightPoint.Color);
			}
			if (ImGui::ColorEdit3("Light Ambiet Strength", glm::value_ptr(m_LightPoint.AmbientStrength)))
			{
				m_LightPoint.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);
			}
			if (ImGui::ColorEdit3("Light Diffuse Strength", glm::value_ptr(m_LightPoint.DiffuseStrength)))
			{
				m_LightPoint.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);
			}
			if (ImGui::ColorEdit3("Light Specular Strength", glm::value_ptr(m_LightPoint.SpecularStrength)))
			{
				m_LightPoint.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);
			}
			if (ImGui::DragFloat3("Light Pos", glm::value_ptr(m_LightPoint.Pos), 0.1f))
			{
				SetLightModel(m_LightPoint.Pos);

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
			}
			if (ImGui::SliderFloat("Linear", &m_LightPoint.Linear, 0.0f, 1.0f))
			{
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);
			}
			if (ImGui::SliderFloat("Quadratic", &m_LightPoint.Quadratic, 0.0f, 1.0f))
			{
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightPoint>("u_Light", m_LightPoint);
			}
			break;

		case CastersName::Spotlight:
			if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_LightSpot.Color)))
			{
				m_LightSpot.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniform3f("u_ColorLight", m_LightSpot.Color);
			}
			if (ImGui::ColorEdit3("Light Ambiet Strength", glm::value_ptr(m_LightSpot.AmbientStrength)))
			{
				m_LightSpot.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			if (ImGui::ColorEdit3("Light Diffuse Strength", glm::value_ptr(m_LightSpot.DiffuseStrength)))
			{
				m_LightSpot.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			if (ImGui::ColorEdit3("Light Specular Strength", glm::value_ptr(m_LightSpot.SpecularStrength)))
			{
				m_LightSpot.SetLightVecs();

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			if (ImGui::SliderFloat("Light Linear", &m_LightSpot.Linear, 0.0f, 1.0f))
			{
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			if (ImGui::SliderFloat("Light Quadratic", &m_LightSpot.Quadratic, 0.0f, 1.0f))
			{
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			ImGui::Checkbox("Light Control", &m_LightControl);
			if (ImGui::DragFloat3("Light Pos", glm::value_ptr(m_LightSpot.Pos), 0.1f))
			{
				SetLightModel(m_LightSpot.Pos);

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
			}
			if (ImGui::SliderFloat3("Light Direction", glm::value_ptr(m_LightSpot.Direction), -1.0f, 1.0f))
			{
				SetLightModel(m_LightSpot.Pos);

				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);

				m_ShaderLight->Bind();
				m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
			}
			if (ImGui::SliderAngle("Light Inner Angle", &m_Inner, 0.0f, 90.0f))
			{
				m_LightSpot.InnerCutOff = cos(m_Inner);
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			if (ImGui::SliderAngle("Light Outter Angle", &m_Outter, 0.0f, 90.0f))
			{
				m_LightSpot.OutCutOff = cos(m_Outter);
				m_ShaderObj->Bind();
				m_ShaderObj->setUniformLight<LightSpotlight>("u_Light", m_LightSpot);
			}
			break;
		}
	}

	void TestLightCasters::SetLightModel(const glm::vec3 & pos)
	{
		m_ModelLight = glm::translate(glm::mat4(1.0f), pos);
		m_ModelLight = glm::scale(m_ModelLight, glm::vec3(0.2f));
	}
}
