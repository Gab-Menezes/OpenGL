#include "TestTexture.h"
#include "VertexBufferAttLayout.h"
#include "Renderer.h"
#include <filesystem>

namespace test
{
	TestTexture::TestTexture() : m_CurrentTextureIndex(0)
	{
		//Get the images from the folder
		namespace fs = std::filesystem;
		std::string m_BasePath = "res/textures/";
		for (auto & p : fs::directory_iterator(m_BasePath))
		{
			m_SItens.emplace_back(fs::path(p).stem().string());
			m_SringPaths.push_back(fs::path(p).string());
		}

		m_CItens.reserve(m_SItens.size());
		for (unsigned int i = 0; i < m_SItens.size(); i++)
		{
			m_CItens.push_back(m_SItens[i].c_str());
		}


		//OpenGL
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float vertices[] =
		{
			//vertices				//texture
		   -1.0f, -1.0f, 1.0f,	 	0.0f, 0.0f, //lower left
			1.0f, -1.0f, 1.0f,		1.0f, 0.0f, //lowe right
			1.0f,  1.0f, 1.0f,		1.0f, 1.0f, //top right
		   -1.0f,  1.0f, 1.0f,		0.0f, 1.0f	//top left
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};
		
		m_ShaderProgram = std::make_unique<ShaderProgram>("res/shaders/TestTexture.glsl");
		m_ShaderProgram->Bind();

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();

		m_VBO = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBO->Bind();
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddAtt(*m_VBO, layout);

		m_EBO = std::make_unique<IndexBuffer>(&indices, 6);
		m_EBO->Bind();

		m_Texture = std::make_unique<Texture>(m_SringPaths[m_CurrentTextureIndex]);
		m_Texture->Bind();

		m_ShaderProgram->setUniform1i("texture1", 0);
	}

	TestTexture::~TestTexture()
	{
		glDisable(GL_BLEND);
	}

	void TestTexture::OnRender()
	{
		m_Texture->Bind();

		Renderer render;
		render.Draw(*m_ShaderProgram, *m_VAO, *m_EBO);
	}

	void TestTexture::OnImGuiRender()
	{
		if (ImGui::Combo("Select a texture", &m_CurrentTextureIndex, m_CItens.data(), m_CItens.size()))
		{
			m_Texture = std::make_unique<Texture>(m_SringPaths[m_CurrentTextureIndex]);
		}
	}
}