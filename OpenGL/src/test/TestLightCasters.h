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

enum CastersName
{
	Directional, Point, Spotlight
};

namespace test
{
	class TestLightCasters : public Test
	{
	public:
		TestLightCasters();
		~TestLightCasters();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void SetLightModel(const glm::vec3& pos);

	private:
		//ImGui
		int m_CasterIndex;
		const char* m_Casters[3];//directional->light sources infinity away | point->light sources fadding away

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
		glm::vec3 m_CubePos[10] = 
		{
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		//Light
		LightDirectional m_LightDir;
		LightPoint m_LightPoint;
		LightSpotlight m_LightSpot; float m_Inner, m_Outter; bool m_LightControl;
		glm::mat4 m_ModelLight;
	};
}