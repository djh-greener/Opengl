#pragma once
#include<functional>
#include<iostream>
#include"Object.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

namespace test {
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender(){}
		virtual void OnImGuiRender() {};
	};

	class TestNormal :public Test
	{
	public:
		TestNormal():
			m_Proj(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f)),
			m_View(glm::mat4(1.0f))
		{}
		
	protected:
		std::vector<Object*>m_objects;
	public:
		glm::mat4 m_Proj, m_View;
	};

	class TestMenu :public Test
	{
	public:
		TestMenu(Test*& m_CurrentTestPointer);
		virtual void OnImGuiRender()override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering Test: " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T; }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>>m_Tests;
	};
}

