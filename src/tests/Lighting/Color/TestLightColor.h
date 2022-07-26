#pragma once
#include"../../Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Shader;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
namespace test {
	
	class TestLightColor:public TestNormal
	{
	public:
		TestLightColor();
		~TestLightColor();
		void OnUpdate(float deltaTime)override;
		void OnRender()override;
		void OnImGuiRender()override;
		//����
		glm::vec3 lightColor = { 1,1,1 };
	};
}


