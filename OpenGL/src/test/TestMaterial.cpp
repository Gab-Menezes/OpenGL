#include "TestMaterial.h"

#include "VertexBufferAttLayout.h"

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestMaterial::TestMaterial() :
		//Obj
		m_ModelObj(1.0f), m_ScaleObj(1.0f), m_ObjPos(0.0f),
		//Light
		m_ScaleLight(0.2f), m_AutoColorChange(false),
		//Proj Matrix
		m_Proj(glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f))
	{
		m_Material.Ambient = glm::vec3(0.0f, 0.1f, 0.06f);
		m_Material.Diffuse = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
		m_Material.Specular = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
		m_Material.Shininess = 32.0f;
		
		m_Light.Pos = glm::vec3(1.2f, 1.0f, 2.0f);
		m_Light.Color = glm::vec3(1.0f);
		m_Light.AmbientStrength = glm::vec3(1.0f);
		m_Light.DiffuseStrength = glm::vec3(1.0f);
		m_Light.SpecularStrength = glm::vec3(1.0f);
		m_Light.SetLightVecs();

		//m_Light with strg 1.0f -> cyan plastic simulation
		glEnable(GL_DEPTH_TEST);

		//Data
		float vertices[] = {
			//vertex pos			 normal vector
			-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f
		};

		//Camera
		m_Camera = std::make_unique<Camera>(false, glm::vec3(-3.75f, 3.19f, 2.03f), glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, 1.0f, .0f), -19.0f, -34.5f);

		//OpenGL
		//Object
		m_ShaderObj = std::make_unique<ShaderProgram>("res/shaders/TestMaterial/Object.glsl");
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_Model", m_ModelObj);
		m_ShaderObj->setUniformMaterial<Material>("u_Material", m_Material);
		m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);

		//Light
		SetLightModel();
		m_ShaderLight = std::make_unique<ShaderProgram>("res/shaders/TestMaterial/Light.glsl");
		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
		m_ShaderLight->setUniform3f("u_ColorLight", m_Light.Color);

		//Object
		m_VAOObj = std::make_unique<VertexArray>();
		m_VAOObj->Bind();
		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layoutObj;
		layoutObj.Push<float>(3);
		layoutObj.Push<float>(3);
		m_VAOObj->AddAtt(*m_VBO, layoutObj);

		//Light Object
		m_VAOLight = std::make_unique<VertexArray>();
		m_VAOLight->Bind();
		m_VBO->Bind();
		VertexBufferAttLayout layoutLight;
		layoutLight.Push<float>(3);
		layoutLight.AddStride<float>(3);
		m_VAOLight->AddAtt(*m_VBO, layoutLight);
	}

	TestMaterial::~TestMaterial()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestMaterial::OnUpdate(float deltaTime)
	{
		m_Camera->MouseMove();
		m_Camera->KeyboardMove(deltaTime);
	}

	void TestMaterial::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		m_Proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);


		if (m_AutoColorChange)
		{
			float t = (float)glfwGetTime();
			m_Light.Color = glm::vec3(sin(t * 2.0f), sin(t * 0.7f), sin(t * 1.3f));
			m_Light.SetLightVecs();

			m_ShaderObj->Bind();
			m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);

			m_ShaderLight->Bind();
			m_ShaderLight->setUniform3f("u_ColorLight", m_Light.Color);
		}

		//OBJECT
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ShaderObj->setUniform3f("u_CamPos", m_Camera->GetCamPos());
		m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
		m_VAOObj->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//LIGHT
		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ShaderLight->setUniformMat4f("u_Proj", m_Proj);
		m_VAOLight->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void TestMaterial::OnImGuiRender()
	{
		//Object
		if (ImGui::ColorEdit3("Object Ambient", glm::value_ptr(m_Material.Ambient)))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniformMaterial<Material>("u_Material", m_Material);
		}
		if (ImGui::ColorEdit3("Object Diffuse", glm::value_ptr(m_Material.Diffuse)))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniformMaterial<Material>("u_Material", m_Material);
		}
		if (ImGui::ColorEdit3("Object Specular", glm::value_ptr(m_Material.Specular)))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniformMaterial<Material>("u_Material", m_Material);
		}
		if (ImGui::SliderFloat("Object Shininess", &m_Material.Shininess, 1.0f, 256.0f))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniformMaterial<Material>("u_Material", m_Material);
		}
		if (ImGui::DragFloat3("Move Object", glm::value_ptr(m_ObjPos), 0.1f))
		{
			SetObjModel();
			m_ShaderObj->Bind();
			m_ShaderObj->setUniformMat4f("u_Model", m_ModelObj);
		}

		ImGui::Spacing();
		ImGui::Spacing();

		//Light
		ImGui::Checkbox("Auto light change", &m_AutoColorChange);
		if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_Light.Color)))
		{
			m_Light.SetLightVecs();

			m_ShaderObj->Bind();
			m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);

			m_ShaderLight->Bind();
			m_ShaderLight->setUniform3f("u_ColorLight", m_Light.Color);
		}
		if (ImGui::ColorEdit3("Light Ambiet Strength", glm::value_ptr(m_Light.AmbientStrength)))
		{
			m_Light.SetLightVecs();

			m_ShaderObj->Bind();
			m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);
		}
		if (ImGui::ColorEdit3("Light Diffuse Strength", glm::value_ptr(m_Light.DiffuseStrength)))
		{
			m_Light.SetLightVecs();

			m_ShaderObj->Bind();
			m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);
		}
		if (ImGui::ColorEdit3("Light Specular Strength", glm::value_ptr(m_Light.SpecularStrength)))
		{
			m_Light.SetLightVecs();

			m_ShaderObj->Bind();
			m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);
		}
		if (ImGui::DragFloat3("Move Light", glm::value_ptr(m_Light.Pos), 0.1f))
		{
			SetLightModel();
			m_ShaderLight->Bind();
			m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);

			m_ShaderObj->Bind();
			m_ShaderObj->setUniformLight<Light>("u_Light", m_Light);
		}
	}

	//Matrix
	void TestMaterial::SetObjModel()
	{
		m_ModelObj = glm::translate(glm::mat4(1.0f), m_ObjPos);
		m_ModelObj = glm::scale(m_ModelObj, glm::vec3(m_ScaleObj));
	}

	void TestMaterial::SetLightModel()
	{
		m_ModelLight = glm::translate(glm::mat4(1.0f), m_Light.Pos);
		m_ModelLight = glm::scale(m_ModelLight, glm::vec3(m_ScaleLight));
	}
}