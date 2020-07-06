#pragma once
#include "Test.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Camera.h"

#include "Materials.h"

#include <glm/glm.hpp>

#include <memory>

namespace test
{
	class TestLightMap : public Test
	{
	public:
		TestLightMap();
		~TestLightMap();

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

		//Matrix
		std::unique_ptr<Camera> m_Camera;
		glm::mat4 m_Proj;

		//Shader Variables
		//Obj
		MaterialMap m_Map;
		glm::mat4 m_ModelObj;
		float m_ScaleObj;
		glm::vec3 m_ObjPos;

		//Light
		Light m_Light;
		glm::mat4 m_ModelLight;
	};
}