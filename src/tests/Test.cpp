#include"Test.h"
#include<vector>
#include"imgui/imgui.h"
namespace test {
	TestMenu::TestMenu(Test*& CurrentTestPointer):m_CurrentTest(CurrentTestPointer)
	{
	}
	void TestMenu::OnImGuiRender()
	{
		
		for (auto& test : m_Tests) {
			
			if (ImGui::Button(test.first.c_str()))//按下对应场景button
			{
				m_CurrentTest = test.second();//切换场景
			}
		}
	}
}