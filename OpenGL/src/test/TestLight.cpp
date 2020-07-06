#include "TestLight.h"
#include "VertexBufferAttLayout.h"
//#include "Renderer.h"

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestLight::TestLight() :
		//Obj Model
		m_ModelObj(1.0f), m_ScaleObj(1.0f), m_ObjPos(0.0f, 0.0f, 0.0f),
		//Light Model
		m_ScaleLight(0.2f), m_LightPos(1.2f, 1.0f, 2.0f),
		//Proj Matrix
		m_Proj(glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f)),
		//Colors
		m_ColorObj(1.0f, 0.5f, 0.31f, 1.0f), m_ColorLight(1.0f, 1.0f, 1.0f, 1.0f),
		//Shader Variables
		m_AmbientStrength(0.1f), m_SpecularStrength(0.5f), m_SpecularShininess(32), m_SpecularShininessPow(5)
	{
		glEnable(GL_DEPTH_TEST);
		
		//Data
		/*float vertices[] =
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
		};*/

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
		m_ShaderObj = std::make_unique<ShaderProgram>("res/shaders/TestLight/Object.glsl");
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_Model", m_ModelObj);
		m_ShaderObj->setUniform4f("u_ColorObj", m_ColorObj);
		m_ShaderObj->setUniform4f("u_ColorLight", m_ColorLight);
		m_ShaderObj->setUniform3f("u_LightPos", m_LightPos);
		m_ShaderObj->setUniform1f("u_AmbientStrength", m_AmbientStrength);
		m_ShaderObj->setUniform1f("u_SpecularStrength", m_SpecularStrength);
		m_ShaderObj->setUniform1i("u_SpecularShininess", m_SpecularShininess);

		//Light
		SetLightModel();
		m_ShaderLight = std::make_unique<ShaderProgram>("res/shaders/TestLight/Light.glsl");
		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);
		m_ShaderLight->setUniform4f("u_ColorLight", m_ColorLight);

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

	TestLight::~TestLight()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestLight::OnUpdate(float deltaTime)
	{
		m_Camera->MouseMove();
		m_Camera->KeyboardMove(deltaTime);
	}

	void TestLight::OnRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		m_Proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);

		//OBJECT
		m_ShaderObj->Bind();
		m_ShaderObj->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ShaderObj->setUniformMat4f("u_Proj", m_Proj);
		m_ShaderObj->setUniform3f("u_CamPos", m_Camera->GetCamPos());
		m_VAOObj->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//LIGHT
		m_ShaderLight->Bind();
		m_ShaderLight->setUniformMat4f("u_View", m_Camera->GetViewMatrix());
		m_ShaderLight->setUniformMat4f("u_Proj", m_Proj);
		m_VAOLight->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void TestLight::OnImGuiRender()
	{
		if (ImGui::ColorEdit4("Object Color", glm::value_ptr(m_ColorObj)))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniform4f("u_ColorObj", m_ColorObj);
		}
		if (ImGui::ColorEdit4("Light Color", glm::value_ptr(m_ColorLight)))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniform4f("u_ColorLight", m_ColorLight);

			m_ShaderLight->Bind();
			m_ShaderLight->setUniform4f("u_ColorLight", m_ColorLight);
		}
		ImGui::Spacing();
		if (ImGui::DragFloat3("Move Object", glm::value_ptr(m_ObjPos), 0.1f))
		{
			SetObjModel();
			m_ShaderObj->Bind();
			m_ShaderObj->setUniformMat4f("u_Model", m_ModelObj);
		}
		if (ImGui::DragFloat3("Move Light", glm::value_ptr(m_LightPos), 0.1f))
		{
			SetLightModel();
			m_ShaderLight->Bind();
			m_ShaderLight->setUniformMat4f("u_Model", m_ModelLight);

			m_ShaderObj->Bind();
			m_ShaderObj->setUniform3f("u_LightPos", m_LightPos);
		}
		ImGui::Spacing();
		if (ImGui::SliderFloat("Ambient Strength", &m_AmbientStrength, 0.0f, 1.0f))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniform1f("u_AmbientStrength", m_AmbientStrength);
		}
		if (ImGui::SliderFloat("Specular Strength", &m_SpecularStrength, 0.0f, 1.0f))
		{
			m_ShaderObj->Bind();
			m_ShaderObj->setUniform1f("u_SpecularStrength", m_SpecularStrength);
		}
		if (ImGui::SliderInt("Specular Shininess(2^num)", &m_SpecularShininessPow, 1, 8))
		{
			m_SpecularShininess = (int)pow(2, m_SpecularShininessPow);
			m_ShaderObj->Bind();
			m_ShaderObj->setUniform1i("u_SpecularShininess", m_SpecularShininess);
		}
	}

	//Matrix
	void TestLight::SetObjModel()
	{
		m_ModelObj = glm::translate(glm::mat4(1.0f), glm::vec3(m_ObjPos[0], m_ObjPos[1], m_ObjPos[2]));
		m_ModelObj = glm::scale(m_ModelObj, glm::vec3(m_ScaleObj));
	}

	void TestLight::SetLightModel()
	{
		m_ModelLight = glm::translate(glm::mat4(1.0f), glm::vec3(m_LightPos[0], m_LightPos[1], m_LightPos[2]));
		m_ModelLight = glm::scale(m_ModelLight, glm::vec3(m_ScaleLight));
	}
}