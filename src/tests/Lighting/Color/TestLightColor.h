#pragma once
#include"../../Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Object.h"

class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Texture;
class Shader;

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
namespace test {
	
	class TestLightColor:public Test
	{
	public:
		TestLightColor();
		~TestLightColor();
		void OnUpdate(float deltaTime)override;
		void OnRender()override;
		void OnImGuiRender()override;

	private:
		std::vector<Object*>m_objects;
		
		//Ãÿ ‚
		glm::vec3 lightColor = { 1,1,1 };
	public:
		glm::mat4 m_Proj, m_View;
	};
}


