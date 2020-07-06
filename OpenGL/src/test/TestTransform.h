#pragma once
#include "Test.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

namespace test
{
	class TestTransform : public Test
	{
	public:
		TestTransform();
		~TestTransform();

		void OnUpdate(float deltatime) {}
		void OnRender() override;
		void OnImGuiRender() override;

		void SetTranformMatrix();

	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;

		glm::mat4 m_TranfomMatrix;
		float m_X, m_Y;
		float m_Angle;
		float m_Scale;
		float m_Color[4];
	};

}

