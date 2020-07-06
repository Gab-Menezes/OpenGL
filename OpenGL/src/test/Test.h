#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <iostream>
#include <string>

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {}

		void OnImGuiRender() override
		{
			unsigned int count = 0;
			for (unsigned int i = 0; i < m_Tests.size(); i++)
			{
				if (count < m_Texts.size())
				{
					if (m_Texts[count].second == i)
					{
						ImGui::Text(m_Texts[count].first.c_str());
						count++;
					}
				}
				if (ImGui::Button(m_Tests[i].first.c_str()))
				{
					m_CurrentTest = m_Tests[i].second();
				}
			}
		}

		template<typename T>
		void PushTest(const std::string& name)
		{
			std::cout << "-> Registering test: " << name << std::endl;

			m_Tests.push_back(make_pair(name, []() { return new T(); }));
		}

		void PushText(const std::string& name)
		{
			std::cout << name << std::endl;
			m_Texts.push_back(make_pair(name, m_Tests.size()));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
		std::vector<std::pair<std::string, unsigned int>> m_Texts;
	};
}