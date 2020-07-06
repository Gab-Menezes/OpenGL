#pragma once
#include "Test.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <memory>

namespace test
{
	class TestLight : public Test
	{
	public:
		TestLight();
		~TestLight();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		void SetObjModel();
		void SetLightModel();

	private:
		//OpenGL
		std::unique_ptr<ShaderProgram> m_ShaderObj;
		std::unique_ptr<ShaderProgram> m_ShaderLight;

		std::unique_ptr<VertexArray> m_VAOObj;
		std::unique_ptr<VertexArray> m_VAOLight;

		std::unique_ptr<VertexBuffer> m_VBO;

		//Colors
		glm::vec4 m_ColorObj;
		glm::vec4 m_ColorLight;

		//Matrix
		glm::mat4 m_ModelObj;
		float m_ScaleObj;
		glm::vec3 m_ObjPos;


		glm::mat4 m_ModelLight;
		float m_ScaleLight;
		glm::vec3 m_LightPos;

		std::unique_ptr<Camera> m_Camera;
		glm::mat4 m_Proj;

		//Shader Variables
		float m_AmbientStrength;
		float m_SpecularStrength;
		int m_SpecularShininess;
		int m_SpecularShininessPow;
	};
}