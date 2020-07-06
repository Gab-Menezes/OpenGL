#include <iostream>

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

//Basic
#include "Test.h"
#include "TestClearColor.h"
#include "TestDrawSquare.h"
#include "TestTexture.h"
#include "TestTransform.h"
#include "TestMVP.h"
#include "TestCamera.h"
//Light
#include "TestLight.h"
#include "TestMaterial.h"
#include "TestLightMap.h"
#include "TestLightCasters.h"
#include "TestMultipleLights.h"
//Model
#include "TestLoadModel.h"
//Advanced
#include "TestStencilTesting.h"
#include "TestBlend.h"
#include "TestFaceCulling.h"
#include "TestFramebuffer.h"

unsigned int WIDTH = 1920;
unsigned int HEIGHT = 1080;

int main()
{	
	//window setup (GLFW)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);//FPS: 60/num

	//GLAD setup
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);

	//GLFW events
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		std::cout << "Resized: " << width << ", " << height << std::endl;
		glViewport(0, 0, width, height);

		WIDTH = width;
		HEIGHT = height;
	});

	//ImGui setup
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	{
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	//Test Framework
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->PushText("Basic:");
	testMenu->PushTest<test::TestClearColor>("Clear Color");
	testMenu->PushTest<test::TestDrawSquare>("Draw Square");
	testMenu->PushTest<test::TestTexture>("Texture");
	testMenu->PushTest<test::TestTransform>("Transformation");
	testMenu->PushTest<test::TestMVP>("MVP");
	testMenu->PushTest<test::TestCamera>("Camera");
	testMenu->PushText("Light:");
	testMenu->PushTest<test::TestLight>("Light");
	testMenu->PushTest<test::TestMaterial>("Material");
	testMenu->PushTest<test::TestLightMap>("Light Map");
	testMenu->PushTest<test::TestLightCasters>("Light Casters");
	testMenu->PushTest<test::TestMultipleLights>("Multiple Lights");
	testMenu->PushText("Load Model:");
	testMenu->PushTest<test::TestLoadModel>("Load Model");
	testMenu->PushText("Advanced OpenGL:");
	testMenu->PushTest<test::TestStencilTesting>("Stencil Testing");
	testMenu->PushTest<test::TestBlend>("Blending");
	testMenu->PushTest<test::TestFaceCulling>("Face Culling");
	testMenu->PushTest<test::TestFramebuffer>("Framebuffer");

	//smooth things
	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;

	//draw loop
	while (!glfwWindowShouldClose(window))
	{
		//background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Tests
		if (currentTest)
		{
			currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			currentTest->OnRender();//OpenGL Render


			currentTest->OnUpdate(deltaTime);
			ImGui::Begin("ImGui Window");
			if (currentTest != testMenu && (ImGui::Button("<-") || glfwGetKey(window, GLFW_KEY_ESCAPE)))//checks if the user clicked in the arrow
			{
 				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();//ImGuiRender -> test change happens here
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//Frame Time and FPS
			ImGui::End();
		}

		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//window backup
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		//buffer
		glfwSwapBuffers(window);

		//events
		glfwPollEvents();
	}

	//prevent memory leak
	delete currentTest;
	if (currentTest != testMenu)
	{
		delete testMenu;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}