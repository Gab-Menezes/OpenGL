#include "TestFramebuffer.h"
#include "Renderer.h"

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

namespace test
{
	TestFramebuffer::TestFramebuffer() : m_Sobel(false)
	{
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

		float pixelOffsetH = 1.f / WIDTH;
		float pixelOffsetV = 1.f / HEIGHT;

		//Shaders setup
		m_ShaderText = std::make_unique<ShaderProgram>("res/shaders/TestFramebuffer/Texture.glsl");
		m_ShaderFBGray = std::make_unique<ShaderProgram>("res/shaders/TestFramebuffer/Gray.glsl");
		m_ShaderFBGaussian = std::make_unique<ShaderProgram>("res/shaders/TestFramebuffer/Gaussian.glsl");
		m_ShaderFBSobel = std::make_unique<ShaderProgram>("res/shaders/TestFramebuffer/Sobel.glsl");

		//Vertices layout
		VertexBufferAttLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		//Texture setup
		m_VAOText = std::make_unique<VertexArray>();
		m_VAOText->Bind();
		m_VBOText = std::make_unique<VertexBuffer>(&vertices, sizeof(vertices));
		m_VBOText->Bind();
		m_VAOText->AddAtt(*m_VBOText, layout);
		m_EBOText = std::make_unique<IndexBuffer>(&indices, 6);
		m_VBOText->Unbind();
		m_VAOText->Unbind();

		//Texture Uniforms
		m_ShaderText->Bind();
		m_ShaderText->setUniform1i("u_Texture", 0);
		m_ShaderText->Unbind();
		//Gray Uniforms
		m_ShaderFBGray->Bind();
		m_ShaderFBGray->setUniform1i("u_Texture", 0);
		m_ShaderFBGray->Unbind();
		//Gaussian Uniforms
		m_ShaderFBGaussian->Bind();
		m_ShaderFBGaussian->setUniform1f("u_OffsetH", pixelOffsetH);
		m_ShaderFBGaussian->setUniform1f("u_OffsetV", pixelOffsetV);
		m_ShaderFBGaussian->setUniform1i("u_Texture", 0);
		m_ShaderFBGaussian->Unbind();
		//Sobel Uniforms
		m_ShaderFBSobel->Bind();
		m_ShaderFBSobel->setUniform1f("u_OffsetH", pixelOffsetH);
		m_ShaderFBSobel->setUniform1f("u_OffsetV", pixelOffsetV);
		m_ShaderFBSobel->setUniform1i("u_Texture", 0);
		m_ShaderFBSobel->Unbind();

		//Texture load
		m_Texture = std::make_unique<Texture>("res/textures/input.png");

		//Gray Framebuffer setup
		m_FBGray = std::make_unique<Framebuffer>();
		m_FBGray->Bind();
		m_FBGray->AddTexture();
		if (!m_FBGray->CheckFramebuffer())
		{
			std::cout << "ERROR: Framebuffer not complete!" << std::endl;
		}
		m_FBGray->Unbind();

		//Gaussian Framebuffer setup
		//Horizontal
		m_FBGaussianH = std::make_unique<Framebuffer>();
		m_FBGaussianH->Bind();
		m_FBGaussianH->AddTexture();
		if (!m_FBGaussianH->CheckFramebuffer())
		{
			std::cout << "ERROR: Framebuffer not complete!" << std::endl;
		}
		m_FBGaussianH->Unbind();
		//Vertical
		m_FBGaussianV = std::make_unique<Framebuffer>();
		m_FBGaussianV->Bind();
		m_FBGaussianV->AddTexture();
		if (!m_FBGaussianV->CheckFramebuffer())
		{
			std::cout << "ERROR: Framebuffer not complete!" << std::endl;
		}
		m_FBGaussianV->Unbind();

		//Sobel Framebuffer setup
		m_FBSobel = std::make_unique<Framebuffer>();
		m_FBSobel->Bind();
		m_FBSobel->AddTexture();
		if (!m_FBSobel->CheckFramebuffer())
		{
			std::cout << "ERROR: Framebuffer not complete!" << std::endl;
		}
		m_FBSobel->Unbind();
	}

	TestFramebuffer::~TestFramebuffer()
	{
		glDisable(GL_BLEND);
	}

	void TestFramebuffer::OnRender()
	{
		Renderer render;

		//Texture -> Gray Framebuffer
		m_FBGray->Bind();
		m_FBGray->Clear(0.1f, 0.1f, 0.1f, 1.0f);
		m_Texture->Bind();
		render.Draw(*m_ShaderText, *m_VAOText, *m_EBOText);
		m_Texture->Unbind();
		m_FBGray->Unbind();

		//Gaussian Framebuffer
		//Gray -> Gaussian Horizontal
		m_FBGaussianH->Bind();
		m_FBGaussianH->Clear(0.1f, 0.1f, 0.1f, 1.0f);
		m_FBGray->BindTexture();
		render.Draw(*m_ShaderFBGray, *m_VAOText, *m_EBOText);
		m_FBGray->UnbindTexture();
		m_FBGaussianH->Unbind();
		//Gaussian Horizontal -> Gaussian Vertical
		m_FBGaussianV->Bind();
		m_FBGaussianV->Clear(0.1f, 0.1f, 0.1f, 1.0f);
		m_FBGaussianH->BindTexture();
		m_ShaderFBGaussian->Bind();
		m_ShaderFBGaussian->setUniform1i("u_Vertical", 0);
		m_ShaderFBGaussian->Unbind();
		render.Draw(*m_ShaderFBGaussian, *m_VAOText, *m_EBOText);
		m_FBGaussianH->UnbindTexture();
		m_FBGaussianV->Unbind();

		//Sobel Framebuffer
		//Gaussian Vertical -> Sobel Horizontal
		m_FBSobel->Bind();
		m_FBSobel->Clear(0.1f, 0.1f, 0.1f, 1.0f);
		m_FBGaussianV->BindTexture();
		m_ShaderFBGaussian->Bind();
		m_ShaderFBGaussian->setUniform1i("u_Vertical", 1);
		m_ShaderFBGaussian->Unbind();
		render.Draw(*m_ShaderFBGaussian, *m_VAOText, *m_EBOText);
		m_FBGaussianV->UnbindTexture();
		m_FBSobel->Unbind();

		//Sobel Vertical -> Default Framebuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_FBSobel->BindTexture();
		render.Draw(*m_ShaderFBSobel, *m_VAOText, *m_EBOText);
		m_FBSobel->UnbindTexture();
	}

	void TestFramebuffer::OnImGuiRender()
	{
		ImGui::Checkbox("Sobel", &m_Sobel);
	}
}