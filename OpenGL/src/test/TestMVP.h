#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <memory>

namespace test
{
	class TestMVP : public Test
	{
	public:
		TestMVP();
		~TestMVP();

		void OnRender() override;
		void OnImGuiRender() override;

		void SetModel();
		void SetView();
		void SetProj();

	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		//std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;

		//Model Matrix
		glm::mat4 m_Model;
		float m_MTranslate[3];
		float m_MAngle;
		float m_Scale;


		//View Matrix
		glm::mat4 m_View;
		float m_VTranslate[3];
		float m_VAngle;

		//Projection Matrix
		glm::mat4 m_Proj;
		float m_FOV;
	};
}
