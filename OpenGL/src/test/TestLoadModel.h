#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "LoadModel.h"
#include "Camera.h"
#include "Materials.h"
#include <memory>

namespace test
{
	class TestLoadModel : public Test
	{
	public:
		TestLoadModel();
		~TestLoadModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<ShaderProgram> m_ModelShader;
		std::unique_ptr<Model> m_Model;
		glm::mat4 m_ModelMatrix;

		LightPoint m_Light;
		float m_Amb, m_Diff, m_Spec;
		std::unique_ptr<ShaderProgram> m_LightShader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		glm::mat4 m_LightMatrix;

		std::unique_ptr<Camera> m_Camera;
		glm::mat4 m_Proj;
	};
}