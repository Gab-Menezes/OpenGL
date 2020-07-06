#pragma once
#include "Test.h"

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>

namespace test
{
	class TestDrawSquare : public Test
	{
	public:
		TestDrawSquare();
		~TestDrawSquare();

		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;

		std::unique_ptr<float> m_Vertices[4];

		float m_Color[4]
		{
			0.0f, 1.0f, 1.0f, 1.0f
		};
	};
}